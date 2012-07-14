#include <qcodingchaincomponent.h>

#define CHUNK_SIZE 8192

/**********************************************************
QCodingChainComponent
**********************************************************/

QCodingChainComponent::QCodingChainComponent()
	: QObject()
{
	mNext = NULL;
}

void QCodingChainComponent::setNext(QCodingChainComponent *next)
{
	mNext = next;
}

int QCodingChainComponent::chunkSize()
{
	return CHUNK_SIZE;
}

void QCodingChainComponent::changeFormat(QExtendedAudioFormat format)
{
}

void QCodingChainComponent::addData(QSampleArray *data)
{
	mData.enqueue(data);
	execute();
}

void QCodingChainComponent::addData(QSampleArray *data, qint64 position)
{
	seek(position);
	addData(data);
}

void QCodingChainComponent::seek(qint64 position)
{
}

/**********************************************************
QCodingChainInput
**********************************************************/

QCodingChainInput::QCodingChainInput()
	: QCodingChainComponent()
{
	mSampleSize = -1;
}

void QCodingChainInput::setSampleSize(int size)
{
	mSampleSize = size / 8;
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

bool QCodingChainFileInput::hasData()
{
	return !mFile.atEnd();
}

int QCodingChainFileInput::size()
{
	return mFile.size();
}

void QCodingChainFileInput::initialize()
{
	mData.clear();
	mFile.setFileName(mFilePath);
	mFile.open(QIODevice::ReadOnly);
}

void QCodingChainFileInput::execute()
{
	char *data = new char[CHUNK_SIZE];
	int size = mFile.read(data, CHUNK_SIZE);
	mNext->addData(new QSampleArray(data, size));
}

void QCodingChainFileInput::finalize()
{
	mFile.close();
}

/**********************************************************
QCodingChainDataInput
**********************************************************/

QCodingChainDataInput::QCodingChainDataInput()
	: QCodingChainInput()
{
	mByteArray = NULL;
	mStream = NULL;
}

QCodingChainDataInput::~QCodingChainDataInput()
{
	if(mStream != NULL)
	{
		delete mStream;
		mStream = NULL;
	}
	mByteArray = NULL;
}

void QCodingChainDataInput::setData(QByteArray &data)
{
	mByteArray = &data;
}

bool QCodingChainDataInput::hasData()
{
	return !mStream->atEnd();
}

int QCodingChainDataInput::size()
{
	return mByteArray->size();
}

void QCodingChainDataInput::initialize()
{
	mData.clear();
	if(mStream != NULL)
	{
		delete mStream;
		mStream = NULL;
	}
	mStream = new QDataStream(mByteArray, QIODevice::ReadOnly);
}

void QCodingChainDataInput::execute()
{
	char *data = new char[CHUNK_SIZE];
	int size = mStream->readRawData(data, CHUNK_SIZE);
	mNext->addData(new QSampleArray(data, size, size / mSampleSize));
}

void QCodingChainDataInput::finalize()
{
	if(mStream != NULL)
	{
		delete mStream;
		mStream = NULL;
	}
	mByteArray = NULL;
}

/**********************************************************
QCodingChainCoder
**********************************************************/

QCodingChainCoder::QCodingChainCoder()
	: QCodingChainComponent()
{
	mCoder = NULL;
}

void QCodingChainCoder::setCoder(QAbstractCoder *coder)
{
	mCoder = coder;
}

/**********************************************************
QCodingChainDecoder
**********************************************************/

QCodingChainDecoder::QCodingChainDecoder()
	: QCodingChainCoder()
{
}

void QCodingChainDecoder::setCoder(QAbstractCoder *coder)
{
	QCodingChainCoder::setCoder(coder);
	coder->disconnect(coder, SIGNAL(formatChanged(QExtendedAudioFormat)));
	QObject::connect(coder, SIGNAL(formatChanged(QExtendedAudioFormat)), mNext, SLOT(changeFormat(QExtendedAudioFormat)), Qt::DirectConnection);
}

void QCodingChainDecoder::initialize()
{
	mData.clear();
	if(mCoder != NULL && mCoder->initializeDecode())
	{
		mCoder->disconnect(mCoder, SIGNAL(decoded(QSampleArray*)));
		QObject::connect(mCoder, SIGNAL(decoded(QSampleArray*)), mNext, SLOT(addData(QSampleArray*)), Qt::DirectConnection);
	}
}

void QCodingChainDecoder::finalize()
{
	if(mCoder != NULL)
	{
		mCoder->finalizeDecode();
		mCoder->disconnect();
	}
}

void QCodingChainDecoder::execute()
{
	QSampleArray *array = mData.dequeue();
	mCoder->decode(array->data(), array->size());
	delete array;
}

/**********************************************************
QCodingChainEncoder
**********************************************************/

QCodingChainEncoder::QCodingChainEncoder()
	: QCodingChainCoder()
{
}

void QCodingChainEncoder::changeFormat(QExtendedAudioFormat format)
{
	if(mCoder != NULL)
	{
		mCoder->setFormat(QAudio::AudioInput, format);
		if(mCoder->initializeEncode())
		{
			int size = mCoder->headerSize();
			qbyte *data = new qbyte[size];
			mNext->addData(new QSampleArray(data, size));
			mCoder->disconnect(mCoder, SIGNAL(encoded(QSampleArray*)));
			QObject::connect(mCoder, SIGNAL(encoded(QSampleArray*)), mNext, SLOT(addData(QSampleArray*)), Qt::DirectConnection);
		}
	}
}

void QCodingChainEncoder::initialize()
{
	mData.clear();
}

void QCodingChainEncoder::finalize()
{
	mNext->addData(new QSampleArray(mCoder->header()), 0);
	if(mCoder != NULL)
	{
		mCoder->finalizeEncode();
		mCoder->disconnect();
	}
}

void QCodingChainEncoder::execute()
{
	QSampleArray *array = mData.dequeue();
	mCoder->encode(array->data(), array->samples());
	delete array;
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

void QCodingChainFileOutput::seek(qint64 position)
{
	mFile.seek(position);
}

void QCodingChainFileOutput::initialize()
{
	mData.clear();
	mFile.setFileName(mFilePath);
	mFile.open(QIODevice::WriteOnly);
}

void QCodingChainFileOutput::finalize()
{
	mFile.close();
}

void QCodingChainFileOutput::execute()
{
	QSampleArray *array = mData.dequeue();
	mFile.write(array->charData(), array->size());
	delete array;
}

/**********************************************************
QCodingChainDataOutput
**********************************************************/

QCodingChainDataOutput::QCodingChainDataOutput()
	: QCodingChainOutput()
{
	mByteArray = NULL;
	mStream = NULL;
}

QCodingChainDataOutput::~QCodingChainDataOutput()
{
	if(mStream != NULL)
	{
		delete mStream;
		mStream = NULL;
	}
	mByteArray = NULL;
}

void QCodingChainDataOutput::setData(QByteArray &data)
{
	mByteArray = &data;
}

void QCodingChainDataOutput::seek(qint64 position)
{
	if(mStream != NULL)
	{
		delete mStream;
		mStream = NULL;
	}
	mStream = new QDataStream(mByteArray, QIODevice::WriteOnly);
	mStream->skipRawData(position);
}

void QCodingChainDataOutput::initialize()
{
	mData.clear();
	if(mStream != NULL)
	{
		delete mStream;
		mStream = NULL;
	}
	mStream = new QDataStream(mByteArray, QIODevice::WriteOnly);
}

void QCodingChainDataOutput::finalize()
{
	if(mStream != NULL)
	{
		delete mStream;
		mStream = NULL;
	}
	mByteArray = NULL;
}

void QCodingChainDataOutput::execute()
{
	QSampleArray *array = mData.dequeue();
	mStream->writeRawData(array->charData(), array->size());
	delete array;
}
