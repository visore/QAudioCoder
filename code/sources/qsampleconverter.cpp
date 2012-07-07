#include <qsampleconverter.h>

QSampleConverter::QSampleConverter()
{
	mFloatSampleSize = 1;
	mRateSampleSize = 1;
	mSizeSampleSize = 1;
	mChannelSampleSize = 1;

	mFloatDifference = 1;
	mRateDifference = 1;
	mSizeDifference = 1;
	mChannelDifference = 1;
}

QSampleConverter::QSampleConverter(QExtendedAudioFormat inputFormat, QExtendedAudioFormat outputFormat)
{
	QSampleConverter();
	initialize(inputFormat, outputFormat);
}

bool QSampleConverter::initialize(QExtendedAudioFormat inputFormat, QExtendedAudioFormat outputFormat)
{
	mFloatSampleSize = 1;
	mRateSampleSize = 1;
	mSizeSampleSize = 1;
	mChannelSampleSize = 1;

	mFloatDifference = 1;
	mRateDifference = 1;
	mSizeDifference = 1;
	mChannelDifference = 1;

	int floatBits = sizeof(qfloat) * 8;

	int inputSize = inputFormat.sampleSize();
	int outputSize = outputFormat.sampleSize();
	int inputChannels = inputFormat.channelCount();
	int outputChannels = outputFormat.channelCount();
	int inputRate = inputFormat.sampleRate();
	int outputRate = outputFormat.sampleRate();
	QAudio::SampleType inputType = QAudio::toAudioSampleType(inputFormat.sampleType());
	QAudio::SampleType outputType = QAudio::toAudioSampleType(outputFormat.sampleType());

	if(inputFormat.sampleType() == QAudioFormat::Float)
	{
		inputSize = 32;
	}
	if(outputFormat.sampleType() == QAudioFormat::Float)
	{
		outputSize = 32;
	}

	if(mFloatConverter.initialize(inputSize, inputType, floatBits, QAudio::Float))
	{
		mFloatSampleSize = inputSize / 8;
		mFloatDifference = floatBits / qreal(inputSize);
	}
	else
	{
		return false;
	}

	if(mRateConverter.initialize(inputChannels, inputRate, outputRate))
	{
		mRateSampleSize = floatBits / 8;
		mRateDifference = outputRate / qreal(inputRate);
	}
	else
	{
		return false;
	}

	if(mSizeConverter.initialize(floatBits, QAudio::Float, outputSize, outputType))
	{
		mSizeSampleSize = floatBits / 8;
		mSizeDifference = outputSize / qreal(floatBits);
	}
	else
	{
		return false;
	}

	if(mChannelConverter.initialize(inputChannels, outputChannels, outputType, outputSize))
	{
		mChannelSampleSize = outputSize / 8;
		mChannelDifference = outputChannels / qreal(inputChannels);
	}
	else
	{
		return false;
	}

	return true;
}

void* QSampleConverter::convert(const void *input, int &samples, int &size)
{
	size = int(samples * mFloatDifference * mFloatSampleSize);
	qbyte *floatData = new qbyte[size];
	mFloatConverter.convert(input, floatData, samples);

	size = int(samples * mRateDifference * mRateSampleSize);
	qbyte *rateData = new qbyte[size];
	mRateConverter.convert((qfloat*) floatData, (qfloat*) rateData, samples);
	samples *= mRateDifference;
	delete [] floatData;

	size = int(samples * mSizeDifference * mSizeSampleSize);
	qbyte *sizeData = new qbyte[size];
	mSizeConverter.convert(rateData, sizeData, samples);
	delete [] rateData;

	size = int(samples * mChannelDifference * mChannelSampleSize);
	qbyte *channelData = new qbyte[size];
	mChannelConverter.convert(sizeData, channelData, samples);
	samples *= mChannelDifference;
	delete [] sizeData;

	return channelData;
}
