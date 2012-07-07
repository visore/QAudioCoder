#ifndef QCHANNELCONVERTER_H
#define QCHANNELCONVERTER_H

template <typename T>
class QChannelConverter
{

	public:

		static void convertMonoToMono(const void *input, void *output, int samples);
		static void convertStereoToMono(const void *input, void *output, int samples);

		static void convertMonoToStereo(const void *input, void *output, int samples);
		static void convertStereoToStereo(const void *input, void *output, int samples);

		static int splitChannels(const void *stereo, void *left, void *right, int samples);
		static int combineChannels(const void *left, const void *right, void *stereo, int samples);
	
};

#endif
