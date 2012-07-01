#ifndef QSAMPLECONVERTER_H
#define QSAMPLECONVERTER_H

#include <QtGlobal>

typedef unsigned char qbyte8u;
typedef unsigned short qbyte16u;
typedef unsigned int qbyte32u;
typedef qbyte8u qbyteu;

typedef signed char qbyte8s;
typedef signed short qbyte16s;
typedef signed int qbyte32s;
typedef qbyte8s qbytes;

typedef qbyte8u qbyte8;
typedef qbyte16u qbyte16;
typedef qbyte32u qbyte32;
typedef qbyte8 qbyte;

typedef float qfloat;

class QSampleConverter
{

	public:

		static void test();

		/**********************************************************************
		Value conversion - unsigned 8
		**********************************************************************/

		static qbyte8u convertTo8u(qbyte8u value);
		static qbyte8u convertTo8u(qbyte16u value);
		static qbyte8u convertTo8u(qbyte32u value);
		static qbyte8u convertTo8u(qbyte8s value);
		static qbyte8u convertTo8u(qbyte16s value);
		static qbyte8u convertTo8u(qbyte32s value);
		static qbyte8u convertTo8u(qfloat value);
		static qbyte8u convertTo8u(qreal value);

		/**********************************************************************
		Value conversion - unsigned 16
		**********************************************************************/

		static qbyte16u convertTo16u(qbyte8u value);
		static qbyte16u convertTo16u(qbyte16u value);
		static qbyte16u convertTo16u(qbyte32u value);
		static qbyte16u convertTo16u(qbyte8s value);
		static qbyte16u convertTo16u(qbyte16s value);
		static qbyte16u convertTo16u(qbyte32s value);
		static qbyte16u convertTo16u(qfloat value);
		static qbyte16u convertTo16u(qreal value);

		/**********************************************************************
		Value conversion - unsigned 32
		**********************************************************************/

		static qbyte32u convertTo32u(qbyte8u value);
		static qbyte32u convertTo32u(qbyte16u value);
		static qbyte32u convertTo32u(qbyte32u value);
		static qbyte32u convertTo32u(qbyte8s value);
		static qbyte32u convertTo32u(qbyte16s value);
		static qbyte32u convertTo32u(qbyte32s value);
		static qbyte32u convertTo32u(qfloat value);
		static qbyte32u convertTo32u(qreal value);

		/**********************************************************************
		Value conversion - signed 8
		**********************************************************************/

		static qbyte8s convertTo8s(qbyte8u value);
		static qbyte8s convertTo8s(qbyte16u value);
		static qbyte8s convertTo8s(qbyte32u value);
		static qbyte8s convertTo8s(qbyte8s value);
		static qbyte8s convertTo8s(qbyte16s value);
		static qbyte8s convertTo8s(qbyte32s value);
		static qbyte8s convertTo8s(qfloat value);
		static qbyte8s convertTo8s(qreal value);

		/**********************************************************************
		Value conversion - signed 16
		**********************************************************************/

		static qbyte16s convertTo16s(qbyte8u value);
		static qbyte16s convertTo16s(qbyte16u value);
		static qbyte16s convertTo16s(qbyte32u value);
		static qbyte16s convertTo16s(qbyte8s value);
		static qbyte16s convertTo16s(qbyte16s value);
		static qbyte16s convertTo16s(qbyte32s value);
		static qbyte16s convertTo16s(qfloat value);
		static qbyte16s convertTo16s(qreal value);

		/**********************************************************************
		Value conversion - signed 32
		**********************************************************************/

		static qbyte32s convertTo32s(qbyte8u value);
		static qbyte32s convertTo32s(qbyte16u value);
		static qbyte32s convertTo32s(qbyte32u value);
		static qbyte32s convertTo32s(qbyte8s value);
		static qbyte32s convertTo32s(qbyte16s value);
		static qbyte32s convertTo32s(qbyte32s value);
		static qbyte32s convertTo32s(qfloat value);
		static qbyte32s convertTo32s(qreal value);

		/**********************************************************************
		Value conversion - float
		**********************************************************************/

		static qfloat convertToFloat(qbyte8u value);
		static qfloat convertToFloat(qbyte16u value);
		static qfloat convertToFloat(qbyte32u value);
		static qfloat convertToFloat(qbyte8s value);
		static qfloat convertToFloat(qbyte16s value);
		static qfloat convertToFloat(qbyte32s value);
		static qfloat convertToFloat(qfloat value);
		static qfloat convertToFloat(qreal value);

		/**********************************************************************
		Value conversion - real
		**********************************************************************/

		static qreal convertToReal(qbyte8u value);
		static qreal convertToReal(qbyte16u value);
		static qreal convertToReal(qbyte32u value);
		static qreal convertToReal(qbyte8s value);
		static qreal convertToReal(qbyte16s value);
		static qreal convertToReal(qbyte32s value);
		static qreal convertToReal(qfloat value);
		static qreal convertToReal(qreal value);

		/**********************************************************************
		Array conversion - unsigned 8
		**********************************************************************/

		static void convert(qbyte8u *input, qbyte8u *output, int size);
		static void convert(qbyte8u *input, qbyte16u *output, int size);
		static void convert(qbyte8u *input, qbyte32u *output, int size);
		static void convert(qbyte8u *input, qbyte8s *output, int size);
		static void convert(qbyte8u *input, qbyte16s *output, int size);
		static void convert(qbyte8u *input, qbyte32s *output, int size);
		static void convert(qbyte8u *input, qfloat *output, int size);
		static void convert(qbyte8u *input, qreal *output, int size);

		/**********************************************************************
		Array conversion - unsigned 16
		**********************************************************************/

		static void convert(qbyte16u *input, qbyte8u *output, int size);
		static void convert(qbyte16u *input, qbyte16u *output, int size);
		static void convert(qbyte16u *input, qbyte32u *output, int size);
		static void convert(qbyte16u *input, qbyte8s *output, int size);
		static void convert(qbyte16u *input, qbyte16s *output, int size);
		static void convert(qbyte16u *input, qbyte32s *output, int size);
		static void convert(qbyte16u *input, qfloat *output, int size);
		static void convert(qbyte16u *input, qreal *output, int size);

		/**********************************************************************
		Array conversion - unsigned 32
		**********************************************************************/

		static void convert(qbyte32u *input, qbyte8u *output, int size);
		static void convert(qbyte32u *input, qbyte16u *output, int size);
		static void convert(qbyte32u *input, qbyte32u *output, int size);
		static void convert(qbyte32u *input, qbyte8s *output, int size);
		static void convert(qbyte32u *input, qbyte16s *output, int size);
		static void convert(qbyte32u *input, qbyte32s *output, int size);
		static void convert(qbyte32u *input, qfloat *output, int size);
		static void convert(qbyte32u *input, qreal *output, int size);

		/**********************************************************************
		Array conversion - signed 8
		**********************************************************************/

		static void convert(qbyte8s *input, qbyte8u *output, int size);
		static void convert(qbyte8s *input, qbyte16u *output, int size);
		static void convert(qbyte8s *input, qbyte32u *output, int size);
		static void convert(qbyte8s *input, qbyte8s *output, int size);
		static void convert(qbyte8s *input, qbyte16s *output, int size);
		static void convert(qbyte8s *input, qbyte32s *output, int size);
		static void convert(qbyte8s *input, qfloat *output, int size);
		static void convert(qbyte8s *input, qreal *output, int size);

		/**********************************************************************
		Array conversion - signed 16
		**********************************************************************/

		static void convert(qbyte16s *input, qbyte8u *output, int size);
		static void convert(qbyte16s *input, qbyte16u *output, int size);
		static void convert(qbyte16s *input, qbyte32u *output, int size);
		static void convert(qbyte16s *input, qbyte8s *output, int size);
		static void convert(qbyte16s *input, qbyte16s *output, int size);
		static void convert(qbyte16s *input, qbyte32s *output, int size);
		static void convert(qbyte16s *input, qfloat *output, int size);
		static void convert(qbyte16s *input, qreal *output, int size);

		/**********************************************************************
		Array conversion - signed 32
		**********************************************************************/

		static void convert(qbyte32s *input, qbyte8u *output, int size);
		static void convert(qbyte32s *input, qbyte16u *output, int size);
		static void convert(qbyte32s *input, qbyte32u *output, int size);
		static void convert(qbyte32s *input, qbyte8s *output, int size);
		static void convert(qbyte32s *input, qbyte16s *output, int size);
		static void convert(qbyte32s *input, qbyte32s *output, int size);
		static void convert(qbyte32s *input, qfloat *output, int size);
		static void convert(qbyte32s *input, qreal *output, int size);

		/**********************************************************************
		Array conversion - float
		**********************************************************************/

		static void convert(qfloat *input, qbyte8u *output, int size);
		static void convert(qfloat *input, qbyte16u *output, int size);
		static void convert(qfloat *input, qbyte32u *output, int size);
		static void convert(qfloat *input, qbyte8s *output, int size);
		static void convert(qfloat *input, qbyte16s *output, int size);
		static void convert(qfloat *input, qbyte32s *output, int size);
		static void convert(qfloat *input, qfloat *output, int size);
		static void convert(qfloat *input, qreal *output, int size);

		/**********************************************************************
		Array conversion - real
		**********************************************************************/

		static void convert(qreal *input, qbyte8u *output, int size);
		static void convert(qreal *input, qbyte16u *output, int size);
		static void convert(qreal *input, qbyte32u *output, int size);
		static void convert(qreal *input, qbyte8s *output, int size);
		static void convert(qreal *input, qbyte16s *output, int size);
		static void convert(qreal *input, qbyte32s *output, int size);
		static void convert(qreal *input, qfloat *output, int size);
		static void convert(qreal *input, qreal *output, int size);

};

#endif
