#include <qcodecexecutor.h>
#include <QFile>

#define FRAME_SIZE 8192

QCodecExecutor::QCodecExecutor()
	: QThread()
{
	mCodec = NULL;
/*
mInputFormat.setChannelCount(2);
mInputFormat.setSampleSize(16);
mInputFormat.setSampleRate(44100);*/

	mError = QCodecExecutor::NoError;
}

void QCodecExecutor::setCodec(QAbstractCodec *codec)
{
	mCodec = codec;
}

QCodecFormat QCodecExecutor::format(QAudio::Mode mode)
{
	return mFormat;
}

void QCodecExecutor::setFormat(QAudio::Mode mode, QCodecFormat format)
{
	mFormat = format;
}

QCodecExecutor::Error QCodecExecutor::error()
{
	return mError;
}

void QCodecExecutor::setError(QCodecExecutor::Error error)
{
	mError = error;
}

/**********************************************************

File Executor

**********************************************************/

QCodecFileExecutor::QCodecFileExecutor()
	: QCodecExecutor()
{
	mFilePath = "";
}

void QCodecFileExecutor::setFilePath(QString filePath)
{
	mFilePath = filePath;
}

QString QCodecFileExecutor::filePath()
{
	return mFilePath;
}

void QFileEncoder::run()
{

}

void QFileEncoder::encode8(char *data, int size)
{

}

void QFileEncoder::encode16(char *data, int size)
{

}

void QFileEncoder::encode32(char *data, int size)
{

}

void QFileDecoder::run()
{

}

























/*
void QCodecExecutor::run()
{
	if(mCodec != NULL)
	{
		mCodec->load();

		mError = QCodecExecutor::NoError;
		mCodec->setFormat(QAudio::AudioInput, mInputFormat);
		mCodec->setFormat(QAudio::AudioOutput, mOutputFormat);
		if(mInputFormat.sampleSize() == 8)
		{
			encode = &QCodecExecutor::encode8;
			mSampleDifference = 1;
		}
		else if(mInputFormat.sampleSize() == 16)
		{
			encode = &QCodecExecutor::encode16;
			mSampleDifference = 2;
		}
		else if(mInputFormat.sampleSize() == 32)
		{
			encode = &QCodecExecutor::encode32;
			mSampleDifference = 4;
		}

		mCodec->initialize();

		if(mMode = QCodecExecutor::FileToFile)
		{
			fileToFile();
		}

		mCodec->finalize();
		mCodec->unload();
	}
}

void QCodecExecutor::fileToFile()
{
	QFile inputFile(mInputPath);
	if(!inputFile.exists() || !inputFile.open(QIODevice::ReadOnly))
	{
		setError(QCodecExecutor::InputFileError);
		return;
	}

	QFile outputFile(mOutputPath);
	if(!outputFile.open(QIODevice::WriteOnly))
	{
		setError(QCodecExecutor::OutputFileError);
		inputFile.close();
		return;
	}

	int readSzie = FRAME_SIZE * mSampleDifference;
	char samples[readSzie];
	int sampleSize = 0;

	do
	{
		sampleSize = inputFile.read((char*) samples, readSzie);
	}
	while((this->*encode)(samples, sampleSize / mSampleDifference) != 0);

	inputFile.close();
	outputFile.close();
}

int QCodecExecutor::encode8(const char input[], int inputSize)
{
	return mCodec->encode((const qint8*) input, inputSize);
}

int QCodecExecutor::encode16(const char input[], int inputSize)
{
	return mCodec->encode((const qint16*) input, inputSize);
}

int QCodecExecutor::encode32(const char input[], int inputSize)
{
	return mCodec->encode((const qint32*) input, inputSize);
}*/
