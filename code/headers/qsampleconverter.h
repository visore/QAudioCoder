#ifndef QSAMPLECONVERTER_H
#define QSAMPLECONVERTER_H

#include <qcodecformat.h>
#include <qsamplechannelconverter.h>
#include <qsamplesizeconverter.h>

class QSampleConverter
{

	public:

		QSampleConverter();
		QSampleConverter(QCodecFormat inputFormat, QCodecFormat outputFormat);
		bool initialize(QCodecFormat inputFormat, QCodecFormat outputFormat);
		void convert(const void *input, void *output, int &samples);

	private:

		QSampleChannelConverter mChannelConverter;
		QSampleSizeConverter mSizeConverter;

		int mChannelSampleSize;
		int mSizeSampleSize;

		qreal mChannelDifference;
		qreal mSizeDifference;

		void convertChannel(const void *input, void *output, int &samples);
		void convertSize(const void *input, void *output, int &samples);

};

#endif
