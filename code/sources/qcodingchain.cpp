#include <qcodingchain.h>
#include <QFile>

#define HEADER_SIZE 4096

QCodingChain::QCodingChain()
	: QThread()
{
	mInputFilePath = "";
	mOutputFilePath = "";
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


void QCodingChain::run()
{
	if(mInput != NULL && mOutput != NULL)
	{
		QCodecContent content;
		QAbstractCodec *codec = detectCodec(content);
		if(codec == NULL)
		{
			cout<<"File format not supported!"<<endl;
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
			format.setChannelCount(1);

			
			codec->setFormat(QAudio::AudioOutput, format);

			mDecoder.setCodec(codec);
			mEncoder.setCodec(codec);

			QByteArray header;
			codec->createHeader(header, content);
cout<<"header size: "<<header.size()<<endl;

			mInput->skipHeader(content.headerSize());
			mOutput->setHeader(header);

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
		cout<<"Finished!!"<<endl;
		emit finished();
	}
}

QAbstractCodec* QCodingChain::detectCodec(QCodecContent &content)
{
	QList<QAbstractCodec*> codecs = mCodecManager.availableCodecs();
	if(codecs.size() == 0)
	{
		return NULL;
	}

	QCodecFormat format;

	QFile file(mInputFilePath);
	if(!file.open(QIODevice::ReadOnly))
	{
		return NULL;
	}

	content.setFileSize(file.size());
	QByteArray header = file.read(HEADER_SIZE);
	file.close();

	for(int i = 0; i < codecs.size(); ++i)
	{
		if(codecs[i]->inspectHeader(header, format, content))
		{
			cout << "Codec found: "<<codecs[i]->name().toAscii().data()<<endl;
			codecs[i]->setFormat(QAudio::AudioInput, format);
			return codecs[i];
		}
	}
	return NULL;
}
