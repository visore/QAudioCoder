#ifndef QSAMPLESIZECONVERTER_H
#define QSAMPLESIZECONVERTER_H

#include <qcommon.h>

class QSampleSizeConverter
{

	public:

		QSampleSizeConverter(){}
		QSampleSizeConverter(int inputSize, int outputSize){}
		void setSampleSize(int inputSize, int outputSize){}
		void (*convert)(void *input, void output, int samples);

		/**********************************************************************
		Value conversion - unsigned 8
		**********************************************************************/

		static qbyte8u convertTo8u(const qbyte8u value);
		static qbyte8u convertTo8u(const qbyte16u value);
		static qbyte8u convertTo8u(const qbyte32u value);
		static qbyte8u convertTo8u(const qbyte8s value);
		static qbyte8u convertTo8u(const qbyte16s value);
		static qbyte8u convertTo8u(const qbyte32s value);
		static qbyte8u convertTo8u(const qfloat value);
		static qbyte8u convertTo8u(const qreal value);

		/**********************************************************************
		Value conversion - unsigned 16
		**********************************************************************/

		static qbyte16u convertTo16u(const qbyte8u value);
		static qbyte16u convertTo16u(const qbyte16u value);
		static qbyte16u convertTo16u(const qbyte32u value);
		static qbyte16u convertTo16u(const qbyte8s value);
		static qbyte16u convertTo16u(const qbyte16s value);
		static qbyte16u convertTo16u(const qbyte32s value);
		static qbyte16u convertTo16u(const qfloat value);
		static qbyte16u convertTo16u(const qreal value);

		/**********************************************************************
		Value conversion - unsigned 32
		**********************************************************************/

		static qbyte32u convertTo32u(const qbyte8u value);
		static qbyte32u convertTo32u(const qbyte16u value);
		static qbyte32u convertTo32u(const qbyte32u value);
		static qbyte32u convertTo32u(const qbyte8s value);
		static qbyte32u convertTo32u(const qbyte16s value);
		static qbyte32u convertTo32u(const qbyte32s value);
		static qbyte32u convertTo32u(const qfloat value);
		static qbyte32u convertTo32u(const qreal value);

		/**********************************************************************
		Value conversion - signed 8
		**********************************************************************/

		static qbyte8s convertTo8s(const qbyte8u value);
		static qbyte8s convertTo8s(const qbyte16u value);
		static qbyte8s convertTo8s(const qbyte32u value);
		static qbyte8s convertTo8s(const qbyte8s value);
		static qbyte8s convertTo8s(const qbyte16s value);
		static qbyte8s convertTo8s(const qbyte32s value);
		static qbyte8s convertTo8s(const qfloat value);
		static qbyte8s convertTo8s(const qreal value);

		/**********************************************************************
		Value conversion - signed 16
		**********************************************************************/

		static qbyte16s convertTo16s(const qbyte8u value);
		static qbyte16s convertTo16s(const qbyte16u value);
		static qbyte16s convertTo16s(const qbyte32u value);
		static qbyte16s convertTo16s(const qbyte8s value);
		static qbyte16s convertTo16s(const qbyte16s value);
		static qbyte16s convertTo16s(const qbyte32s value);
		static qbyte16s convertTo16s(const qfloat value);
		static qbyte16s convertTo16s(const qreal value);

		/**********************************************************************
		Value conversion - signed 32
		**********************************************************************/

		static qbyte32s convertTo32s(const qbyte8u value);
		static qbyte32s convertTo32s(const qbyte16u value);
		static qbyte32s convertTo32s(const qbyte32u value);
		static qbyte32s convertTo32s(const qbyte8s value);
		static qbyte32s convertTo32s(const qbyte16s value);
		static qbyte32s convertTo32s(const qbyte32s value);
		static qbyte32s convertTo32s(const qfloat value);
		static qbyte32s convertTo32s(const qreal value);

		/**********************************************************************
		Value conversion - float
		**********************************************************************/

		static qfloat convertToFloat(const qbyte8u value);
		static qfloat convertToFloat(const qbyte16u value);
		static qfloat convertToFloat(const qbyte32u value);
		static qfloat convertToFloat(const qbyte8s value);
		static qfloat convertToFloat(const qbyte16s value);
		static qfloat convertToFloat(const qbyte32s value);
		static qfloat convertToFloat(const qfloat value);
		static qfloat convertToFloat(const qreal value);

		/**********************************************************************
		Value conversion - real
		**********************************************************************/

		static qreal convertToReal(const qbyte8u value);
		static qreal convertToReal(const qbyte16u value);
		static qreal convertToReal(const qbyte32u value);
		static qreal convertToReal(const qbyte8s value);
		static qreal convertToReal(const qbyte16s value);
		static qreal convertToReal(const qbyte32s value);
		static qreal convertToReal(const qfloat value);
		static qreal convertToReal(const qreal value);

		/**********************************************************************
		Array conversion - unsigned 8
		**********************************************************************/

		static void convert8uTo8u(const void *input, void *output, const int samples);
		static void convert8uTo16u(const void *input, void *output, const int samples);
		static void convert8uTo32u(const void *input, void *output, const int samples);
		static void convert8uTo8s(const void *input, void *output, const int samples);
		static void convert8uTo16s(const void *input, void *output, const int samples);
		static void convert8uTo32s(const void *input, void *output, const int samples);
		static void convert8uToFloat(const void *input, void *output, const int samples);
		static void convert8uToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - unsigned 16
		**********************************************************************/

		static void convert16uTo8u(const void *input, void *output, const int samples);
		static void convert16uTo16u(const void *input, void *output, const int samples);
		static void convert16uTo32u(const void *input, void *output, const int samples);
		static void convert16uTo8s(const void *input, void *output, const int samples);
		static void convert16uTo16s(const void *input, void *output, const int samples);
		static void convert16uTo32s(const void *input, void *output, const int samples);
		static void convert16uToFloat(const void *input, void *output, const int samples);
		static void convert16uToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - unsigned 32
		**********************************************************************/

		static void convert32uTo8u(const void *input, void *output, const int samples);
		static void convert32uTo16u(const void *input, void *output, const int samples);
		static void convert32uTo32u(const void *input, void *output, const int samples);
		static void convert32uTo8s(const void *input, void *output, const int samples);
		static void convert32uTo16s(const void *input, void *output, const int samples);
		static void convert32uTo32s(const void *input, void *output, const int samples);
		static void convert32uToFloat(const void *input, void *output, const int samples);
		static void convert32uToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - signed 8
		**********************************************************************/

		static void convert8sTo8u(const void *input, void *output, const int samples);
		static void convert8sTo16u(const void *input, void *output, const int samples);
		static void convert8sTo32u(const void *input, void *output, const int samples);
		static void convert8sTo8s(const void *input, void *output, const int samples);
		static void convert8sTo16s(const void *input, void *output, const int samples);
		static void convert8sTo32s(const void *input, void *output, const int samples);
		static void convert8sToFloat(const void *input, void *output, const int samples);
		static void convert8sToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - signed 16
		**********************************************************************/

		static void convert16sTo8u(const void *input, void *output, const int samples);
		static void convert16sTo16u(const void *input, void *output, const int samples);
		static void convert16sTo32u(const void *input, void *output, const int samples);
		static void convert16sTo8s(const void *input, void *output, const int samples);
		static void convert16sTo16s(const void *input, void *output, const int samples);
		static void convert16sTo32s(const void *input, void *output, const int samples);
		static void convert16sToFloat(const void *input, void *output, const int samples);
		static void convert16sToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - signed 32
		**********************************************************************/

		static void convert32sTo8u(const void *input, void *output, const int samples);
		static void convert32sTo16u(const void *input, void *output, const int samples);
		static void convert32sTo32u(const void *input, void *output, const int samples);
		static void convert32sTo8s(const void *input, void *output, const int samples);
		static void convert32sTo16s(const void *input, void *output, const int samples);
		static void convert32sTo32s(const void *input, void *output, const int samples);
		static void convert32sToFloat(const void *input, void *output, const int samples);
		static void convert32sToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - float
		**********************************************************************/

		static void convertFloatTo8u(const void *input, void *output, const int samples);
		static void convertFloatTo16u(const void *input, void *output, const int samples);
		static void convertFloatTo32u(const void *input, void *output, const int samples);
		static void convertFloatTo8s(const void *input, void *output, const int samples);
		static void convertFloatTo16s(const void *input, void *output, const int samples);
		static void convertFloatTo32s(const void *input, void *output, const int samples);
		static void convertFloatToFloat(const void *input, void *output, const int samples);
		static void convertFloatToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - real
		**********************************************************************/

		static void convertRealTo8u(const void *input, void *output, const int samples);
		static void convertRealTo16u(const void *input, void *output, const int samples);
		static void convertRealTo32u(const void *input, void *output, const int samples);
		static void convertRealTo8s(const void *input, void *output, const int samples);
		static void convertRealTo16s(const void *input, void *output, const int samples);
		static void convertRealTo32s(const void *input, void *output, const int samples);
		static void convertRealToFloat(const void *input, void *output, const int samples);
		static void convertRealToReal(const void *input, void *output, const int samples);

		/**********************************************************************
		Array conversion - unsigned 8
		**********************************************************************/

		static void convert(const qbyte8u *input, qbyte8u *output, const int samples);
		static void convert(const qbyte8u *input, qbyte16u *output, const int samples);
		static void convert(const qbyte8u *input, qbyte32u *output, const int samples);
		static void convert(const qbyte8u *input, qbyte8s *output, const int samples);
		static void convert(const qbyte8u *input, qbyte16s *output, const int samples);
		static void convert(const qbyte8u *input, qbyte32s *output, const int samples);
		static void convert(const qbyte8u *input, qfloat *output, const int samples);
		static void convert(const qbyte8u *input, qreal *output, const int samples);

		/**********************************************************************
		Array conversion - unsigned 16
		**********************************************************************/

		static void convert(const qbyte16u *input, qbyte8u *output, const int samples);
		static void convert(const qbyte16u *input, qbyte16u *output, const int samples);
		static void convert(const qbyte16u *input, qbyte32u *output, const int samples);
		static void convert(const qbyte16u *input, qbyte8s *output, const int samples);
		static void convert(const qbyte16u *input, qbyte16s *output, const int samples);
		static void convert(const qbyte16u *input, qbyte32s *output, const int samples);
		static void convert(const qbyte16u *input, qfloat *output, const int samples);
		static void convert(const qbyte16u *input, qreal *output, const int samples);

		/**********************************************************************
		Array conversion - unsigned 32
		**********************************************************************/

		static void convert(const qbyte32u *input, qbyte8u *output, const int samples);
		static void convert(const qbyte32u *input, qbyte16u *output, const int samples);
		static void convert(const qbyte32u *input, qbyte32u *output, const int samples);
		static void convert(const qbyte32u *input, qbyte8s *output, const int samples);
		static void convert(const qbyte32u *input, qbyte16s *output, const int samples);
		static void convert(const qbyte32u *input, qbyte32s *output, const int samples);
		static void convert(const qbyte32u *input, qfloat *output, const int samples);
		static void convert(const qbyte32u *input, qreal *output, const int samples);

		/**********************************************************************
		Array conversion - signed 8
		**********************************************************************/

		static void convert(const qbyte8s *input, qbyte8u *output, const int samples);
		static void convert(const qbyte8s *input, qbyte16u *output, const int samples);
		static void convert(const qbyte8s *input, qbyte32u *output, const int samples);
		static void convert(const qbyte8s *input, qbyte8s *output, const int samples);
		static void convert(const qbyte8s *input, qbyte16s *output, const int samples);
		static void convert(const qbyte8s *input, qbyte32s *output, const int samples);
		static void convert(const qbyte8s *input, qfloat *output, const int samples);
		static void convert(const qbyte8s *input, qreal *output, const int samples);

		/**********************************************************************
		Array conversion - signed 16
		**********************************************************************/

		static void convert(const qbyte16s *input, qbyte8u *output, const int samples);
		static void convert(const qbyte16s *input, qbyte16u *output, const int samples);
		static void convert(const qbyte16s *input, qbyte32u *output, const int samples);
		static void convert(const qbyte16s *input, qbyte8s *output, const int samples);
		static void convert(const qbyte16s *input, qbyte16s *output, const int samples);
		static void convert(const qbyte16s *input, qbyte32s *output, const int samples);
		static void convert(const qbyte16s *input, qfloat *output, const int samples);
		static void convert(const qbyte16s *input, qreal *output, const int samples);

		/**********************************************************************
		Array conversion - signed 32
		**********************************************************************/

		static void convert(const qbyte32s *input, qbyte8u *output, const int samples);
		static void convert(const qbyte32s *input, qbyte16u *output, const int samples);
		static void convert(const qbyte32s *input, qbyte32u *output, const int samples);
		static void convert(const qbyte32s *input, qbyte8s *output, const int samples);
		static void convert(const qbyte32s *input, qbyte16s *output, const int samples);
		static void convert(const qbyte32s *input, qbyte32s *output, const int samples);
		static void convert(const qbyte32s *input, qfloat *output, const int samples);
		static void convert(const qbyte32s *input, qreal *output, const int samples);

		/**********************************************************************
		Array conversion - float
		**********************************************************************/

		static void convert(const qfloat *input, qbyte8u *output, const int samples);
		static void convert(const qfloat *input, qbyte16u *output, const int samples);
		static void convert(const qfloat *input, qbyte32u *output, const int samples);
		static void convert(const qfloat *input, qbyte8s *output, const int samples);
		static void convert(const qfloat *input, qbyte16s *output, const int samples);
		static void convert(const qfloat *input, qbyte32s *output, const int samples);
		static void convert(const qfloat *input, qfloat *output, const int samples);
		static void convert(const qfloat *input, qreal *output, const int samples);

		/**********************************************************************
		Array conversion - real
		**********************************************************************/

		static void convert(const qreal *input, qbyte8u *output, const int samples);
		static void convert(const qreal *input, qbyte16u *output, const int samples);
		static void convert(const qreal *input, qbyte32u *output, const int samples);
		static void convert(const qreal *input, qbyte8s *output, const int samples);
		static void convert(const qreal *input, qbyte16s *output, const int samples);
		static void convert(const qreal *input, qbyte32s *output, const int samples);
		static void convert(const qreal *input, qfloat *output, const int samples);
		static void convert(const qreal *input, qreal *output, const int samples);

};

#endif
