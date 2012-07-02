#include <qsampleconverter.h>
#include <string.h>
#include <math.h>

#define ROUND(x) (x<0?ceil((x)-0.5):floor((x)+0.5))

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

qbyte8u QSampleConverter::convertTo8u(const qbyte8u value)
{
	return value;
}

qbyte8u QSampleConverter::convertTo8u(const qbyte16u value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8u QSampleConverter::convertTo8u(const qbyte32u value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8u QSampleConverter::convertTo8u(const qbyte8s value)
{
	return value + RANGE_8;
}

qbyte8u QSampleConverter::convertTo8u(const qbyte16s value)
{
	return ROUND((value + RANGE_16) / RATIO_16_8);
}

qbyte8u QSampleConverter::convertTo8u(const qbyte32s value)
{
	return ROUND((value + RANGE_32) / RATIO_32_8);
}

qbyte8u QSampleConverter::convertTo8u(const qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_8);
}

qbyte8u QSampleConverter::convertTo8u(const qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_8);
}

/**********************************************************************
Value conversion - unsigned 16
**********************************************************************/

qbyte16u QSampleConverter::convertTo16u(const qbyte8u value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16u QSampleConverter::convertTo16u(const qbyte16u value)
{
	return value;
}

qbyte16u QSampleConverter::convertTo16u(const qbyte32u value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16u QSampleConverter::convertTo16u(const qbyte8s value)
{
	return ROUND((value + RANGE_8) / RATIO_8_16);
}

qbyte16u QSampleConverter::convertTo16u(qbyte16s value)
{
	return value + RANGE_16;
}

qbyte16u QSampleConverter::convertTo16u(const qbyte32s value)
{
	return ROUND((value + RANGE_32) / RATIO_32_16);
}

qbyte16u QSampleConverter::convertTo16u(const qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_16);
}

qbyte16u QSampleConverter::convertTo16u(const qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_16);
}

/**********************************************************************
Value conversion - unsigned 32
**********************************************************************/

qbyte32u QSampleConverter::convertTo32u(const qbyte8u value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32u QSampleConverter::convertTo32u(const qbyte16u value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32u QSampleConverter::convertTo32u(const qbyte32u value)
{
	return value;
}

qbyte32u QSampleConverter::convertTo32u(const qbyte8s value)
{
	return ROUND((value + RANGE_8) / RATIO_8_32);
}

qbyte32u QSampleConverter::convertTo32u(const qbyte16s value)
{
	return ROUND((value + RANGE_16) / RATIO_16_32);
}

qbyte32u QSampleConverter::convertTo32u(const qbyte32s value)
{
	return value + RANGE_32;
}

qbyte32u QSampleConverter::convertTo32u(const qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_32);
}

qbyte32u QSampleConverter::convertTo32u(const qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_32);
}

/**********************************************************************
Value conversion - signed 8
**********************************************************************/

qbyte8s QSampleConverter::convertTo8s(const qbyte8u value)
{
	return value - RANGE_8;
}

qbyte8s QSampleConverter::convertTo8s(const qbyte16u value)
{
	return ROUND((value - RANGE_16) / RATIO_16_8);
}

qbyte8s QSampleConverter::convertTo8s(const qbyte32u value)
{
	return ROUND((value - RANGE_32) / RATIO_32_8);
}

qbyte8s QSampleConverter::convertTo8s(const qbyte8s value)
{
	return value;
}

qbyte8s QSampleConverter::convertTo8s(const qbyte16s value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8s QSampleConverter::convertTo8s(const qbyte32s value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8s QSampleConverter::convertTo8s(const qfloat value)
{
	return ROUND(value * RANGE_8);
}

qbyte8s QSampleConverter::convertTo8s(const qreal value)
{
	return ROUND(value * RANGE_8);
}

/**********************************************************************
Value conversion - signed 16
**********************************************************************/

qbyte16s QSampleConverter::convertTo16s(const qbyte8u value)
{
	return ROUND((value - RANGE_8) / RATIO_8_16);
}

qbyte16s QSampleConverter::convertTo16s(const qbyte16u value)
{
	return value - RANGE_16;
}

qbyte16s QSampleConverter::convertTo16s(const qbyte32u value)
{
	return ROUND((value - RANGE_32) / RATIO_32_16);
}

qbyte16s QSampleConverter::convertTo16s(const qbyte8s value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16s QSampleConverter::convertTo16s(const qbyte16s value)
{
	return value;
}

qbyte16s QSampleConverter::convertTo16s(const qbyte32s value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16s QSampleConverter::convertTo16s(const qfloat value)
{
	return ROUND(value * RANGE_16);
}

qbyte16s QSampleConverter::convertTo16s(const qreal value)
{
	return ROUND(value * RANGE_16);
}

/**********************************************************************
Value conversion - signed 32
**********************************************************************/

qbyte32s QSampleConverter::convertTo32s(const qbyte8u value)
{
	return ROUND((value - RANGE_8) / RATIO_8_32);
}

qbyte32s QSampleConverter::convertTo32s(const qbyte16u value)
{
	return ROUND((value - RANGE_16) / RATIO_16_32);
}

qbyte32s QSampleConverter::convertTo32s(const qbyte32u value)
{
	return value - RANGE_32;
}

qbyte32s QSampleConverter::convertTo32s(const qbyte8s value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32s QSampleConverter::convertTo32s(const qbyte16s value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32s QSampleConverter::convertTo32s(const qbyte32s value)
{
	return value;
}

qbyte32s QSampleConverter::convertTo32s(const qfloat value)
{
	return ROUND(value * RANGE_32);
}

qbyte32s QSampleConverter::convertTo32s(const qreal value)
{
	return ROUND(value * RANGE_32);
}

/**********************************************************************
Value conversion - float
**********************************************************************/

qfloat QSampleConverter::convertToFloat(const qbyte8u value)
{
	return (value - RANGE_8) / RANGE_8f;
}

qfloat QSampleConverter::convertToFloat(const qbyte16u value)
{
	return (value - RANGE_16) / RANGE_16f;
}

qfloat QSampleConverter::convertToFloat(const qbyte32u value)
{
	return (value - RANGE_32) / RANGE_32f;
}

qfloat QSampleConverter::convertToFloat(const qbyte8s value)
{
	return value / RANGE_8f;
}

qfloat QSampleConverter::convertToFloat(const qbyte16s value)
{
	return value / RANGE_16f;
}

qfloat QSampleConverter::convertToFloat(const qbyte32s value)
{
	return value / RANGE_32f;
}

qfloat QSampleConverter::convertToFloat(const qfloat value)
{
	return value;
}

qfloat QSampleConverter::convertToFloat(const qreal value)
{
	return value;
}

/**********************************************************************
Value conversion - real
**********************************************************************/

qreal QSampleConverter::convertToReal(const qbyte8u value)
{
	return (value - RANGE_8) / RANGE_8f;
}

qreal QSampleConverter::convertToReal(const qbyte16u value)
{
	return (value - RANGE_16) / RANGE_16f;
}

qreal QSampleConverter::convertToReal(const qbyte32u value)
{
	return (value - RANGE_32) / RANGE_32f;
}

qreal QSampleConverter::convertToReal(const qbyte8s value)
{
	return value / RANGE_8f;
}

qreal QSampleConverter::convertToReal(const qbyte16s value)
{
	return value / RANGE_16f;
}

qreal QSampleConverter::convertToReal(const qbyte32s value)
{
	return value / RANGE_32f;
}

qreal QSampleConverter::convertToReal(const qfloat value)
{
	return value;
}

qreal QSampleConverter::convertToReal(const qreal value)
{
	return value;
}

/**********************************************************************
Array conversion - unsigned 8
**********************************************************************/

void QSampleConverter::convert8uTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convert8uTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convert8uTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convert8uTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convert8uTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convert8uTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convert8uToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qfloat*) output, size);
}

void QSampleConverter::convert8uToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8u*) input, (qreal*) output, size);
}

/**********************************************************************
Array conversion - unsigned 16
**********************************************************************/

void QSampleConverter::convert16uTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convert16uTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convert16uTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convert16uTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convert16uTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convert16uTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convert16uToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qfloat*) output, size);
}

void QSampleConverter::convert16uToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16u*) input, (qreal*) output, size);
}

/**********************************************************************
Array conversion - unsigned 32
**********************************************************************/

void QSampleConverter::convert32uTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convert32uTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convert32uTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convert32uTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convert32uTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convert32uTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convert32uToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qfloat*) output, size);
}

void QSampleConverter::convert32uToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32u*) input, (qreal*) output, size);
}

/**********************************************************************
Array conversion - signed 8
**********************************************************************/

void QSampleConverter::convert8sTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convert8sTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convert8sTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convert8sTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convert8sTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convert8sTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convert8sToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qfloat*) output, size);
}

void QSampleConverter::convert8sToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte8s*) input, (qreal*) output, size);
}

/**********************************************************************
Array conversion - signed 16
**********************************************************************/

void QSampleConverter::convert16sTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convert16sTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convert16sTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convert16sTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convert16sTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convert16sTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convert16sToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qfloat*) output, size);
}

void QSampleConverter::convert16sToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte16s*) input, (qreal*) output, size);
}


/**********************************************************************
Array conversion - signed 32
**********************************************************************/

void QSampleConverter::convert32sTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convert32sTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convert32sTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convert32sTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convert32sTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convert32sTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convert32sToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qfloat*) output, size);
}

void QSampleConverter::convert32sToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qbyte32s*) input, (qreal*) output, size);
}

/**********************************************************************
Array conversion - float
**********************************************************************/

void QSampleConverter::convertFloatTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convertFloatTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convertFloatTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convertFloatTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convertFloatTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convertFloatTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convertFloatToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qfloat*) output, size);
}

void QSampleConverter::convertFloatToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qfloat*) input, (qreal*) output, size);
}

/**********************************************************************
Array conversion - real
**********************************************************************/

void QSampleConverter::convertRealTo8u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qbyte8u*) output, size);
}

void QSampleConverter::convertRealTo16u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qbyte16u*) output, size);
}

void QSampleConverter::convertRealTo32u(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qbyte32u*) output, size);
}

void QSampleConverter::convertRealTo8s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qbyte8s*) output, size);
}

void QSampleConverter::convertRealTo16s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qbyte16s*) output, size);
}

void QSampleConverter::convertRealTo32s(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qbyte32s*) output, size);
}

void QSampleConverter::convertRealToFloat(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qfloat*) output, size);
}

void QSampleConverter::convertRealToReal(const void *input, void *output, const int size)
{
	QSampleConverter::convert((qreal*) input, (qreal*) output, size);
}

/**********************************************************************
Array conversion - unsigned 8
**********************************************************************/

void QSampleConverter::convert(const qbyte8u *input, qbyte8u *output, const int size)
{
	memcpy(output, input, size * sizeof(qbyte8u));
}

void QSampleConverter::convert(const qbyte8u *input, qbyte16u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8u *input, qbyte32u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8u *input, qbyte8s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8u *input, qbyte16s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8u *input, qbyte32s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8u *input, qfloat *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8u *input, qreal *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 16
**********************************************************************/

void QSampleConverter::convert(const qbyte16u *input, qbyte8u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16u *input, qbyte16u *output, const int size)
{
	memcpy(output, input, size * sizeof(qbyte16u));
}

void QSampleConverter::convert(const qbyte16u *input, qbyte32u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16u *input, qbyte8s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16u *input, qbyte16s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16u *input, qbyte32s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16u *input, qfloat *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16u *input, qreal *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 32
**********************************************************************/

void QSampleConverter::convert(const qbyte32u *input, qbyte8u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32u *input, qbyte16u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32u *input, qbyte32u *output, const int size)
{
	memcpy(output, input, size * sizeof(qbyte32u));
}

void QSampleConverter::convert(const qbyte32u *input, qbyte8s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32u *input, qbyte16s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32u *input, qbyte32s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32u *input, qfloat *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32u *input, qreal *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 8
**********************************************************************/

void QSampleConverter::convert(const qbyte8s *input, qbyte8u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8s *input, qbyte16u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8s *input, qbyte32u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8s *input, qbyte8s *output, const int size)
{
	memcpy(output, input, size * sizeof(qbyte8s));
}

void QSampleConverter::convert(const qbyte8s *input, qbyte16s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8s *input, qbyte32s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8s *input, qfloat *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(const qbyte8s *input, qreal *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 16
**********************************************************************/

void QSampleConverter::convert(const qbyte16s *input, qbyte8u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16s *input, qbyte16u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16s *input, qbyte32u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16s *input, qbyte8s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16s *input, qbyte16s *output, const int size)
{
	memcpy(output, input, size * sizeof(qbyte16s));
}

void QSampleConverter::convert(const qbyte16s *input, qbyte32s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16s *input, qfloat *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(const qbyte16s *input, qreal *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 32
**********************************************************************/

void QSampleConverter::convert(const qbyte32s *input, qbyte8u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32s *input, qbyte16u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32s *input, qbyte32u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32s *input, qbyte8s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32s *input, qbyte16s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32s *input, qbyte32s *output, const int size)
{
	memcpy(output, input, size * sizeof(qbyte32s));
}

void QSampleConverter::convert(const qbyte32s *input, qfloat *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(const qbyte32s *input, qreal *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - float
**********************************************************************/

void QSampleConverter::convert(const qfloat *input, qbyte8u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(const qfloat *input, qbyte16u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(const qfloat *input, qbyte32u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(const qfloat *input, qbyte8s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(const qfloat *input, qbyte16s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(const qfloat *input, qbyte32s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(const qfloat *input, qfloat *output, const int size)
{
	memcpy(output, input, size * sizeof(qfloat));
}

void QSampleConverter::convert(const qfloat *input, qreal *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - real
**********************************************************************/

void QSampleConverter::convert(const qreal *input, qbyte8u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(const qreal *input, qbyte16u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(const qreal *input, qbyte32u *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(const qreal *input, qbyte8s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(const qreal *input, qbyte16s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(const qreal *input, qbyte32s *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(const qreal *input, qfloat *output, const int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(const qreal *input, qreal *output, const int size)
{
	memcpy(output, input, size * sizeof(qreal));
}

