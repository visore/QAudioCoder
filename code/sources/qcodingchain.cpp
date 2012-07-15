#include <qcodingchain.h>
#include <QFile>

QCodingChain::QCodingChain()
	: QThread()
{
	mManager = &QAudioManager::instance();
	mInputFormat = NULL;
	mOutputFormat = NULL;
	mInput = NULL;
	mOutput = NULL;
	setMode(QCodingChain::Unknown);
}

QCodingChain::~QCodingChain()
{
	if(!mReferenceInputFormat && mInputFormat != NULL)
	{
		delete mInputFormat;
		mInputFormat = NULL;
	}
	if(mOutputFormat != NULL)
	{
		delete mOutputFormat;
		mOutputFormat = NULL;
	}
}

void QCodingChain::setMode(QCodingChain::Mode mode)
{
	reset();
	mMode = mode;
}

void QCodingChain::reset()
{
	mError = QCoder::NoError;

	if(mInput != NULL)
	{
		mInput->disconnect();
	}
	mDecoder.disconnect();
	mEncoder.disconnect();
	if(mOutput != NULL)
	{
		mOutput->disconnect();
	}

	mInputFilePath = "";
	mInputData = NULL;
	mInput = NULL;
	mOutput = NULL;
	mInputCoder = NULL;
	mOutputCoder = NULL;

	if(!mReferenceInputFormat && mInputFormat != NULL)
	{
		delete mInputFormat;
	}
	if(mOutputFormat != NULL)
	{
		delete mOutputFormat;
	}
	mInputFormat = NULL;
	mOutputFormat = NULL;
	mReferenceInputFormat = false;
}

void QCodingChain::setError(QCoder::Error error)
{
	mError = error;
	if(mInput != NULL)
	{
		mInput->disconnect();
	}
	mDecoder.disconnect();
	mEncoder.disconnect();
	if(mOutput != NULL)
	{
		mOutput->disconnect();
	}

	if(isRunning())
	{
		exit(-1);
	}

	if(mInputCoder != NULL)
	{
		mInputCoder->unload();
	}
	if(mOutputCoder != NULL)
	{
		mOutputCoder->unload();
	}

	if(mError != QCoder::NoError)
	{
		emit failed(mError);
	}
}

void QCodingChain::setInputPath(QString filePath)
{
	mInputFilePath = filePath;
	mFileInput.setFilePath(filePath);
	mInput = &mFileInput;
	detectCoder = &QCodingChain::detectCoderFile;
}

void QCodingChain::setOutputPath(QString filePath)
{
	mFileOutput.setFilePath(filePath);
	mOutput = &mFileOutput;
}

void QCodingChain::setInputData(QByteArray &array)
{
	mInputData = &array;
	mDataInput.setData(array);
	mInput = &mDataInput;
	detectCoder = &QCodingChain::detectCoderData;
}

void QCodingChain::setOutputData(QByteArray &array)
{
	mDataOutput.setData(array);
	mOutput = &mDataOutput;
}

void QCodingChain::setInputFormat(QExtendedAudioFormat *format)
{
	if(!mReferenceInputFormat && mInputFormat != NULL)
	{
		delete mInputFormat;
		mInputFormat = NULL;
	}
	mReferenceInputFormat = true;
	mInputFormat = format;
}

void QCodingChain::setInputFormat(QExtendedAudioFormat &format)
{
	if(!mReferenceInputFormat && mInputFormat != NULL)
	{
		delete mInputFormat;
		mInputFormat = NULL;
	}
	mReferenceInputFormat = false;
	mInputFormat = new QExtendedAudioFormat(format);
}

void QCodingChain::setOutputFormat(QExtendedAudioFormat &format)
{
	if(mOutputFormat != NULL)
	{
		delete mOutputFormat;
		mOutputFormat = NULL;
	}
	mOutputFormat = new QExtendedAudioFormat(format);
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
			QCoder::Error error = mManager->error();
			if(error == QCoder::UnsupportedCodecError)
			{
				setError(QCoder::UnsupportedInputCodecError);
			}
			else if(error == QCoder::UnavailableCodecError)
			{
				setError(QCoder::UnavailableInputCodecError);
			}
			else
			{
				setError(error);
			}
			return;
		}
		else
		{
			QObject::connect(mInputCoder, SIGNAL(failed(QCoder::Error)), this, SLOT(setError(QCoder::Error)), Qt::DirectConnection);
		}
	}
	if(mError != QCoder::NoError) return;

	if(mMode != QCodingChain::DecodeFile && mMode != QCodingChain::DecodeData)
	{
		mOutputCoder = mManager->coder(*mOutputFormat);
		if(mOutputCoder == NULL)
		{
			QCoder::Error error = mManager->error();
			if(error == QCoder::UnsupportedCodecError)
			{
				setError(QCoder::UnsupportedOutputCodecError);
			}
			else if(error == QCoder::UnavailableCodecError)
			{
				setError(QCoder::UnavailableOutputCodecError);
			}
			else
			{
				setError(error);
			}
			return;
		}
		else
		{
			QObject::connect(mOutputCoder, SIGNAL(failed(QCoder::Error)), this, SLOT(setError(QCoder::Error)), Qt::DirectConnection);
		}
	}
	if(mError != QCoder::NoError) return;

	//////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Initialize mode
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	mInput->disconnect();
	mDecoder.disconnect();
	mEncoder.disconnect();
	mOutput->disconnect();
	QObject::connect(mInput, SIGNAL(failed(QCoder::Error)), this, SLOT(setError(QCoder::Error)), Qt::DirectConnection);
	QObject::connect(&mDecoder, SIGNAL(failed(QCoder::Error)), this, SLOT(setError(QCoder::Error)), Qt::DirectConnection);
	QObject::connect(&mEncoder, SIGNAL(failed(QCoder::Error)), this, SLOT(setError(QCoder::Error)), Qt::DirectConnection);
	QObject::connect(mOutput, SIGNAL(failed(QCoder::Error)), this, SLOT(setError(QCoder::Error)), Qt::DirectConnection);

	if(mMode == QCodingChain::ConvertFileToFile || mMode == QCodingChain::ConvertFileToData || mMode == QCodingChain::ConvertDataToFile || mMode == QCodingChain::ConvertDataToData)
	{
		mInput->setNext(&mDecoder);
		mDecoder.setNext(&mEncoder);
		mEncoder.setNext(mOutput);
		mOutputCoder->setFormat(QAudio::AudioOutput, *mOutputFormat);
		if(mMode == QCodingChain::ConvertDataToFile || mMode == QCodingChain::ConvertDataToData)
		{
			mInputCoder->setFormat(QAudio::AudioInput, *mInputFormat);
		}
	}
	else if(mMode == QCodingChain::DecodeFile || mMode == QCodingChain::DecodeData)
	{
		mInput->setNext(&mDecoder);
		mDecoder.setNext(mOutput);
		if(mMode == QCodingChain::DecodeData)
		{
			mInputCoder->setFormat(QAudio::AudioInput, *mInputFormat);
		}
	}
	else if(mMode == QCodingChain::EncodeFile || mMode == QCodingChain::EncodeData)
	{
		mInput->setNext(&mEncoder);
		mEncoder.setNext(mOutput);
		mOutputCoder->setFormat(QAudio::AudioOutput, *mOutputFormat);
	}

	mInput->initialize();
	if(mError != QCoder::NoError) return;

	mOutput->initialize();
	if(mError != QCoder::NoError) return;

	if(mMode != QCodingChain::EncodeFile && mMode != QCodingChain::EncodeData)
	{
		mDecoder.setCoder(mInputCoder);
		mInputCoder->load();
		if(mError != QCoder::NoError) return;
		mDecoder.initialize();
		if(mError != QCoder::NoError) return;
	}
	if(mMode != QCodingChain::DecodeFile && mMode != QCodingChain::DecodeData)
	{
		mEncoder.setCoder(mOutputCoder);
		mOutputCoder->load();
		if(mError != QCoder::NoError) return;
		mEncoder.initialize();
		if(mError != QCoder::NoError) return;
		if(mMode == QCodingChain::EncodeFile || mMode == QCodingChain::EncodeData)
		{
			mOutputCoder->setFormat(QAudio::AudioInput, *mInputFormat);
			mInput->setSampleSize(mInputFormat->sampleSize());
			mEncoder.changeFormat(*mInputFormat);
		}
	}

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
		emit progressed(progress);
		if(mError != QCoder::NoError) return;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Finalize
	//
	//////////////////////////////////////////////////////////////////////////////////////////////

	mInput->finalize();
	if(mError != QCoder::NoError) return;
	if(mMode != QCodingChain::EncodeFile && mMode != QCodingChain::EncodeData)
	{
		if(mMode == QCodingChain::DecodeFile || mMode == QCodingChain::DecodeData)
		{
			*mInputFormat = mInputCoder->format(QAudio::AudioInput);
		}
		mDecoder.finalize();
		if(mError != QCoder::NoError) return;
	}
	if(mMode != QCodingChain::DecodeFile && mMode != QCodingChain::DecodeData)
	{
		mEncoder.finalize();
		if(mError != QCoder::NoError) return;
	}
	mOutput->finalize();

	if(mInputCoder != NULL)
	{
		mInputCoder->unload();
	}
	if(mOutputCoder != NULL)
	{
		mOutputCoder->unload();
	}

	progress = 100;
	emit progressed(progress);
}
