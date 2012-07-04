#ifndef QSAMPLERATECONVERTER_H
#define QSAMPLERATECONVERTER_H

#include <qcommon.h>

class QSampleRateConverter
{

	public:

		enum Mode
		{
			HighQuality = 0,
			LowQuality = 1
		};

		QSampleRateConverter();
		QSampleRateConverter(short channels, qreal inputRate, qreal outputRate, QSampleRateConverter::Mode mode = QSampleRateConverter::HighQuality);
		~QSampleRateConverter();
		bool initialize(short channels, qreal inputRate, qreal outputRate, QSampleRateConverter::Mode mode = QSampleRateConverter::HighQuality);
		void convert(const qfloat *input, qfloat *output, int samples);

	private:

		void (QSampleRateConverter::*convertPointer)(const qfloat *input, qfloat *output, int samples);
		void copy(const qfloat *input, qfloat *output, int samples);
		void resample(const qfloat *input, qfloat *output, int samples);

	private:

		void *mResampler;
		qreal mFactor;

};

#endif
