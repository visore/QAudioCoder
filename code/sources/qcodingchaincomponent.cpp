#include <qcodingchaincomponent.h>

#define CHUNK_SIZE 8192

/**********************************************************
QCodingChainComponent
**********************************************************/

QCodingChainComponent::QCodingChainComponent()
	: QThread()
{
	mNext = NULL;
	mInputBuffer = NULL;
	mOutputBuffer = NULL;
	mChunksToRead = 10;
	runPointer = &QCodingChainComponent::initialize;
}

QCodingChainComponent::~QCodingChainComponent()
{
	if(mInputBuffer != NULL)
	{
		delete mInputBuffer;
		mInputBuffer = NULL;
	}
	if(mOutputBuffer != NULL)
	{
		delete mOutputBuffer;
		mOutputBuffer = NULL;
	}
}


void QCodingChainComponent::setInputBuffer(QSharedBuffer *buffer)
{
	mInputBuffer = buffer;
}

void QCodingChainComponent::setOutputBuffer(QSharedBuffer *buffer)
{
	mOutputBuffer = buffer;
}

void QCodingChainComponent::setNext(QCodingChainComponent *next)
{
	mNext = next;
	mOutputBuffer = new QSharedBuffer();
	mNext->setInputBuffer(mOutputBuffer);
	QObject::connect(this, SIGNAL(wasFinished()), mNext, SLOT(finish()));
	QObject::connect(mOutputBuffer, SIGNAL(dataAdded()), mNext, SLOT(dataAvailable()));
	QObject::connect(mOutputBuffer, SIGNAL(almostEmpty(int)), this, SLOT(processData(int)));
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
	if(!isRunning() && !mFinishUp)
	{
		start();
	}
}

void QCodingChainComponent::finish()
{
	mFinishUp = true;
}

void QCodingChainComponent::run()
{
	(this->*runPointer)();
}

void QCodingChainComponent::initialize()
{
	mFinishUp = false;
	initializeComponent();
	runPointer = &QCodingChainComponent::executeComponent;
	run();
}

void QCodingChainComponent::finalize()
{
	finalizeComponent();
	runPointer = &QCodingChainComponent::initializeComponent;
	mFinishUp = true;
	emit wasFinished();
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

void QCodingChainFileInput::initializeComponent()
{
	mFile.setFileName(mFilePath);
	if(!mFile.open(QIODevice::ReadOnly))
	{
		return;
	}
}

void QCodingChainFileInput::executeComponent()
{
	int size = 0;
	int chunks = mChunksToRead;
	while(mChunksToRead > 0 && !mFinishUp)
	{
		--mChunksToRead;
		char *data = new char[CHUNK_SIZE];
		size = mFile.read(data, CHUNK_SIZE);
		if(size > 0)
		{
			mOutputBuffer->enqueue(new QSampleArray(data, size));
		}
		else
		{
			delete [] data;
			finalize();
			break;
		}
	}
}

void QCodingChainFileInput::finalizeComponent()
{
	mFile.close();
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

void QCodingChainDecoder::initializeComponent()
{
	if(mCoder != NULL && mCoder->initializeDecode())
	{
		QObject::connect(mCoder, SIGNAL(decoded(QSampleArray*)), mOutputBuffer, SLOT(enqueue(QSampleArray*)));
	}
}

void QCodingChainDecoder::finalizeComponent()
{
	if(mCoder != NULL && mCoder->finalizeDecode())
	{
		QObject::disconnect(mCoder, SIGNAL(decoded(QSampleArray*)));
	}
}

void QCodingChainDecoder::executeComponent()
{
	QSampleArray *array;
	while(mChunksToRead > 0 && !mInputBuffer->isEmpty())
	{cout<<"decoder..."<<endl;
		//--mChunksToRead;
		array = mInputBuffer->dequeue();
		//mCoder->decode(array->data(), array->size());
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

void QCodingChainEncoder::initializeComponent()
{/*
	if(mCoder != NULL && mCoder->initializeEncode())
	{
		QObject::connect(mCoder, SIGNAL(encoded(QSampleArray*)), mOutputBuffer, SLOT(enqueue(QSampleArray*)));
		return true;
	}
	return false;*/
}

void QCodingChainEncoder::finalizeComponent()
{/*
	if(mCoder != NULL && mCoder->finalizeEncode())
	{
		QObject::disconnect(mCoder, SIGNAL(encoded(QSampleArray*)));
		return true;
	}
	return false;*/
}
/*
void QCodingChainEncoder::run()
{
	QSampleArray *array;
	while(mChunksToRead > 0 && !mInputBuffer->isEmpty())
	{
		--mChunksToRead;
		array = mInputBuffer->dequeue();
cout<<array->samples()<<" pop"l<<endl;
		mCoder->encode(array->data(), array->samples());
cout<<"**pop"<<endl;
		delete array;
	}
}
*/
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

void QCodingChainFileOutput::initializeComponent()
{/*
	mFile.setFileName(mFilePath);
	if(!mFile.open(QIODevice::WriteOnly))
	{
		return false;
	}
	mFile.write(mHeader);
	return true;*/
}

void QCodingChainFileOutput::finalizeComponent()
{/*
	mFile.close();
	return true;*/
}
/*
void QCodingChainFileOutput::run()
{
	QSampleArray *array;
	while(!mInputBuffer->isEmpty())
	{
		array = mInputBuffer->dequeue();
		mFile.write(array->charData(), array->size());
		delete array;
	}
}*/
