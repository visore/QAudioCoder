#include <qchannelconverter.h>
#include <qcommon.h>
#include <string.h>

template <typename T>
void QChannelConverter<T>::convertMonoToMono(const void *input, void *output, int samples)
{
	memcpy(output, input, sizeof(T) * samples);
}

template <typename T>
void QChannelConverter<T>::convertStereoToMono(const void *input, void *output, int samples)
{
	T *inputData = (T*) input;
	T *outputData = (T*) output;
	for(int i = 0, j = 0; i < samples; i += 2, ++j)
	{
		outputData[j] = (inputData[i] + inputData[i + 1]) / 2.0;
	}
}

template <typename T>
void QChannelConverter<T>::convertMonoToStereo(const void *input, void *output, int samples)
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
void QChannelConverter<T>::convertStereoToStereo(const void *input, void *output, int samples)
{
	memcpy(output, input, sizeof(T) * samples);
}

template <typename T>
int QChannelConverter<T>::splitChannels(const void *stereo, void *left, void *right, int samples)
{
	T *typedStereo = (T*) stereo;
	T *typedLeft = (T*) left;
	T *typedRight = (T*) right;
	int counter = 0;
	for(int i = 0; i < samples; i += 2)
	{
		typedLeft[counter] = typedStereo[i];
		typedRight[counter] = typedStereo[i + 1];
		++counter;
	}
	return counter;
}

template <typename T>
int QChannelConverter<T>::combineChannels(const void *left, const void *right, void *stereo, int samples)
{
	T *typedStereo = (T*) stereo;
	T *typedLeft = (T*) left;
	T *typedRight = (T*) right;
	int counter = 0;
	for(int i = 0; i < samples; ++i)
	{
		typedStereo[counter++] = typedLeft[i];
		typedStereo[counter++] = typedRight[i];
	}
	return counter;
}

template class QChannelConverter<qbyte8s>;
template class QChannelConverter<qbyte16s>;
template class QChannelConverter<qbyte32s>;
template class QChannelConverter<qbyte8u>;
template class QChannelConverter<qbyte16u>;
template class QChannelConverter<qbyte32u>;
template class QChannelConverter<qfloat>;
template class QChannelConverter<qreal>;
