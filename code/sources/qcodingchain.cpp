#include <qcodingchain.h>
#include <QFile>

QCodingChain::QCodingChain()
	: QThread()
{
	mManager = &QAudioManager::instance();
	setMode(QCodingChain::Unknown);
}

void QCodingChain::setMode(QCodingChain::Mode mode)
{
	reset();
	mMode = mode;
}

void QCodingChain::reset()
{
	mInputFilePath = "";
	mInputData = NULL;
	mInput = NULL;
	mOutput = NULL;
	mInputCoder = NULL;
	mOutputCoder = NULL;
}

void QCodingChain::setInput(QString filePath)
{
	mInputFilePath = filePath;
	mFileInput.setFilePath(filePath);
	mInput = &mFileInput;
	detectCoder = &QCodingChain::detectCoderFile;
}

void QCodingChain::setOutput(QString filePath)
{
	mFileOutput.setFilePath(filePath);
	mOutput = &mFileOutput;
}

void QCodingChain::setInput(QByteArray &array)
{
	mInputData = &array;
	mDataInput.setData(array);
	mInput = &mDataInput;
	detectCoder = &QCodingChain::detectCoderData;
}

void QCodingChain::setOutput(QByteArray &array)
{
	mDataOutput.setData(array);
	mOutput = &mDataOutput;
}

void QCodingChain::setInput(QExtendedAudioFormat format)
{
	mInputFormat = format;
}

void QCodingChain::setOutput(QExtendedAudioFormat format)
{
	mOutputFormat = format;
}

void QCodingChain::detectCoderData()
{
	mInputCoder = mManager->detect(*mInputData);
}

void QCodingChain::detectCoderFile()
{
	mInputCoder = mManager->detect(mInputFilePath);
}

void QCodingChain::run()
{
	//////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Initialize
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	if(mMode == QCodingChain::Unknown)
	{
		return;
	}

	if(mMode != QCodingChain::EncodeFile && mMode != QCodingChain::EncodeData)
	{
		(this->*detectCoder)();
		if(mInputCoder == NULL)
		{
			cout<<"Input file format not supported!"<<endl;
			return;
		}
	}
	if(mMode != QCodingChain::DecodeFile && mMode != QCodingChain::DecodeData)
	{
		mOutputCoder = mManager->coder(mOutputFormat);
		if(mOutputCoder == NULL)
		{
			cout<<"Output file format not supported!"<<endl;
			return;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Initialize mode
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	if(mMode == QCodingChain::ConvertFileToFile || mMode == QCodingChain::ConvertFileToData || mMode == QCodingChain::ConvertDataToFile || mMode == QCodingChain::ConvertDataToData)
	{
		mInput->setNext(&mDecoder);
		mDecoder.setNext(&mEncoder);
		mEncoder.setNext(mOutput);
		mOutputCoder->setFormat(QAudio::AudioOutput, mOutputFormat);
		if(mMode == QCodingChain::ConvertDataToFile || mMode == QCodingChain::ConvertDataToData)
		{
			mInputCoder->setFormat(QAudio::AudioInput, mInputFormat);
		}
	}
	else if(mMode == QCodingChain::DecodeFile || mMode == QCodingChain::DecodeData)
	{
		mInput->setNext(&mDecoder);
		mDecoder.setNext(mOutput);
		if(mMode == QCodingChain::DecodeData)
		{
			mInputCoder->setFormat(QAudio::AudioInput, mInputFormat);
		}
	}
	else if(mMode == QCodingChain::EncodeFile || mMode == QCodingChain::EncodeData)
	{
		mInput->setNext(&mEncoder);
		mEncoder.setNext(mOutput);
		mOutputCoder->setFormat(QAudio::AudioOutput, mOutputFormat);
	}

	mInput->initialize();
	if(mMode != QCodingChain::EncodeFile && mMode != QCodingChain::EncodeData)
	{
		mDecoder.setCoder(mInputCoder);
		mInputCoder->load();
		mDecoder.initialize();
	}
	if(mMode != QCodingChain::DecodeFile && mMode != QCodingChain::DecodeData)
	{
		mEncoder.setCoder(mOutputCoder);
		mOutputCoder->load();
		mEncoder.initialize();
	}
	mOutput->initialize();

	//////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Execute
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	qreal progressedData = 0;
	qint64 totalSize = mInput->size(); 
	static qint32 chunkSize = mInput->chunkSize();
	qreal progress = 0;

	while(mInput->hasData())
	{
		mInput->execute();

		progressedData += chunkSize;
		if(totalSize <= 0)
		{
			progress = 0;
		}
		else
		{
			progress = progressedData / totalSize * 99; // * 99 to first finalize everything before 100% is emitted
		}
		//cout << "Progress: " << progress << "%" << endl;
		emit progressed(progress);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Finalize
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	mInput->finalize();
	if(mMode != QCodingChain::EncodeFile && mMode != QCodingChain::EncodeData)
	{
		mDecoder.finalize();
	}
	if(mMode != QCodingChain::DecodeFile && mMode != QCodingChain::DecodeData)
	{
		mEncoder.finalize();
	}
	mOutput->finalize();

	progress = 100;
	cout << "Progress: " << progress << "%" << endl;
	emit progressed(progress);
}
