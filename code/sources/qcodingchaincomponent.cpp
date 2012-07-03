#include <qcodingchaincomponent.h>

#define CHUNK_SIZE 8192
#define FILE_BUFFER_SIZE 8

/**********************************************************
QCodingChainComponent
**********************************************************/

QCodingChainComponent::QCodingChainComponent()
	: QThread()
{
}

bool QCodingChainComponent::hasChunk()
{
	mMutex.lock();
	bool result = !mChunks.isEmpty();
	mMutex.unlock();
	return result;
}

void QCodingChainComponent::addChunk(QAudioChunk *chunk)
{
	mMutex.lock();
	mChunks.enqueue(chunk);
	mMutex.unlock();
	if(!isRunning())
	{
		start();
	}
}

QAudioChunk* QCodingChainComponent::takeChunk()
{
	mMutex.lock();
	QAudioChunk* chunk = mChunks.dequeue();
	mMutex.unlock();
	return chunk;
}

int QCodingChainComponent::numberOfChunks()
{
	mMutex.lock();
	int size = mChunks.size();
	mMutex.unlock();
	return size;
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
	while(numberOfChunks() < FILE_BUFFER_SIZE && !mAtEnd)
	{
		qbyte *data = new qbyte[CHUNK_SIZE];
		size = mFile.read((char*) data, CHUNK_SIZE);
		if(size > 0)
		{
			/*addChunk(new QAudioChunk(data, 0, size));
			emit available(takeChunk());*/
			emit available(new QAudioChunk(data, 0, size));
		}
		else
		{
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
		QObject::connect(mCodec, SIGNAL(decoded(QAudioChunk*)), this, SIGNAL(available(QAudioChunk*)));
		return true;
	}
	return false;
}

bool QCodingChainDecoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeDecode())
	{
		QObject::disconnect(mCodec, SIGNAL(decoded(QAudioChunk*)), this, SIGNAL(available(QAudioChunk*)));
		return true;
	}
	return false;
}

void QCodingChainDecoder::run()
{
	QAudioChunk *chunk;
	while(hasChunk())
	{
		chunk = takeChunk();
		mCodec->decode(chunk->data(), chunk->bytes());
		delete chunk;
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
		QObject::connect(mCodec, SIGNAL(encoded(QAudioChunk*)), this, SIGNAL(available(QAudioChunk*)));
		return true;
	}
	return false;
}

bool QCodingChainEncoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeEncode())
	{
		QObject::disconnect(mCodec, SIGNAL(encoded(QAudioChunk*)), this, SIGNAL(available(QAudioChunk*)));
		return true;
	}
	return false;
}

void QCodingChainEncoder::run()
{
	QAudioChunk *chunk;
	while(hasChunk())
	{
		chunk = takeChunk();
		mCodec->encode(chunk->data(), chunk->samples());
		delete chunk;
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
	QAudioChunk *chunk;
	while(hasChunk())
	{
		chunk = takeChunk();
		mFile.write((char*) chunk->data(), chunk->bytes());
	}
}
