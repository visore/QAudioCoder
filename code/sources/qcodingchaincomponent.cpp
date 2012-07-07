#include <qcodingchaincomponent.h>

#define CHUNK_SIZE 8192

/**********************************************************
QCodingChainComponent
**********************************************************/

QCodingChainComponent::QCodingChainComponent()
	: QThread()
{
	mInputBuffer = NULL;
	mOutputBuffer = NULL;
	mChunksToRead = 10;
}

void QCodingChainComponent::setInputBuffer(QSharedBuffer *buffer)
{
	mInputBuffer = buffer;
}

void QCodingChainComponent::setOutputBuffer(QSharedBuffer *buffer)
{
	mOutputBuffer = buffer;
}

void QCodingChainComponent::dataAvailable()
{
	if(!isRunning())
	{
		start();
	}
}

void QCodingChainComponent::processData(int size)
{
	mChunksToRead = size;
	if(!isRunning())
	{
		start();
	}
}

/**********************************************************
QCodingChainInput
**********************************************************/

QCodingChainInput::QCodingChainInput()
	: QCodingChainComponent()
{
	mHeaderSize = 0;
	mAtEnd = false;
}

void QCodingChainInput::skipHeader(int bytes)
{
	mHeaderSize = bytes;
}

/**********************************************************
QCodingChainFileInput
**********************************************************/

QCodingChainFileInput::QCodingChainFileInput()
	: QCodingChainInput()
{
	mFilePath = "";
}

void QCodingChainFileInput::setFilePath(QString filePath)
{
	mFilePath = filePath;
}

bool QCodingChainFileInput::initialize()
{
	mFile.setFileName(mFilePath);
	if(!mFile.open(QIODevice::ReadOnly))
	{
		return false;
	}
	mFile.seek(mHeaderSize);
	mAtEnd = false;
	return true;
}

bool QCodingChainFileInput::finalize()
{
	mFile.close();
	return true;
}
		
void QCodingChainFileInput::run()
{
	int size = 0;
	int chunks = mChunksToRead;
	while(mChunksToRead > 0 && !mAtEnd)
	{
		--mChunksToRead;
		char *data = new char[CHUNK_SIZE];
		size = mFile.read(data, CHUNK_SIZE);
		if(size > 0)
		{
			mOutputBuffer->enqueue(new QSampleArray(data, size));
		}
		else
		{cout<<"at end"<<endl;
			delete [] data;
			mAtEnd = true;
			emit atEnd();
			break;
		}
	}
}

/**********************************************************
QCodingChainCoder
**********************************************************/

QCodingChainCoder::QCodingChainCoder()
	: QCodingChainComponent()
{
	mCodec = NULL;
}

void QCodingChainCoder::setCodec(QAbstractCodec *codec)
{
	mCodec = codec;
}

/**********************************************************
QCodingChainDecoder
**********************************************************/

QCodingChainDecoder::QCodingChainDecoder()
	: QCodingChainCoder()
{
}

bool QCodingChainDecoder::initialize()
{
	if(mCodec != NULL && mCodec->initializeDecode())
	{
		QObject::connect(mCodec, SIGNAL(decoded(QSampleArray*)), mOutputBuffer, SLOT(enqueue(QSampleArray*)));
		return true;
	}
	return false;
}

bool QCodingChainDecoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeDecode())
	{
		QObject::disconnect(mCodec, SIGNAL(decoded(QSampleArray*)), mOutputBuffer, SLOT(enqueue(QSampleArray*)));
		return true;
	}
	return false;
}

void QCodingChainDecoder::run()
{
	QSampleArray *array;
	while(mChunksToRead > 0 && !mInputBuffer->isEmpty())
	{
		--mChunksToRead;
		array = mInputBuffer->dequeue();
		mCodec->decode(array->data(), array->size());
		delete array;
	}
}

/**********************************************************
QCodingChainEncoder
**********************************************************/

QCodingChainEncoder::QCodingChainEncoder()
	: QCodingChainCoder()
{
}

bool QCodingChainEncoder::initialize()
{
	if(mCodec != NULL && mCodec->initializeEncode())
	{
		QObject::connect(mCodec, SIGNAL(encoded(QSampleArray*)), mOutputBuffer, SLOT(enqueue(QSampleArray*)));
		return true;
	}
	return false;
}

bool QCodingChainEncoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeEncode())
	{
		QObject::disconnect(mCodec, SIGNAL(encoded(QSampleArray*)), mOutputBuffer, SLOT(enqueue(QSampleArray*)));
		return true;
	}
	return false;
}

void QCodingChainEncoder::run()
{
	QSampleArray *array;
	while(mChunksToRead > 0 && !mInputBuffer->isEmpty())
	{
		--mChunksToRead;
		array = mInputBuffer->dequeue();
		mCodec->encode(array->data(), array->samples());
		delete array;
	}
}

/**********************************************************
QCodingChainOutput
**********************************************************/

QCodingChainOutput::QCodingChainOutput()
	: QCodingChainComponent()
{
}

void QCodingChainOutput::setHeader(QByteArray header)
{
	mHeader = header;
}

/**********************************************************
QCodingChainFileOutput
**********************************************************/

QCodingChainFileOutput::QCodingChainFileOutput()
	: QCodingChainOutput()
{
	mFilePath = "";
}

void QCodingChainFileOutput::setFilePath(QString filePath)
{
	mFilePath = filePath;
}

bool QCodingChainFileOutput::initialize()
{
	mFile.setFileName(mFilePath);
	if(!mFile.open(QIODevice::WriteOnly))
	{
		return false;
	}
	mFile.write(mHeader);
	return true;
}

bool QCodingChainFileOutput::finalize()
{
	mFile.close();
	return true;
}

void QCodingChainFileOutput::run()
{
	QSampleArray *array;
	while(!mInputBuffer->isEmpty())
	{
		array = mInputBuffer->dequeue();
		mFile.write(array->charData(), array->size());
		delete array;
	}
}
