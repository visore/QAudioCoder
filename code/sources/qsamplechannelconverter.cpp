#include <qsamplechannelconverter.h>

template <typename T>
void QSampleChunkChannelConverter<T>::convert1To1(const void *input, void *output, int samples)
{
	memcpy(output, input, sizeof(T) * samples);
}

template <typename T>
void QSampleChunkChannelConverter<T>::convert2To1(const void *input, void *output, int samples)
{
	T *inputData = (T*) input;
	T *outputData = (T*) output;
	for(int i = 0, j = 0; i < samples; i += 2, ++j)
	{
		outputData[j] = (inputData[i] + inputData[i + 1]) / 2.0;
	}
}

template <typename T>
void QSampleChunkChannelConverter<T>::convert1To2(const void *input, void *output, int samples)
{
	T *inputData = (T*) input;
	T *outputData = (T*) output;
	for(int i = 0, j = 0; i < samples; ++i, j += 2)
	{
		outputData[j] = inputData[i];
		outputData[j + 1] = inputData[i];
	}
}

template <typename T>
void QSampleChunkChannelConverter<T>::convert2To2(const void *input, void *output, int samples)
{
	memcpy(output, input, sizeof(T) * samples);
}

template class QSampleChunkChannelConverter<qbyte8s>;
template class QSampleChunkChannelConverter<qbyte16s>;
template class QSampleChunkChannelConverter<qbyte32s>;
template class QSampleChunkChannelConverter<qbyte8u>;
template class QSampleChunkChannelConverter<qbyte16u>;
template class QSampleChunkChannelConverter<qbyte32u>;
template class QSampleChunkChannelConverter<qfloat>;
template class QSampleChunkChannelConverter<qreal>;

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
				convert = &QSampleChunkChannelConverter<qfloat>::convert1To1;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QSampleChunkChannelConverter<qreal>::convert1To1;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8s>::convert1To1;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16s>::convert1To1;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32s>::convert1To1;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8u>::convert1To1;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16u>::convert1To1;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32u>::convert1To1;
			}
		}
		else if(outputChannels == 2)
		{
			if(sampleType == QAudio::Float)
			{
				convert = &QSampleChunkChannelConverter<qfloat>::convert1To2;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QSampleChunkChannelConverter<qreal>::convert1To2;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8s>::convert1To2;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16s>::convert1To2;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32s>::convert1To2;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8u>::convert1To2;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16u>::convert1To2;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32u>::convert1To2;
			}
		}
	}
	else if(inputChannels == 2)
	{
		if(outputChannels == 1)
		{
			if(sampleType == QAudio::Float)
			{
				convert = &QSampleChunkChannelConverter<qfloat>::convert2To1;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QSampleChunkChannelConverter<qreal>::convert2To1;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8s>::convert2To1;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16s>::convert2To1;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32s>::convert2To1;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8u>::convert2To1;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16u>::convert2To1;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32u>::convert2To1;
			}
		}
		else if(outputChannels == 2)
		{
			if(sampleType == QAudio::Float)
			{
				convert = &QSampleChunkChannelConverter<qfloat>::convert2To2;
			}
			else if(sampleType == QAudio::Real)
			{
				convert = &QSampleChunkChannelConverter<qreal>::convert2To2;
			}
			else if(sampleType == QAudio::SignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8s>::convert2To2;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16s>::convert2To2;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32s>::convert2To2;
			}
			else if(sampleType == QAudio::UnSignedInt)
			{
				if(sampleSize == 8) convert = &QSampleChunkChannelConverter<qbyte8u>::convert2To2;
				else if(sampleSize == 16) convert = &QSampleChunkChannelConverter<qbyte16u>::convert2To2;
				else if(sampleSize == 32) convert = &QSampleChunkChannelConverter<qbyte32u>::convert2To2;
			}
		}
	}

	return convert != NULL;
}
