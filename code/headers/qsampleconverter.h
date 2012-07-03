#ifndef QSAMPLECONVERTER_H
#define QSAMPLECONVERTER_H

#include <qcodecformat.h>
#include <qsamplechannelconverter.h>

class QSampleConverter
{

	public:

		QSampleConverter();
		QSampleConverter(QCodecFormat inputFormat, QCodecFormat outputFormat);
		void setFormat(QCodecFormat inputFormat, QCodecFormat outputFormat);

		void (QSampleConverter::*convert)(const void *input, const void *output, int &samples);

	private:

		QSampleChannelConverter mChannelConverter;
		int mChannelDifference;

		void convert8s(const void* input, void* output, int &samples);
		void convert16s(const void* input, void* output, int samples);
		void convert32s(const void* input, void* output, int samples);
		void convert8u(const void* input, void* output, int samples);
		void convert16u(const void* input, void* output, int samples);
		void convert32u(const void* input, void* output, int samples);
		void convertFloat(const void* input, void* output, int samples);
		void convertReal(const void* input, void* output, int samples);

};

#endif
