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

	if(inputFormat.sampleType() == QAudioFormat::Float)
	{
		inputSize = 32;
	}
	if(outputFormat.sampleType() == QAudioFormat::Float)
	{
		outputSize = 32;
	}

	if(mChannelConverter.initialize(inputChannels, outputChannels, inputFormat.sampleType(), inputSize))
	{
		mChannelSampleSize = inputSize / 8;
		mChannelDifference = outputChannels / qreal(inputChannels);
	}
	else
	{
		return false;
	}

	if(mSizeConverter.initialize(inputSize, QAudio::toAudioSampleType(inputFormat.sampleType()), outputSize, QAudio::toAudioSampleType(outputFormat.sampleType())))
	{
		mSizeSampleSize = outputSize / 8;
		mSizeDifference = outputSize / qreal(inputSize);
	}
	else
	{
		return false;
	}

	return true;
}

void QSampleConverter::convert(const void *input, void *output, int &samples)
{	
	qbyte *channelData = new qbyte[int(samples * mChannelDifference * mChannelSampleSize)];
	mChannelConverter.convert(input, channelData, samples);
	//samples *= mChannelSampleSize;

	/*qbyte *sizeData = new qbyte[int(samples * mSizeDifference * mSizeSampleSize)];
	mSizeConverter.convert(channelData, sizeData, samples);
	delete [] channelData;*/

	output = channelData;// sizeData;
}
