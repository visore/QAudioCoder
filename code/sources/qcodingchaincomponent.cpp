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
	return !mChunks.isEmpty();
}

void QCodingChainComponent::addChunk(QAudioChunk chunk)
{
	mChunks.enqueue(chunk);
}

QAudioChunk QCodingChainComponent::takeChunk()
{
	return mChunks.dequeue();
}

int QCodingChainComponent::numberOfChunks()
{
	return mChunks.size();
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
	while(numberOfChunks() < FILE_BUFFER_SIZE)
	{
		qbyte *data = new qbyte[CHUNK_SIZE];
		size = mFile.read((char*) data, CHUNK_SIZE);
		if(size > 0)
		{
			addChunk(QAudioChunk(data, 0, size));
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
		QObject::connect(mCodec, SIGNAL(decoded(QAudioChunk)), this, SLOT(available(QAudioChunk)));
		return true;
	}
	return false;
}

bool QCodingChainDecoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeDecode())
	{
		QObject::disconnect(mCodec, SIGNAL(decoded(QAudioChunk)), this, SLOT(available(QAudioChunk)));
		return true;
	}
	return false;
}

void QCodingChainDecoder::run()
{
	QAudioChunk chunk;
	while(hasChunk())
	{
		chunk = takeChunk();
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
		QObject::connect(mCodec, SIGNAL(encoded(QAudioChunk)), this, SLOT(available(QAudioChunk)));
		return true;
	}
	return false;
}

bool QCodingChainEncoder::finalize()
{
	if(mCodec != NULL && mCodec->finalizeDecode())
	{
		QObject::disconnect(mCodec, SIGNAL(encoded(QAudioChunk)), this, SLOT(available(QAudioChunk)));
		return true;
	}
	return false;
}

void QCodingChainEncoder::run()
{
	QAudioChunk chunk;
	while(hasChunk())
	{
		chunk = takeChunk();
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
	while(hasChunk())
	{
		chunk = takeChunk();
		mFile.write((char*) chunk.data(), chunk.bytes());
	}
}
