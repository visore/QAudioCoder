#include <qcodingchain.h>
#include <QFile>

#define HEADER_SIZE 4096
#define MAXIMUM_HEADER_REQUESTS 100

QCodingChain::QCodingChain()
	: QThread()
{
	mInputFilePath = "";
	mOutputFilePath = "";
	mInput = NULL;
	mOutput = NULL;
	mInputAtEnd = false;
	mIsFinished = true;

	QObject::connect(&mFileInput, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mFileOutput, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mDecoder, SIGNAL(finished()), this, SLOT(checkFinished()));
	QObject::connect(&mEncoder, SIGNAL(finished()), this, SLOT(checkFinished()));
}

bool QCodingChain::isFinished()
{
	return mIsFinished;
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
		mInputCodec = detectCodec(content);

mOutputCodec = mCodecManager.availableCodecs()[1];

		if(mInputCodec == NULL)
		{
			cout<<"File format not supported!"<<endl;
		}
		else
		{
			mBuffer1.clear();
			mBuffer2.clear();
			mBuffer3.clear();

			mBuffer1.connect(mInput, &mDecoder);
			mBuffer2.connect(&mDecoder, &mEncoder);
			mBuffer3.connect(&mEncoder, mOutput);

			QObject::connect(mInput, SIGNAL(atEnd()), this, SLOT(inputFinished()));
			//QObject::connect(mInput, SIGNAL(available(QSampleArray*)), &mDecoder, SLOT(addChunk(QSampleArray*)));
			//QObject::connect(&mDecoder, SIGNAL(requestChunks(int)), mInput, SLOT(readChunks(int)));
			//QObject::connect(&mDecoder, SIGNAL(available(QSampleArray*)), &mEncoder, SLOT(addChunk(QSampleArray*)));
			//QObject::connect(&mEncoder, SIGNAL(available(QSampleArray*)), mOutput, SLOT(addChunk(QSampleArray*)));






			QCodecFormat format;
			format.setSampleSize(16);
			format.setSampleType(QAudioFormat::SignedInt);
			format.setSampleRate(44100);
			format.setChannelCount(2);
			format.setBitrateMode(QCodecFormat::VariableBitrate);
			format.setBitrate(256);

			mOutputCodec->setFormat(QAudio::AudioInput, mInputCodec->format(QAudio::AudioInput));
			mOutputCodec->setFormat(QAudio::AudioOutput, format);

			mDecoder.setCodec(mInputCodec);
			mEncoder.setCodec(mOutputCodec);

			mInputCodec->load();
			mOutputCodec->load();

			cout << "Input Codec: "<<mInputCodec->name().toAscii().data()<<endl;
			cout << "Output Codec: "<<mOutputCodec->name().toAscii().data()<<endl;

			/*QByteArray header;
			mOutputCodec->createHeader(header, content);

			mInput->skipHeader(content.headerSize());
			mOutput->setHeader(header);*/

			mInput->initialize();
			mDecoder.initialize();
			mEncoder.initialize();
			mOutput->initialize();

			mInputAtEnd = false;
			mIsFinished = false;
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
	if(mInputAtEnd && !mIsFinished && !mInput->isRunning() && !mDecoder.isRunning() && !mEncoder.isRunning() && !mOutput->isRunning())
	{
		mInput->finalize();
		mDecoder.finalize();
		mEncoder.finalize();
		mOutput->finalize();

		mInputCodec->unload();
		mOutputCodec->unload();

		cout<<"Finished!!"<<endl;
		mIsFinished = true;
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

	QFile file(mInputFilePath);
	if(!file.open(QIODevice::ReadOnly))
	{
		return NULL;
	}

	content.setFileSize(file.size());
	QByteArray header = file.read(HEADER_SIZE);
	QAbstractCodec::Header result;
	int requests;

	for(int i = 0; i < codecs.size(); ++i)
	{
		requests = 0;
		result = codecs[i]->inspectHeader(header, content);
		while(result == QAbstractCodec::NeedMoreData && requests < MAXIMUM_HEADER_REQUESTS)
		{
			++requests;
			header.append(file.read(HEADER_SIZE));
			result = codecs[i]->inspectHeader(header, content);
		}

		if(result == QAbstractCodec::ValidHeader)
		{
			file.close();
			return codecs[i];
		}
	}
	file.close();
	return NULL;
}
