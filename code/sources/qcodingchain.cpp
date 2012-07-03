#include <qcodingchain.h>

QCodingChain::QCodingChain()
	: QThread()
{
	mInput = NULL;
	mOutput = NULL;
	mInputAtEnd = false;

	QObject::connect(&mFileInput, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mFileOutput, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mDecoder, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mEncoder, SIGNAL(finished()), this, SLOT(checkFinished()));
}

void QCodingChain::setInputFilePath(QString filePath)
{
	mFileInput.setFilePath(filePath);
	mInput = &mFileInput;
}

void QCodingChain::setOutputFilePath(QString filePath)
{
	mFileOutput.setFilePath(filePath);
	mOutput = &mFileOutput;
}


void QCodingChain::run()
{
	if(mInput != NULL && mOutput != NULL)
	{
		QList<QAbstractCodec*> codecs = mCodecManager.availableCodecs();
		if(codecs.size()!=1)
		{
			cout<<"No enough codecs available! ("<<codecs.size()<<" available)"<<endl;
		}
		else
		{
			QObject::connect(mInput, SIGNAL(atEnd()), this, SLOT(inputFinished()));
			QObject::connect(mInput, SIGNAL(available(QAudioChunk*)), &mDecoder, SLOT(addChunk(QAudioChunk*)));
			QObject::connect(&mDecoder, SIGNAL(available(QAudioChunk*)), &mEncoder, SLOT(addChunk(QAudioChunk*)));
			QObject::connect(&mDecoder, SIGNAL(available(QAudioChunk*)), mInput, SLOT(start()));
			QObject::connect(&mEncoder, SIGNAL(available(QAudioChunk*)), mOutput, SLOT(addChunk(QAudioChunk*)));

			QCodecFormat format;
			format.setSampleSize(16);
			format.setSampleType(QAudioFormat::SignedInt);
			format.setSampleRate(44100);
			format.setChannelCount(2);

			codecs[0]->setFormat(QAudio::AudioInput, format);
			format.setSampleSize(32);
			codecs[0]->setFormat(QAudio::AudioOutput, format);

			mDecoder.setCodec(codecs[0]);
			mEncoder.setCodec(codecs[0]);

			mInput->initialize();
			mDecoder.initialize();
			mEncoder.initialize();
			mOutput->initialize();

			mInputAtEnd = false;
			mInput->start();
		}
	}
}

void QCodingChain::inputFinished()
{
	mInputAtEnd = true;
}

void QCodingChain::checkFinished()
{
	if(mInputAtEnd && !mInput->isRunning() && !mDecoder.isRunning() && !mEncoder.isRunning() && !mOutput->isRunning())
	{
		mInput->finalize();
		mDecoder.finalize();
		mEncoder.finalize();
		mOutput->finalize();
		emit finished();
	}
}
