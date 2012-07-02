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

bool QCodingChainComponent::hasInputChunk()
{
	mMutex.lock();
	bool result = !mInputChunks.isEmpty();
	mMutex.unlock();
	return result;
}

bool QCodingChainComponent::hasOutputChunk()
{
	mMutex.lock();
	bool result = !mOutputChunks.isEmpty();
	mMutex.unlock();
	return result;
}

void QCodingChainComponent::addInputChunk(QAudioChunk chunk)
{
	mMutex.lock();
	mInputChunks.enqueue(chunk);
	mMutex.unlock();
}

void QCodingChainComponent::addOutputChunk(QAudioChunk chunk)
{
	mMutex.lock();
	mOutputChunks.enqueue(chunk);
	mMutex.unlock();
	emit chunkAvailable();
}

QAudioChunk QCodingChainComponent::takeInputChunk()
{
	mMutex.lock();
	QAudioChunk chunk = mInputChunks.dequeue();
	mMutex.unlock();
	return chunk;
}

QAudioChunk QCodingChainComponent::takeOutputChunk()
{
	mMutex.lock();
	QAudioChunk chunk = mOutputChunks.dequeue();
	mMutex.unlock();
	return chunk;
}

int QCodingChainComponent::numberOfInputChunks()
{
	mMutex.lock();
	int size = mInputChunks.size();
	mMutex.unlock();
	return size;
}

int QCodingChainComponent::numberOfOutputChunks()
{
	mMutex.lock();
	int size = mOutputChunks.size();
	mMutex.unlock();
	return size;
}

/**********************************************************
QCodingChainInput
**********************************************************/

QCodingChainInput::QCodingChainInput()
	: QCodingChainComponent()
{
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
	return mFile.open(QIODevice::ReadOnly);
}

bool QCodingChainFileInput::finalize()
{
	mFile.close();
	return true;
}
		
void QCodingChainFileInput::run()
{
	int size = 0;
	while(numberOfOutputChunks() < FILE_BUFFER_SIZE)
	{
		qbyte *data = new qbyte[CHUNK_SIZE];
		size = mFile.read((char*) data, CHUNK_SIZE);
		if(size > 0)
		{
			addOutputChunk(QAudioChunk(data, 0, size));
		}
		else
		{
			delete data;
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
		QObject::connect(mCodec, SIGNAL(decoded(QAudioChunk)), this, SLOT(addOutputChunk(QAudioChunk)));
		return true;
	}
	return false;
}

bool QCodingChainDecoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeDecode())
	{
		QObject::disconnect(mCodec, SIGNAL(decoded(QAudioChunk)), this, SLOT(addOutputChunk(QAudioChunk)));
		return true;
	}
	return false;
}

void QCodingChainDecoder::run()
{
	QAudioChunk chunk;
	while(hasInputChunk())
	{
		chunk = takeInputChunk();
		mCodec->decode(chunk.data(), chunk.bytes());
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
	if(mCodec != NULL && mCodec->initializeDecode())
	{
		QObject::connect(mCodec, SIGNAL(encoded(QAudioChunk)), this, SLOT(addOutputChunk(QAudioChunk)));
		return true;
	}
	return false;
}

bool QCodingChainEncoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeDecode())
	{
		QObject::disconnect(mCodec, SIGNAL(encoded(QAudioChunk)), this, SLOT(addOutputChunk(QAudioChunk)));
		return true;
	}
	return false;
}

void QCodingChainEncoder::run()
{
	QAudioChunk chunk;
	while(hasInputChunk())
	{
		chunk = takeInputChunk();
		mCodec->encode(chunk.data(), chunk.samples());
	}
}

/**********************************************************
QCodingChainOutput
**********************************************************/

QCodingChainOutput::QCodingChainOutput()
	: QCodingChainComponent()
{
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
	return mFile.open(QIODevice::WriteOnly);
}

bool QCodingChainFileOutput::finalize()
{
	mFile.close();
	return true;
}

void QCodingChainFileOutput::run()
{
	QAudioChunk chunk;
	while(hasInputChunk())
	{
		chunk = takeInputChunk();
		mFile.write((char*) chunk.data(), chunk.bytes());
	}
}
