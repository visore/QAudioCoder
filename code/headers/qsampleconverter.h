#ifndef QSAMPLECONVERTER_H
#define QSAMPLECONVERTER_H

#include <qcodecformat.h>
#include <qsamplechannelconverter.h>
#include <qsamplesizeconverter.h>
#include <qsamplerateconverter.h>

class QSampleConverter
{

	public:

		QSampleConverter();
		QSampleConverter(QCodecFormat inputFormat, QCodecFormat outputFormat);
		bool initialize(QCodecFormat inputFormat, QCodecFormat outputFormat);
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
