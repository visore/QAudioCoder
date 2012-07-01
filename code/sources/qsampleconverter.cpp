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

void QSampleConverter::test()
{
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8u(255u)) == qbyte8u(255u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8u(200u)) == qbyte8u(200u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8u(100u)) == qbyte8u(100u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8u(0u)) == qbyte8u(0u));

	Q_ASSERT(QSampleConverter::convertTo8u(qbyte16u(65535u)) == qbyte8u(255u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte16u(40000u)) == qbyte8u(156u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte16u(10000u)) == qbyte8u(39u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte16u(0u)) == qbyte8u(0u));

	Q_ASSERT(QSampleConverter::convertTo8u(qbyte32u(4294967295u)) == qbyte8u(255u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte32u(2000000000u)) == qbyte8u(119u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte32u(1000000000u)) == qbyte8u(59u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte32u(0u)) == qbyte8u(0u));

	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8s(127)) == qbyte8u(255u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8s(100)) == qbyte8u(228u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8s(0)) == qbyte8u(128u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8s(-100)) == qbyte8u(28u));
	Q_ASSERT(QSampleConverter::convertTo8u(qbyte8s(-128)) == qbyte8u(0u));
}

/**********************************************************************
Value conversion - unsigned 8
**********************************************************************/

qbyte8u QSampleConverter::convertTo8u(qbyte8u value)
{
	return value;
}

qbyte8u QSampleConverter::convertTo8u(qbyte16u value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8u QSampleConverter::convertTo8u(qbyte32u value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8u QSampleConverter::convertTo8u(qbyte8s value)
{
	return value + RANGE_8;
}

qbyte8u QSampleConverter::convertTo8u(qbyte16s value)
{
	return ROUND((value + RANGE_16) / RATIO_16_8);
}

qbyte8u QSampleConverter::convertTo8u(qbyte32s value)
{
	return ROUND((value + RANGE_32) / RATIO_32_8);
}

qbyte8u QSampleConverter::convertTo8u(qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_8);
}

qbyte8u QSampleConverter::convertTo8u(qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_8);
}

/**********************************************************************
Value conversion - unsigned 16
**********************************************************************/

qbyte16u QSampleConverter::convertTo16u(qbyte8u value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16u QSampleConverter::convertTo16u(qbyte16u value)
{
	return value;
}

qbyte16u QSampleConverter::convertTo16u(qbyte32u value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16u QSampleConverter::convertTo16u(qbyte8s value)
{
	return ROUND((value + RANGE_8) / RATIO_8_16);
}

qbyte16u QSampleConverter::convertTo16u(qbyte16s value)
{
	return value + RANGE_16;
}

qbyte16u QSampleConverter::convertTo16u(qbyte32s value)
{
	return ROUND((value + RANGE_32) / RATIO_32_16);
}

qbyte16u QSampleConverter::convertTo16u(qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_16);
}

qbyte16u QSampleConverter::convertTo16u(qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_16);
}

/**********************************************************************
Value conversion - unsigned 32
**********************************************************************/

qbyte32u QSampleConverter::convertTo32u(qbyte8u value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32u QSampleConverter::convertTo32u(qbyte16u value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32u QSampleConverter::convertTo32u(qbyte32u value)
{
	return value;
}

qbyte32u QSampleConverter::convertTo32u(qbyte8s value)
{
	return ROUND((value + RANGE_8) / RATIO_8_32);
}

qbyte32u QSampleConverter::convertTo32u(qbyte16s value)
{
	return ROUND((value + RANGE_16) / RATIO_16_32);
}

qbyte32u QSampleConverter::convertTo32u(qbyte32s value)
{
	return value + RANGE_32;
}

qbyte32u QSampleConverter::convertTo32u(qfloat value)
{
	return ROUND((value + RANGE_FLOAT) * RANGE_32);
}

qbyte32u QSampleConverter::convertTo32u(qreal value)
{
	return ROUND((value + RANGE_REAL) * RANGE_32);
}

/**********************************************************************
Value conversion - signed 8
**********************************************************************/

qbyte8s QSampleConverter::convertTo8s(qbyte8u value)
{
	return value - RANGE_8;
}

qbyte8s QSampleConverter::convertTo8s(qbyte16u value)
{
	return ROUND((value - RANGE_16) / RATIO_16_8);
}

qbyte8s QSampleConverter::convertTo8s(qbyte32u value)
{
	return ROUND((value - RANGE_32) / RATIO_32_8);
}

qbyte8s QSampleConverter::convertTo8s(qbyte8s value)
{
	return value;
}

qbyte8s QSampleConverter::convertTo8s(qbyte16s value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8s QSampleConverter::convertTo8s(qbyte32s value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8s QSampleConverter::convertTo8s(qfloat value)
{
	return ROUND(value * RANGE_8);
}

qbyte8s QSampleConverter::convertTo8s(qreal value)
{
	return ROUND(value * RANGE_8);
}

/**********************************************************************
Value conversion - signed 16
**********************************************************************/

qbyte16s QSampleConverter::convertTo16s(qbyte8u value)
{
	return ROUND((value - RANGE_8) / RATIO_8_16);
}

qbyte16s QSampleConverter::convertTo16s(qbyte16u value)
{
	return value - RANGE_16;
}

qbyte16s QSampleConverter::convertTo16s(qbyte32u value)
{
	return ROUND((value - RANGE_32) / RATIO_32_16);
}

qbyte16s QSampleConverter::convertTo16s(qbyte8s value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16s QSampleConverter::convertTo16s(qbyte16s value)
{
	return value;
}

qbyte16s QSampleConverter::convertTo16s(qbyte32s value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16s QSampleConverter::convertTo16s(qfloat value)
{
	return ROUND(value * RANGE_16);
}

qbyte16s QSampleConverter::convertTo16s(qreal value)
{
	return ROUND(value * RANGE_16);
}

/**********************************************************************
Value conversion - signed 32
**********************************************************************/

qbyte32s QSampleConverter::convertTo32s(qbyte8u value)
{
	return ROUND((value - RANGE_8) / RATIO_8_32);
}

qbyte32s QSampleConverter::convertTo32s(qbyte16u value)
{
	return ROUND((value - RANGE_16) / RATIO_16_32);
}

qbyte32s QSampleConverter::convertTo32s(qbyte32u value)
{
	return value - RANGE_32;
}

qbyte32s QSampleConverter::convertTo32s(qbyte8s value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32s QSampleConverter::convertTo32s(qbyte16s value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32s QSampleConverter::convertTo32s(qbyte32s value)
{
	return value;
}

qbyte32s QSampleConverter::convertTo32s(qfloat value)
{
	return ROUND(value * RANGE_32);
}

qbyte32s QSampleConverter::convertTo32s(qreal value)
{
	return ROUND(value * RANGE_32);
}

/**********************************************************************
Value conversion - float
**********************************************************************/

qfloat QSampleConverter::convertToFloat(qbyte8u value)
{
	return (value - RANGE_8) / RANGE_8f;
}

qfloat QSampleConverter::convertToFloat(qbyte16u value)
{
	return (value - RANGE_16) / RANGE_16f;
}

qfloat QSampleConverter::convertToFloat(qbyte32u value)
{
	return (value - RANGE_32) / RANGE_32f;
}

qfloat QSampleConverter::convertToFloat(qbyte8s value)
{
	return value / RANGE_8f;
}

qfloat QSampleConverter::convertToFloat(qbyte16s value)
{
	return value / RANGE_16f;
}

qfloat QSampleConverter::convertToFloat(qbyte32s value)
{
	return value / RANGE_32f;
}

qfloat QSampleConverter::convertToFloat(qfloat value)
{
	return value;
}

qfloat QSampleConverter::convertToFloat(qreal value)
{
	return value;
}

/**********************************************************************
Value conversion - real
**********************************************************************/

qreal QSampleConverter::convertToReal(qbyte8u value)
{
	return (value - RANGE_8) / RANGE_8f;
}

qreal QSampleConverter::convertToReal(qbyte16u value)
{
	return (value - RANGE_16) / RANGE_16f;
}

qreal QSampleConverter::convertToReal(qbyte32u value)
{
	return (value - RANGE_32) / RANGE_32f;
}

qreal QSampleConverter::convertToReal(qbyte8s value)
{
	return value / RANGE_8f;
}

qreal QSampleConverter::convertToReal(qbyte16s value)
{
	return value / RANGE_16f;
}

qreal QSampleConverter::convertToReal(qbyte32s value)
{
	return value / RANGE_32f;
}

qreal QSampleConverter::convertToReal(qfloat value)
{
	return value;
}

qreal QSampleConverter::convertToReal(qreal value)
{
	return value;
}

/**********************************************************************
Array conversion - unsigned 8
**********************************************************************/

void QSampleConverter::convert(qbyte8u *input, qbyte8u *output, int size)
{
	memcpy(output, input, size * sizeof(qbyte8u));
}

void QSampleConverter::convert(qbyte8u *input, qbyte16u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(qbyte8u *input, qbyte32u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(qbyte8u *input, qbyte8s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(qbyte8u *input, qbyte16s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(qbyte8u *input, qbyte32s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(qbyte8u *input, qfloat *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(qbyte8u *input, qreal *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 16
**********************************************************************/

void QSampleConverter::convert(qbyte16u *input, qbyte8u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(qbyte16u *input, qbyte16u *output, int size)
{
	memcpy(output, input, size * sizeof(qbyte16u));
}

void QSampleConverter::convert(qbyte16u *input, qbyte32u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(qbyte16u *input, qbyte8s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(qbyte16u *input, qbyte16s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(qbyte16u *input, qbyte32s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(qbyte16u *input, qfloat *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(qbyte16u *input, qreal *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 32
**********************************************************************/

void QSampleConverter::convert(qbyte32u *input, qbyte8u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(qbyte32u *input, qbyte16u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(qbyte32u *input, qbyte32u *output, int size)
{
	memcpy(output, input, size * sizeof(qbyte32u));
}

void QSampleConverter::convert(qbyte32u *input, qbyte8s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(qbyte32u *input, qbyte16s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(qbyte32u *input, qbyte32s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(qbyte32u *input, qfloat *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(qbyte32u *input, qreal *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 8
**********************************************************************/

void QSampleConverter::convert(qbyte8s *input, qbyte8u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(qbyte8s *input, qbyte16u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(qbyte8s *input, qbyte32u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(qbyte8s *input, qbyte8s *output, int size)
{
	memcpy(output, input, size * sizeof(qbyte8s));
}

void QSampleConverter::convert(qbyte8s *input, qbyte16s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(qbyte8s *input, qbyte32s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(qbyte8s *input, qfloat *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(qbyte8s *input, qreal *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 16
**********************************************************************/

void QSampleConverter::convert(qbyte16s *input, qbyte8u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(qbyte16s *input, qbyte16u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(qbyte16s *input, qbyte32u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(qbyte16s *input, qbyte8s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(qbyte16s *input, qbyte16s *output, int size)
{
	memcpy(output, input, size * sizeof(qbyte16s));
}

void QSampleConverter::convert(qbyte16s *input, qbyte32s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(qbyte16s *input, qfloat *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(qbyte16s *input, qreal *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - signed 32
**********************************************************************/

void QSampleConverter::convert(qbyte32s *input, qbyte8u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(qbyte32s *input, qbyte16u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(qbyte32s *input, qbyte32u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(qbyte32s *input, qbyte8s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(qbyte32s *input, qbyte16s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(qbyte32s *input, qbyte32s *output, int size)
{
	memcpy(output, input, size * sizeof(qbyte32s));
}

void QSampleConverter::convert(qbyte32s *input, qfloat *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(qbyte32s *input, qreal *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - float
**********************************************************************/

void QSampleConverter::convert(qfloat *input, qbyte8u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(qfloat *input, qbyte16u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(qfloat *input, qbyte32u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(qfloat *input, qbyte8s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(qfloat *input, qbyte16s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(qfloat *input, qbyte32s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(qfloat *input, qfloat *output, int size)
{
	memcpy(output, input, size * sizeof(qfloat));
}

void QSampleConverter::convert(qfloat *input, qreal *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToReal(input[i]);
	}
}

/**********************************************************************
Array conversion - real
**********************************************************************/

void QSampleConverter::convert(qreal *input, qbyte8u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8u(input[i]);
	}
}

void QSampleConverter::convert(qreal *input, qbyte16u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16u(input[i]);
	}
}

void QSampleConverter::convert(qreal *input, qbyte32u *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32u(input[i]);
	}
}

void QSampleConverter::convert(qreal *input, qbyte8s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo8s(input[i]);
	}
}

void QSampleConverter::convert(qreal *input, qbyte16s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo16s(input[i]);
	}
}

void QSampleConverter::convert(qreal *input, qbyte32s *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertTo32s(input[i]);
	}
}

void QSampleConverter::convert(qreal *input, qfloat *output, int size)
{
	for(int i = 0; i < size; ++i)
	{
		output[i] = QSampleConverter::convertToFloat(input[i]);
	}
}

void QSampleConverter::convert(qreal *input, qreal *output, int size)
{
	memcpy(output, input, size * sizeof(qreal));
}

