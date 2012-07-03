#include <qsamplesizeconverter.h>

#define RANGE_8 128u
#define RANGE_16 32768u
#define RANGE_32 2147483648u
#define RANGE_FLOAT 1u
#define RANGE_REAL 1u

#define RANGE_8f 128.0
#define RANGE_16f 32768.0
#define RANGE_32f 2147483648.0
#define RANGE_FLOATf 1.0
#define RANGE_REALf 1.0

#define RATIO_16_8 257.0
#define RATIO_32_8 16843009.0

#define RATIO_8_16 0.00389105058365759
#define RATIO_32_16 65537.0

#define RATIO_8_32 5.93718141455603e-08
#define RATIO_16_32 1.5258556235409e-05

/**********************************************************************
Value conversion - unsigned 8
**********************************************************************/

qbyte8u QSampleSizeConverter::convertTo8u(const qbyte8u value)
{
	return value;
}

qbyte8u QSampleSizeConverter::convertTo8u(const qbyte16u value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8u QSampleSizeConverter::convertTo8u(const qbyte32u value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8u QSampleSizeConverter::convertTo8u(const qbyte8s value)
{
	return value + RANGE_8;
}

qbyte8u QSampleSizeConverter::convertTo8u(const qbyte16s value)
{
	return ROUND((value + RANGE_16) / RATIO_16_8);
}

qbyte8u QSampleSizeConverter::convertTo8u(const qbyte32s value)
{
	return ROUND((value + RANGE_32) / RATIO_32_8);
}

qbyte8u QSampleSizeConverter::convertTo8u(const qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_8);
}

qbyte8u QSampleSizeConverter::convertTo8u(const qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_8);
}

/**********************************************************************
Value conversion - unsigned 16
**********************************************************************/

qbyte16u QSampleSizeConverter::convertTo16u(const qbyte8u value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16u QSampleSizeConverter::convertTo16u(const qbyte16u value)
{
	return value;
}

qbyte16u QSampleSizeConverter::convertTo16u(const qbyte32u value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16u QSampleSizeConverter::convertTo16u(const qbyte8s value)
{
	return ROUND((value + RANGE_8) / RATIO_8_16);
}

qbyte16u QSampleSizeConverter::convertTo16u(qbyte16s value)
{
	return value + RANGE_16;
}

qbyte16u QSampleSizeConverter::convertTo16u(const qbyte32s value)
{
	return ROUND((value + RANGE_32) / RATIO_32_16);
}

qbyte16u QSampleSizeConverter::convertTo16u(const qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_16);
}

qbyte16u QSampleSizeConverter::convertTo16u(const qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_16);
}

/**********************************************************************
Value conversion - unsigned 32
**********************************************************************/

qbyte32u QSampleSizeConverter::convertTo32u(const qbyte8u value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32u QSampleSizeConverter::convertTo32u(const qbyte16u value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32u QSampleSizeConverter::convertTo32u(const qbyte32u value)
{
	return value;
}

qbyte32u QSampleSizeConverter::convertTo32u(const qbyte8s value)
{
	return ROUND((value + RANGE_8) / RATIO_8_32);
}

qbyte32u QSampleSizeConverter::convertTo32u(const qbyte16s value)
{
	return ROUND((value + RANGE_16) / RATIO_16_32);
}

qbyte32u QSampleSizeConverter::convertTo32u(const qbyte32s value)
{
	return value + RANGE_32;
}

qbyte32u QSampleSizeConverter::convertTo32u(const qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_32);
}

qbyte32u QSampleSizeConverter::convertTo32u(const qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_32);
}

/**********************************************************************
Value conversion - signed 8
**********************************************************************/

qbyte8s QSampleSizeConverter::convertTo8s(const qbyte8u value)
{
	return value - RANGE_8;
}

qbyte8s QSampleSizeConverter::convertTo8s(const qbyte16u value)
{
	return ROUND((value - RANGE_16) / RATIO_16_8);
}

qbyte8s QSampleSizeConverter::convertTo8s(const qbyte32u value)
{
	return ROUND((value - RANGE_32) / RATIO_32_8);
}

qbyte8s QSampleSizeConverter::convertTo8s(const qbyte8s value)
{
	return value;
}

qbyte8s QSampleSizeConverter::convertTo8s(const qbyte16s value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8s QSampleSizeConverter::convertTo8s(const qbyte32s value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8s QSampleSizeConverter::convertTo8s(const qfloat value)
{
	return ROUND(value * RANGE_8);
}

qbyte8s QSampleSizeConverter::convertTo8s(const qreal value)
{
	return ROUND(value * RANGE_8);
}

/**********************************************************************
Value conversion - signed 16
**********************************************************************/

qbyte16s QSampleSizeConverter::convertTo16s(const qbyte8u value)
{
	return ROUND((value - RANGE_8) / RATIO_8_16);
}

qbyte16s QSampleSizeConverter::convertTo16s(const qbyte16u value)
{
	return value - RANGE_16;
}

qbyte16s QSampleSizeConverter::convertTo16s(const qbyte32u value)
{
	return ROUND((value - RANGE_32) / RATIO_32_16);
}

qbyte16s QSampleSizeConverter::convertTo16s(const qbyte8s value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16s QSampleSizeConverter::convertTo16s(const qbyte16s value)
{
	return value;
}

qbyte16s QSampleSizeConverter::convertTo16s(const qbyte32s value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16s QSampleSizeConverter::convertTo16s(const qfloat value)
{
	return ROUND(value * RANGE_16);
}

qbyte16s QSampleSizeConverter::convertTo16s(const qreal value)
{
	return ROUND(value * RANGE_16);
}

/**********************************************************************
Value conversion - signed 32
**********************************************************************/

qbyte32s QSampleSizeConverter::convertTo32s(const qbyte8u value)
{
	return ROUND((value - RANGE_8) / RATIO_8_32);
}

qbyte32s QSampleSizeConverter::convertTo32s(const qbyte16u value)
{
	return ROUND((value - RANGE_16) / RATIO_16_32);
}

qbyte32s QSampleSizeConverter::convertTo32s(const qbyte32u value)
{
	return value - RANGE_32;
}

qbyte32s QSampleSizeConverter::convertTo32s(const qbyte8s value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32s QSampleSizeConverter::convertTo32s(const qbyte16s value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32s QSampleSizeConverter::convertTo32s(const qbyte32s value)
{
	return value;
}

qbyte32s QSampleSizeConverter::convertTo32s(const qfloat value)
{
	return ROUND(value * RANGE_32);
}

qbyte32s QSampleSizeConverter::convertTo32s(const qreal value)
{
	return ROUND(value * RANGE_32);
}

/**********************************************************************
Value conversion - float
**********************************************************************/

qfloat QSampleSizeConverter::convertToFloat(const qbyte8u value)
{
	return (value - RANGE_8) / RANGE_8f;
}

qfloat QSampleSizeConverter::convertToFloat(const qbyte16u value)
{
	return (value - RANGE_16) / RANGE_16f;
}

qfloat QSampleSizeConverter::convertToFloat(const qbyte32u value)
{
	return (value - RANGE_32) / RANGE_32f;
}

qfloat QSampleSizeConverter::convertToFloat(const qbyte8s value)
{
	return value / RANGE_8f;
}

qfloat QSampleSizeConverter::convertToFloat(const qbyte16s value)
{
	return value / RANGE_16f;
}

qfloat QSampleSizeConverter::convertToFloat(const qbyte32s value)
{
	return value / RANGE_32f;
}

qfloat QSampleSizeConverter::convertToFloat(const qfloat value)
{
	return value;
}

qfloat QSampleSizeConverter::convertToFloat(const qreal value)
{
	return value;
}

/**********************************************************************
Value conversion - real
**********************************************************************/

qreal QSampleSizeConverter::convertToReal(const qbyte8u value)
{
	return (value - RANGE_8) / RANGE_8f;
}

qreal QSampleSizeConverter::convertToReal(const qbyte16u value)
{
	return (value - RANGE_16) / RANGE_16f;
}

qreal QSampleSizeConverter::convertToReal(const qbyte32u value)
{
	return (value - RANGE_32) / RANGE_32f;
}

qreal QSampleSizeConverter::convertToReal(const qbyte8s value)
{
	return value / RANGE_8f;
}

qreal QSampleSizeConverter::convertToReal(const qbyte16s value)
{
	return value / RANGE_16f;
}

qreal QSampleSizeConverter::convertToReal(const qbyte32s value)
{
	return value / RANGE_32f;
}

qreal QSampleSizeConverter::convertToReal(const qfloat value)
{
	return value;
}

qreal QSampleSizeConverter::convertToReal(const qreal value)
{
	return value;
}

/**********************************************************************
Array conversion - unsigned 8
**********************************************************************/

void QSampleSizeConverter::convert8uTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convert8uTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convert8uTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convert8uTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convert8uTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convert8uTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convert8uToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convert8uToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8u*) input, (qreal*) output, samples);
}

/**********************************************************************
Array conversion - unsigned 16
**********************************************************************/

void QSampleSizeConverter::convert16uTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convert16uTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convert16uTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convert16uTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convert16uTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convert16uTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convert16uToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convert16uToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16u*) input, (qreal*) output, samples);
}

/**********************************************************************
Array conversion - unsigned 32
**********************************************************************/

void QSampleSizeConverter::convert32uTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convert32uTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convert32uTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convert32uTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convert32uTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convert32uTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convert32uToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convert32uToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32u*) input, (qreal*) output, samples);
}

/**********************************************************************
Array conversion - signed 8
**********************************************************************/

void QSampleSizeConverter::convert8sTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convert8sTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convert8sTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convert8sTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convert8sTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convert8sTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convert8sToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convert8sToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte8s*) input, (qreal*) output, samples);
}

/**********************************************************************
Array conversion - signed 16
**********************************************************************/

void QSampleSizeConverter::convert16sTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convert16sTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convert16sTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convert16sTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convert16sTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convert16sTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convert16sToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convert16sToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte16s*) input, (qreal*) output, samples);
}


/**********************************************************************
Array conversion - signed 32
**********************************************************************/

void QSampleSizeConverter::convert32sTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convert32sTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convert32sTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convert32sTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convert32sTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convert32sTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convert32sToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convert32sToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qbyte32s*) input, (qreal*) output, samples);
}

/**********************************************************************
Array conversion - float
**********************************************************************/

void QSampleSizeConverter::convertFloatTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convertFloatTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convertFloatTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convertFloatTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convertFloatTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convertFloatTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convertFloatToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convertFloatToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qfloat*) input, (qreal*) output, samples);
}

/**********************************************************************
Array conversion - real
**********************************************************************/

void QSampleSizeConverter::convertRealTo8u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qbyte8u*) output, samples);
}

void QSampleSizeConverter::convertRealTo16u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qbyte16u*) output, samples);
}

void QSampleSizeConverter::convertRealTo32u(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qbyte32u*) output, samples);
}

void QSampleSizeConverter::convertRealTo8s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qbyte8s*) output, samples);
}

void QSampleSizeConverter::convertRealTo16s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qbyte16s*) output, samples);
}

void QSampleSizeConverter::convertRealTo32s(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qbyte32s*) output, samples);
}

void QSampleSizeConverter::convertRealToFloat(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qfloat*) output, samples);
}

void QSampleSizeConverter::convertRealToReal(const void *input, void *output, const int samples)
{
	QSampleSizeConverter::convert((qreal*) input, (qreal*) output, samples);
}

/**********************************************************************
Array conversion - unsigned 8
**********************************************************************/

void QSampleSizeConverter::convert(const qbyte8u *input, qbyte8u *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte8u));
}

void QSampleSizeConverter::convert(const qbyte8u *input, qbyte16u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8u *input, qbyte32u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8u *input, qbyte8s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8u *input, qbyte16s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8u *input, qbyte32s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8u *input, qfloat *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToFloat(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8u *input, qreal *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 16
**********************************************************************/

void QSampleSizeConverter::convert(const qbyte16u *input, qbyte8u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16u *input, qbyte16u *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte16u));
}

void QSampleSizeConverter::convert(const qbyte16u *input, qbyte32u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16u *input, qbyte8s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16u *input, qbyte16s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16u *input, qbyte32s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16u *input, qfloat *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToFloat(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16u *input, qreal *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 32
**********************************************************************/

void QSampleSizeConverter::convert(const qbyte32u *input, qbyte8u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32u *input, qbyte16u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32u *input, qbyte32u *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte32u));
}

void QSampleSizeConverter::convert(const qbyte32u *input, qbyte8s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32u *input, qbyte16s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32u *input, qbyte32s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32u *input, qfloat *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToFloat(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32u *input, qreal *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 8
**********************************************************************/

void QSampleSizeConverter::convert(const qbyte8s *input, qbyte8u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8s *input, qbyte16u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8s *input, qbyte32u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8s *input, qbyte8s *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte8s));
}

void QSampleSizeConverter::convert(const qbyte8s *input, qbyte16s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8s *input, qbyte32s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8s *input, qfloat *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToFloat(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte8s *input, qreal *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 16
**********************************************************************/

void QSampleSizeConverter::convert(const qbyte16s *input, qbyte8u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16s *input, qbyte16u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16s *input, qbyte32u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16s *input, qbyte8s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16s *input, qbyte16s *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte16s));
}

void QSampleSizeConverter::convert(const qbyte16s *input, qbyte32s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16s *input, qfloat *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToFloat(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte16s *input, qreal *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 32
**********************************************************************/

void QSampleSizeConverter::convert(const qbyte32s *input, qbyte8u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32s *input, qbyte16u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32s *input, qbyte32u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32s *input, qbyte8s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32s *input, qbyte16s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32s *input, qbyte32s *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte32s));
}

void QSampleSizeConverter::convert(const qbyte32s *input, qfloat *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToFloat(input[i]);
	}
}

void QSampleSizeConverter::convert(const qbyte32s *input, qreal *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - float
**********************************************************************/

void QSampleSizeConverter::convert(const qfloat *input, qbyte8u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qfloat *input, qbyte16u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qfloat *input, qbyte32u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qfloat *input, qbyte8s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qfloat *input, qbyte16s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qfloat *input, qbyte32s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qfloat *input, qfloat *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qfloat));
}

void QSampleSizeConverter::convert(const qfloat *input, qreal *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - real
**********************************************************************/

void QSampleSizeConverter::convert(const qreal *input, qbyte8u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qreal *input, qbyte16u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qreal *input, qbyte32u *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32u(input[i]);
	}
}

void QSampleSizeConverter::convert(const qreal *input, qbyte8s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo8s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qreal *input, qbyte16s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo16s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qreal *input, qbyte32s *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertTo32s(input[i]);
	}
}

void QSampleSizeConverter::convert(const qreal *input, qfloat *output, const int samples)
{
	for(int i = 0; i < samples; ++i)
	{
		output[i] = QSampleSizeConverter::convertToFloat(input[i]);
	}
}

void QSampleSizeConverter::convert(const qreal *input, qreal *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qreal));
}

