#ifndef QSAMPLECHANNELCONVERTER_H
#define QSAMPLECHANNELCONVERTER_H

#include <qcommon.h>
#include <qcodecformat.h>

template <typename T>
class QSampleChunkChannelConverter
{

	public:

		static void convert1To1(const void *input, void *output, int samples);
		static void convert2To1(const void *input, void *output, int samples);

		static void convert1To2(const void *input, void *output, int samples);
		static void convert2To2(const void *input, void *output, int samples);
	
};

class QSampleChannelConverter
{

	public:

		QSampleChannelConverter();
		QSampleChannelConverter(int inputChannels, int outputChannels, QAudio::SampleType sampleType, int sampleSize);
		bool initialize(int inputChannels, int outputChannels, QAudio::SampleType sampleType, int sampleSize);
		void (*convert)(const void *input, void *output, int samples);

	private:

	
};

#endif
