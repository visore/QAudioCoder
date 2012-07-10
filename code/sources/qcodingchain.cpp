#include <qcodingchain.h>
#include <QFile>

QCodingChain::QCodingChain()
	: QThread()
{
	mManager = &QAudioManager::instance();
	mInputFilePath = "";
	mOutputFilePath = "";
	mInput = NULL;
	mOutput = NULL;
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
		mInputCoder = mManager->detect(mInputFilePath);
		mOutputCoder = mManager->coder(mOutputFormat);

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

			mInput->setNext(&mDecoder);
			mDecoder.setNext(&mEncoder);
			mEncoder.setNext(mOutput);

			mOutputCoder->setFormat(QAudio::AudioOutput, mOutputFormat);
			mDecoder.setCoder(mInputCoder);
			mEncoder.setCoder(mOutputCoder);
			mInputCoder->load();
			mOutputCoder->load();

			cout << "Input Coder: "<<mInputCoder->name().toAscii().data()<<endl;
			cout << "Output Coder: "<<mOutputCoder->name().toAscii().data()<<endl;

			mInput->initialize();
			mDecoder.initialize();
			mEncoder.initialize();
			mOutput->initialize();

			while(mInput->hasData())
			{
				mInput->execute();
			}
			cout<<"lsat things"<<endl;
			mInput->finalize();
			mDecoder.finalize();
			mEncoder.finalize();
			mOutput->setHeader(mOutputCoder->header());
			mOutput->finalize();

			cout << "Finished"<<endl;
		}
	}
}
