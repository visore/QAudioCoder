#include <qsamplechannelconverter.h>

QSampleChannelConverter::QSampleChannelConverter()
{
	convert = NULL;
}

QSampleChannelConverter::QSampleChannelConverter(int inputChannels, int outputChannels, QAudio::SampleType sampleType, int sampleSize)
{
	QSampleChannelConverter();
	initialize(inputChannels, outputChannels, sampleType, sampleSize);
}

bool QSampleChannelConverter::initialize(int inputChannels, int outputChannels, QAudio::SampleType sampleType, int sampleSize)
{
	convert = NULL;

	if(inputChannels == 1)
	{
		if(outputChannels == 1)
		{
			if(sampleType == QAudio::Float)
			{
				convert = &QChannelConverter<qfloat>::convertMonoToMono;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QChannelConverter<qreal>::convertMonoToMono;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8s>::convertMonoToMono;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16s>::convertMonoToMono;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32s>::convertMonoToMono;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8u>::convertMonoToMono;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16u>::convertMonoToMono;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32u>::convertMonoToMono;
			}
		}
		else if(outputChannels == 2)
		{
			if(sampleType == QAudio::Float)
			{
				convert = &QChannelConverter<qfloat>::convertMonoToStereo;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QChannelConverter<qreal>::convertMonoToStereo;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8s>::convertMonoToStereo;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16s>::convertMonoToStereo;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32s>::convertMonoToStereo;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8u>::convertMonoToStereo;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16u>::convertMonoToStereo;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32u>::convertMonoToStereo;
			}
		}
	}
	else if(inputChannels == 2)
	{
		if(outputChannels == 1)
		{
			if(sampleType == QAudio::Float)
			{
				convert = &QChannelConverter<qfloat>::convertStereoToMono;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QChannelConverter<qreal>::convertStereoToMono;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8s>::convertStereoToMono;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16s>::convertStereoToMono;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32s>::convertStereoToMono;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8u>::convertStereoToMono;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16u>::convertStereoToMono;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32u>::convertStereoToMono;
			}
		}
		else if(outputChannels == 2)
		{
			if(sampleType == QAudio::Float)
			{
				convert = &QChannelConverter<qfloat>::convertStereoToStereo;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QChannelConverter<qreal>::convertStereoToStereo;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8s>::convertStereoToStereo;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16s>::convertStereoToStereo;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32s>::convertStereoToStereo;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QChannelConverter<qbyte8u>::convertStereoToStereo;
				else if(sampleSize == 16) convert = &QChannelConverter<qbyte16u>::convertStereoToStereo;
				else if(sampleSize == 32) convert = &QChannelConverter<qbyte32u>::convertStereoToStereo;
			}
		}
	}

	return convert != NULL;
}
