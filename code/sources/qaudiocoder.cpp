#include <qaudiocoder.h>
#include <QFile>

#define FRAME_SIZE 8192

QAudioCoderThread::QAudioCoderThread()
	: QThread()
{
	mCodec = NULL;

mInputFormat.setChannelCount(2);
mInputFormat.setSampleSize(16);
mInputFormat.setSampleRate(44100);

	mInputData = NULL;
	mOutputData = NULL;
	mInputPath = "";
	mOutputPath = "";
	mMode = QAudioCoderThread::Undefinied;
	mError = QAudioCoder::NoError;
	mSampleDifference = 0;
}

void QAudioCoderThread::setCodec(QAbstractCodec *codec)
{
	mCodec = codec;
}

void QAudioCoderThread::setData(const QString inputFilePath, const QString outputFilePath)
{
	mInputPath = inputFilePath;
	mOutputPath = outputFilePath;
	mMode = QAudioCoderThread::FileToFile;
}

QCodecFormat QAudioCoderThread::format(QAudio::Mode mode)
{
	if(mode == QAudio::AudioInput)
	{
		return mInputFormat;
	}
	else if(mode == QAudio::AudioOutput)
	{
		return mOutputFormat;
	}
	return QCodecFormat();
}

void QAudioCoderThread::setFormat(QAudio::Mode mode, QCodecFormat format)
{
	if(mode == QAudio::AudioInput)
	{
		mInputFormat = format;
	}
	else if(mode == QAudio::AudioOutput)
	{
		mOutputFormat = format;
	}
}

QAudioCoder::Error QAudioCoderThread::error()
{
	return mError;
}

void QAudioCoderThread::run()
{
	if(mCodec != NULL)
	{
		mCodec->load();

		mError = QAudioCoder::NoError;
		mCodec->setFormat(QAudio::AudioInput, mInputFormat);
		mCodec->setFormat(QAudio::AudioOutput, mOutputFormat);
		if(mInputFormat.sampleSize() == 8)
		{
			encode = &QAudioCoderThread::encode8;
			mSampleDifference = 1;
		}
		else if(mInputFormat.sampleSize() == 16)
		{
			encode = &QAudioCoderThread::encode16;
			mSampleDifference = 2;
		}
		else if(mInputFormat.sampleSize() == 32)
		{
			encode = &QAudioCoderThread::encode32;
			mSampleDifference = 4;
		}

		mCodec->initialize();

		if(mMode = QAudioCoderThread::FileToFile)
		{
			fileToFile();
		}

		mCodec->finalize();
		mCodec->unload();
	}
}

void QAudioCoderThread::fileToFile()
{
	QFile inputFile(mInputPath);
	if(!inputFile.exists() || !inputFile.open(QIODevice::ReadOnly))
	{
		setError(QAudioCoder::InputFileError);
		return;
	}

	QFile outputFile(mOutputPath);
	if(!outputFile.open(QIODevice::WriteOnly))
	{
		setError(QAudioCoder::OutputFileError);
		inputFile.close();
		return;
	}

	/*QByteArray samples = inputFile.read(FRAME_SIZE);
	QByteArray outputData;
	outputData.resize(FRAME_SIZE/2);*/

	int readSzie = FRAME_SIZE * mSampleDifference;
	char samples[readSzie];
	char outputData[FRAME_SIZE];
	int sampleSize = 0;
	int outputSize = 0;

	while(sampleSize = inputFile.read((char*) samples, readSzie))
	{
		outputSize = (this->*encode)(samples, sampleSize / mSampleDifference, outputData, FRAME_SIZE);
		if(outputFile.write((char*) outputData, outputSize) == 0)
		{
			break;
		}
	}

	inputFile.close();
	outputFile.close();
}

int QAudioCoderThread::encode8(const char input[], int inputSize, char output[], int outputSize)
{
	return mCodec->encode((const qint8*) input, inputSize, (qint8*) output, outputSize);
}

int QAudioCoderThread::encode16(const char input[], int inputSize, char output[], int outputSize)
{
	return mCodec->encode((const qint16*) input, inputSize, (qint8*) output, outputSize);
}

int QAudioCoderThread::encode32(const char input[], int inputSize, char output[], int outputSize)
{
	return mCodec->encode((const qint16*) input, inputSize, (qint8*) output, outputSize);
}

void QAudioCoderThread::setError(QAudioCoder::Error error)
{
	mError = error;
}

QAudioCoder::QAudioCoder()
	: QObject()
{
	mThread = new QAudioCoderThread();
	QObject::connect(mThread, SIGNAL(finished()), this, SIGNAL(finished()));
}

QAudioCoder::~QAudioCoder()
{
	delete mThread;
	mThread = NULL;
}

void QAudioCoder::encode(const QByteArray *data, const QString filePath)
{

}

void QAudioCoder::convert(const QString inputFilePath, const QString outputFilePath, QCodecFormat outputFormat)
{
	mThread->setFormat(QAudio::AudioOutput, outputFormat);
	mThread->setData(inputFilePath, outputFilePath);

	QList<QAbstractCodec*> codecs = mCodecManager.availableCodecs();
	if(codecs.size()==0)
	{
		cout<<"No codecs available!"<<endl;
	}
	else
	{
		mThread->setCodec(codecs[0]);
		mThread->start();
		while(!mThread->isFinished());
	}
}
