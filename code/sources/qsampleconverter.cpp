#include <qsampleconverter.h>

#include <iostream>
using namespace std;

QSampleConverter::QSampleConverter()
{
	mChannelSampleSize = 1;
	mSizeSampleSize = 1;
	mChannelDifference = 1;
	mSizeDifference = 1;
}

QSampleConverter::QSampleConverter(QCodecFormat inputFormat, QCodecFormat outputFormat)
{
	QSampleConverter();
	initialize(inputFormat, outputFormat);
}

bool QSampleConverter::initialize(QCodecFormat inputFormat, QCodecFormat outputFormat)
{
	mChannelDifference = 1;
	mSizeDifference = 1;
	mChannelSampleSize = 1;
	mSizeSampleSize = 1;

	int inputSize = inputFormat.sampleSize();
	int outputSize = outputFormat.sampleSize();
	int inputChannels = inputFormat.channelCount();
	int outputChannels = outputFormat.channelCount();
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

	if(mChannelConverter.initialize(inputChannels, outputChannels, inputType, inputSize))
	{
		mChannelSampleSize = inputSize / 8;
		mChannelDifference = outputChannels / qreal(inputChannels);
	}
	else
	{
		return false;
	}

	if(mSizeConverter.initialize(inputSize, inputType, outputSize, outputType))
	{
		mSizeSampleSize = inputSize / 8;
		mSizeDifference = outputSize / qreal(inputSize);
	}
	else
	{
		return false;
	}

	return true;
}
void* QSampleConverter::convert(const void *input, int &samples, int &size)
{
	size = int(samples * mChannelDifference * mChannelSampleSize);
	qbyte *channelData = new qbyte[size];
	mChannelConverter.convert(input, channelData, samples);
	samples *= mChannelDifference;

	size = int(samples * mSizeDifference * mSizeSampleSize);
	qbyte *sizeData = new qbyte[size];
	mSizeConverter.convert(channelData, sizeData, samples);
	delete [] channelData;

	return sizeData;
}
