#include <qcodingchain.h>
#include <QFile>
#include <qaudiomanager.h>

QCodingChain::QCodingChain()
	: QThread()
{
	mInputFilePath = "";
	mOutputFilePath = "";
	mInput = NULL;
	mOutput = NULL;
	mInputAtEnd = false;
	mIsFinished = false;
	QObject::connect(&mFileInput, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mFileOutput, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mDecoder, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mEncoder, SIGNAL(finished()), this, SLOT(checkFinished()));
}

void QCodingChain::setInputFilePath(QString filePath)
{
	mInputFilePath = filePath;
	mFileInput.setFilePath(filePath);
	mInput = &mFileInput;
}

void QCodingChain::setOutputFilePath(QString filePath)
{
	mOutputFilePath = filePath;
	mFileOutput.setFilePath(filePath);
	mOutput = &mFileOutput;
}

void QCodingChain::setOutputFormat(QExtendedAudioFormat format)
{
	mOutputFormat = format;
}

void QCodingChain::run()
{
	if(mInput != NULL && mOutput != NULL)
	{
		QAudioManager manager = QAudioManager::instance();

		QAudioInfo content;
		mInputCoder = manager.detect(mInputFilePath);
		mOutputCoder = manager.coder(mOutputFormat);

		if(mInputCoder == NULL)
		{
			cout<<"Input file format not supported!"<<endl;
		}
		else if(mOutputCoder == NULL)
		{
			cout<<"Output file format not supported!"<<endl;
		}
		else
		{
			mBuffer1.clear();
			mBuffer2.clear();
			mBuffer3.clear();

			mBuffer1.connect(mInput, &mDecoder);
			mBuffer2.connect(&mDecoder, &mEncoder);
			mBuffer3.connect(&mEncoder, mOutput);

			//QObject::connect(mInput, SIGNAL(atEnd()), this, SLOT(inputFinished()));

			mOutputCoder->setFormat(QAudio::AudioInput, mInputCoder->format(QAudio::AudioInput));
			mOutputCoder->setFormat(QAudio::AudioOutput, mOutputFormat);

			mDecoder.setCoder(mInputCoder);
			mEncoder.setCoder(mOutputCoder);

			mInputCoder->load();
			mOutputCoder->load();

			cout << "Input Coder: "<<mInputCoder->name().toAscii().data()<<endl;
			cout << "Output Coder: "<<mOutputCoder->name().toAscii().data()<<endl;

			QByteArray header;
cout<<"Sam: "<<content.samples()<<" "<<21026304<<endl;
			//mOutputCoder->createHeader(header, content);

			//mInput->skipHeader(content.headerSize());
			//mOutput->setHeader(header);

		/*	mInput->initialize();
			mDecoder.initialize();
			mEncoder.initialize();
			mOutput->initialize();*/

			mInputAtEnd = false;
			mIsFinished = false;

			mInput->start();
		}
	}
}

void QCodingChain::inputFinished()
{
	mInputAtEnd = true;
	checkFinished();
}

void QCodingChain::checkFinished()
{
	if(mInputAtEnd && !mIsFinished && !mInput->isRunning() && !mDecoder.isRunning() && !mEncoder.isRunning() && !mOutput->isRunning())
	{
		mIsFinished = true;

		mInput->finalize();
		mDecoder.finalize();
		mEncoder.finalize();
		mOutput->finalize();

		mInputCoder->unload();
		mOutputCoder->unload();

			mBuffer1.clear();
			mBuffer2.clear();
			mBuffer3.clear();

		cout<<"Finished!!"<<endl;
		
		emit finished();
//start();
	}
}
