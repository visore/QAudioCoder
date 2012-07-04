#include <qsamplerateconverter.h>
#include <libresample.h>

QSampleRateConverter::QSampleRateConverter()
{
	mResampler = NULL;
	mFactor = 1;
}

QSampleRateConverter::QSampleRateConverter(short channels, qreal inputRate, qreal outputRate, QSampleRateConverter::Mode mode)
{
	QSampleRateConverter();
	initialize(channels, inputRate, outputRate, mode);
}

QSampleRateConverter::~QSampleRateConverter()
{
	if(mResampler != NULL)
	{
		resample_close(mResampler);
		mResampler = NULL;
	}
}

bool QSampleRateConverter::initialize(short channels, qreal inputRate, qreal outputRate, QSampleRateConverter::Mode mode)
{
	if(mResampler != NULL)
	{
		resample_close(mResampler);
	}

	mFactor = outputRate / inputRate;

	if(mFactor == 1)
	{
		convertPointer = &QSampleRateConverter::copy;
	}
	else
	{
		convertPointer = &QSampleRateConverter::resample;
		mResampler = resample_open(mode == QSampleRateConverter::HighQuality, mFactor, mFactor);
	}

	return true;
}

void QSampleRateConverter::convert(const qfloat *input, qfloat *output, int samples)
{
	(this->*convertPointer)(input, output, samples);
}

void QSampleRateConverter::copy(const qfloat *input, qfloat *output, int samples)
{
	memcpy(output, input, sizeof(qfloat) * samples);
}

void QSampleRateConverter::resample(const qfloat *input, qfloat *output, int samples)
{
	int used;
	resample_process(mResampler, mFactor, (float*) input, samples, 0, &used, output, ceil(samples * mFactor));
}
