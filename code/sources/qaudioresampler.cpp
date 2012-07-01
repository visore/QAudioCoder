#include <qaudioresampler.h>
#include <string.h>
#include <math.h>

#define ROUND(x) (x<0?ceil((x)-0.5):floor((x)+0.5))

#define RANGE_8 128u
#define RANGE_16 32768u
#define RANGE_32 2147483648u

#define RATIO_16_8 257.0
#define RATIO_32_8 16843009.0

#define RATIO_8_16 0.00389105058365759
#define RATIO_32_16 65537.0

#define RATIO_8_32 5.93718141455603e-08
#define RATIO_16_32 1.5258556235409e-05

void QAudioResampler::test()
{
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8u(255u)) == qbyte8u(255u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8u(200u)) == qbyte8u(200u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8u(100u)) == qbyte8u(100u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8u(0u)) == qbyte8u(0u));

	Q_ASSERT(QAudioResampler::convertTo8u(qbyte16u(65535u)) == qbyte8u(255u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte16u(40000u)) == qbyte8u(156u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte16u(10000u)) == qbyte8u(39u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte16u(0u)) == qbyte8u(0u));

	Q_ASSERT(QAudioResampler::convertTo8u(qbyte32u(4294967295u)) == qbyte8u(255u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte32u(2000000000u)) == qbyte8u(119u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte32u(1000000000u)) == qbyte8u(59u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte32u(0u)) == qbyte8u(0u));

	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8s(127)) == qbyte8u(255u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8s(100)) == qbyte8u(228u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8s(0)) == qbyte8u(128u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8s(-100)) == qbyte8u(28u));
	Q_ASSERT(QAudioResampler::convertTo8u(qbyte8s(-128)) == qbyte8u(0u));
}

/**********************************************************************
Value conversion - unsigned 8
**********************************************************************/

qbyte8u QAudioResampler::convertTo8u(qbyte8u value)
{
	return value;
}

qbyte8u QAudioResampler::convertTo8u(qbyte16u value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8u QAudioResampler::convertTo8u(qbyte32u value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8u QAudioResampler::convertTo8u(qbyte8s value)
{
	return value + RANGE_8;
}

qbyte8u QAudioResampler::convertTo8u(qbyte16s value)
{
	return ROUND((value + RANGE_16) / RATIO_16_8);
}

qbyte8u QAudioResampler::convertTo8u(qbyte32s value)
{
	return ROUND((value + RANGE_32) / RATIO_32_8);
}

qbyte8u QAudioResampler::convertTo8u(qfloat value)
{
	return ROUND(value * RANGE_8);
}

qbyte8u QAudioResampler::convertTo8u(qreal value)
{
	return ROUND(value * RANGE_8);
}

/**********************************************************************
Value conversion - unsigned 16
**********************************************************************/

qbyte16u QAudioResampler::convertTo16u(qbyte8u value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16u QAudioResampler::convertTo16u(qbyte16u value)
{
	return value;
}

qbyte16u QAudioResampler::convertTo16u(qbyte32u value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16u QAudioResampler::convertTo16u(qbyte8s value)
{

}

qbyte16u QAudioResampler::convertTo16u(qbyte16s value)
{

}

qbyte16u QAudioResampler::convertTo16u(qbyte32s value)
{

}

qbyte16u QAudioResampler::convertTo16u(qfloat value)
{

}

qbyte16u QAudioResampler::convertTo16u(qreal value)
{

}

/**********************************************************************
Value conversion - unsigned 32
**********************************************************************/

qbyte32u QAudioResampler::convertTo32u(qbyte8u value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32u QAudioResampler::convertTo32u(qbyte16u value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32u QAudioResampler::convertTo32u(qbyte32u value)
{
	return value;
}

qbyte32u QAudioResampler::convertTo32u(qbyte8s value)
{

}

qbyte32u QAudioResampler::convertTo32u(qbyte16s value)
{

}

qbyte32u QAudioResampler::convertTo32u(qbyte32s value)
{

}

qbyte32u QAudioResampler::convertTo32u(qfloat value)
{

}

qbyte32u QAudioResampler::convertTo32u(qreal value)
{

}

/**********************************************************************
Value conversion - signed 8
**********************************************************************/

qbyte8s QAudioResampler::convertTo8s(qbyte8u value)
{

}

qbyte8s QAudioResampler::convertTo8s(qbyte16u value)
{

}

qbyte8s QAudioResampler::convertTo8s(qbyte32u value)
{

}

qbyte8s QAudioResampler::convertTo8s(qbyte8s value)
{
	return value;
}

qbyte8s QAudioResampler::convertTo8s(qbyte16s value)
{
	return ROUND(value / RATIO_16_8);
}

qbyte8s QAudioResampler::convertTo8s(qbyte32s value)
{
	return ROUND(value / RATIO_32_8);
}

qbyte8s QAudioResampler::convertTo8s(qfloat value)
{

}

qbyte8s QAudioResampler::convertTo8s(qreal value)
{

}

/**********************************************************************
Value conversion - signed 16
**********************************************************************/

qbyte16s QAudioResampler::convertTo16s(qbyte8u value)
{

}

qbyte16s QAudioResampler::convertTo16s(qbyte16u value)
{

}

qbyte16s QAudioResampler::convertTo16s(qbyte32u value)
{

}

qbyte16s QAudioResampler::convertTo16s(qbyte8s value)
{
	return ROUND(value / RATIO_8_16);
}

qbyte16s QAudioResampler::convertTo16s(qbyte16s value)
{
	return value;
}

qbyte16s QAudioResampler::convertTo16s(qbyte32s value)
{
	return ROUND(value / RATIO_32_16);
}

qbyte16s QAudioResampler::convertTo16s(qfloat value)
{

}

qbyte16s QAudioResampler::convertTo16s(qreal value)
{

}

/**********************************************************************
Value conversion - signed 32
**********************************************************************/

qbyte32s QAudioResampler::convertTo32s(qbyte8u value)
{

}

qbyte32s QAudioResampler::convertTo32s(qbyte16u value)
{

}

qbyte32s QAudioResampler::convertTo32s(qbyte32u value)
{

}

qbyte32s QAudioResampler::convertTo32s(qbyte8s value)
{
	return ROUND(value / RATIO_8_32);
}

qbyte32s QAudioResampler::convertTo32s(qbyte16s value)
{
	return ROUND(value / RATIO_16_32);
}

qbyte32s QAudioResampler::convertTo32s(qbyte32s value)
{
	return value;
}

qbyte32s QAudioResampler::convertTo32s(qfloat value)
{

}

qbyte32s QAudioResampler::convertTo32s(qreal value)
{

}

/**********************************************************************
Value conversion - float
**********************************************************************/

qfloat QAudioResampler::convertToFloat(qbyte8u value)
{

}

qfloat QAudioResampler::convertToFloat(qbyte16u value)
{

}

qfloat QAudioResampler::convertToFloat(qbyte32u value)
{

}

qfloat QAudioResampler::convertToFloat(qbyte8s value)
{

}

qfloat QAudioResampler::convertToFloat(qbyte16s value)
{

}

qfloat QAudioResampler::convertToFloat(qbyte32s value)
{

}

qfloat QAudioResampler::convertToFloat(qfloat value)
{
	return value;
}

qfloat QAudioResampler::convertToFloat(qreal value)
{

}

/**********************************************************************
Value conversion - real
**********************************************************************/

qreal QAudioResampler::convertToReal(qbyte8u value)
{

}

qreal QAudioResampler::convertToReal(qbyte16u value)
{

}

qreal QAudioResampler::convertToReal(qbyte32u value)
{

}

qreal QAudioResampler::convertToReal(qbyte8s value)
{

}

qreal QAudioResampler::convertToReal(qbyte16s value)
{

}

qreal QAudioResampler::convertToReal(qbyte32s value)
{

}

qreal QAudioResampler::convertToReal(qfloat value)
{

}

qreal QAudioResampler::convertToReal(qreal value)
{
	return value;
}

/**********************************************************************
Array conversion - unsigned 8
**********************************************************************/

int QAudioResampler::convert(qbyte8u *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qbyte8u *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qbyte8u *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qbyte8u *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qbyte8u *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qbyte8u *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qbyte8u *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qbyte8u *input, qreal *output, int size)
{

}

/**********************************************************************
Array conversion - unsigned 16
**********************************************************************/

int QAudioResampler::convert(qbyte16u *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qbyte16u *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qbyte16u *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qbyte16u *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qbyte16u *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qbyte16u *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qbyte16u *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qbyte16u *input, qreal *output, int size)
{

}

/**********************************************************************
Array conversion - unsigned 32
**********************************************************************/

int QAudioResampler::convert(qbyte32u *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qbyte32u *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qbyte32u *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qbyte32u *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qbyte32u *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qbyte32u *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qbyte32u *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qbyte32u *input, qreal *output, int size)
{

}

/**********************************************************************
Array conversion - signed 8
**********************************************************************/

int QAudioResampler::convert(qbyte8s *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qbyte8s *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qbyte8s *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qbyte8s *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qbyte8s *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qbyte8s *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qbyte8s *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qbyte8s *input, qreal *output, int size)
{

}

/**********************************************************************
Array conversion - signed 16
**********************************************************************/

int QAudioResampler::convert(qbyte16s *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qbyte16s *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qbyte16s *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qbyte16s *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qbyte16s *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qbyte16s *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qbyte16s *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qbyte16s *input, qreal *output, int size)
{

}

/**********************************************************************
Array conversion - signed 32
**********************************************************************/

int QAudioResampler::convert(qbyte32s *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qbyte32s *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qbyte32s *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qbyte32s *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qbyte32s *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qbyte32s *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qbyte32s *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qbyte32s *input, qreal *output, int size)
{

}

/**********************************************************************
Array conversion - float
**********************************************************************/

int QAudioResampler::convert(qfloat *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qfloat *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qfloat *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qfloat *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qfloat *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qfloat *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qfloat *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qfloat *input, qreal *output, int size)
{

}

/**********************************************************************
Array conversion - real
**********************************************************************/

int QAudioResampler::convert(qreal *input, qbyte8u *output, int size)
{

}

int QAudioResampler::convert(qreal *input, qbyte16u *output, int size)
{

}

int QAudioResampler::convert(qreal *input, qbyte32u *output, int size)
{

}

int QAudioResampler::convert(qreal *input, qbyte8s *output, int size)
{

}

int QAudioResampler::convert(qreal *input, qbyte16s *output, int size)
{

}

int QAudioResampler::convert(qreal *input, qbyte32s *output, int size)
{

}

int QAudioResampler::convert(qreal *input, qfloat *output, int size)
{

}

int QAudioResampler::convert(qreal *input, qreal *output, int size)
{

}

