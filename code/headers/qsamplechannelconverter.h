#ifndef QSAMPLECHANNELCONVERTER_H
#define QSAMPLECHANNELCONVERTER_H

#include <qcommon.h>
#include <qextendedaudioformat.h>
#include <qchannelconverter.h>

class QSampleChannelConverter
{

	public:

		QSampleChannelConverter();
		QSampleChannelConverter(int inputChannels, int outputChannels, QExtendedAudioFormat::SampleType sampleType, int sampleSize);
		bool initialize(int inputChannels, int outputChannels, QExtendedAudioFormat::SampleType sampleType, int sampleSize);
		void (*convert)(const void *input, void *output, int samples);

};

#endif
