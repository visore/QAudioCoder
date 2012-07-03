#include <qsampleconverter.h>

QSampleConverter::QSampleConverter()
{
	mChannelDifference = 1;
}

QSampleConverter::QSampleConverter(QCodecFormat inputFormat, QCodecFormat outputFormat)
{
	QSampleConverter();
	setFormat(inputFormat, outputFormat);
}

void QSampleConverter::setFormat(QCodecFormat inputFormat, QCodecFormat outputFormat)
{
	mChannelConverter.initialize(inputFormat.channelCount(), outputFormat.channelCount(), inputFormat.sampleType(), inputFormat.sampleSize());
	mChannelDifference = outputFormat.channelCount() / inputFormat.channelCount();

}

void QSampleConverter::convert8s(const void* input, void* output, int &samples)
{
	qbyte8s data[samples * mChannelDifference];
	mChannelConverter.convert(input, data, samples);
}

void QSampleConverter::convert16s(const void* input, void* output, int samples)
{
	qbyte16s data[samples * mChannelDifference];
	mChannelConverter.convert(input, data, samples);
}

void QSampleConverter::convert32s(const void* input, void* output, int samples)
{

}

void QSampleConverter::convert8u(const void* input, void* output, int samples)
{

}

void QSampleConverter::convert16u(const void* input, void* output, int samples)
{

}

void QSampleConverter::convert32u(const void* input, void* output, int samples)
{

}

void QSampleConverter::convertFloat(const void* input, void* output, int samples)
{

}

void QSampleConverter::convertReal(const void* input, void* output, int samples)
{

}
