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
}

void QCodingChainComponent::setInputBuffer(QSharedBuffer *buffer)
{
	mInputBuffer = buffer;
}

void QCodingChainComponent::setOutputBuffer(QSharedBuffer *buffer)
{
	mOutputBuffer = buffer;
}

void QCodingChainComponent::chunkAvailable()
{
	if(!isRunning())
	{
		start();
	}
}

void QCodingChainComponent::addChunks(int size)
{
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

void QCodingChainInput::addChunks(int size)
{
	if(!isRunning())
	{
		start();
	}
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
	while(!mAtEnd)
	{
		qbyte *data = new qbyte[CHUNK_SIZE];
		size = mFile.read((char*) data, CHUNK_SIZE);
		if(size > 0)
		{
			mOutputBuffer->enqueue(new QAudioChunk(data, 0, size));
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
		QObject::connect(mCodec, SIGNAL(decoded(QAudioChunk*)), mOutputBuffer, SLOT(enqueue(QAudioChunk*)));
		return true;
	}
	return false;
}

bool QCodingChainDecoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeDecode())
	{
		QObject::disconnect(mCodec, SIGNAL(decoded(QAudioChunk*)), mOutputBuffer, SLOT(enqueue(QAudioChunk*)));
		return true;
	}
	return false;
}

void QCodingChainDecoder::run()
{
	QAudioChunk *chunk;
	while(!mInputBuffer->isEmpty())
	{
		chunk = mInputBuffer->dequeue();
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
		QObject::connect(mCodec, SIGNAL(encoded(QAudioChunk*)), mOutputBuffer, SLOT(enqueue(QAudioChunk*)));
		return true;
	}
	return false;
}

bool QCodingChainEncoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeEncode())
	{
		QObject::disconnect(mCodec, SIGNAL(encoded(QAudioChunk*)), mOutputBuffer, SLOT(enqueue(QAudioChunk*)));
		return true;
	}
	return false;
}

void QCodingChainEncoder::run()
{
	QAudioChunk *chunk;
	while(!mInputBuffer->isEmpty())
	{
		chunk = mInputBuffer->dequeue();
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
	while(!mInputBuffer->isEmpty())
	{
		chunk = mInputBuffer->dequeue();
		mFile.write((char*) chunk->data(), chunk->bytes());
		delete chunk;
	}
}
