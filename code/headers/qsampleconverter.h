#ifndef QSAMPLECONVERTER_H
#define QSAMPLECONVERTER_H

#include <qextendedaudioformat.h>
#include <qsamplechannelconverter.h>
#include <qsamplesizeconverter.h>
#include <qsamplerateconverter.h>

class QSampleConverter
{

	public:

		QSampleConverter();
		QSampleConverter(QExtendedAudioFormat inputFormat, QExtendedAudioFormat outputFormat);
		bool initialize(QExtendedAudioFormat inputFormat, QExtendedAudioFormat outputFormat);
		void* convert(const void *input, int &samples, int &size);

	private:

		QSampleSizeConverter mFloatConverter;
		QSampleRateConverter mRateConverter;
		QSampleSizeConverter mSizeConverter;
		QSampleChannelConverter mChannelConverter;

		int mFloatSampleSize;
		int mRateSampleSize;
		int mSizeSampleSize;
		int mChannelSampleSize;

		qreal mFloatDifference;
		qreal mRateDifference;
		qreal mSizeDifference;
		qreal mChannelDifference;

};

#endif
