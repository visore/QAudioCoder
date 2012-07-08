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

QSampleSizeConverter::QSampleSizeConverter()
{
	convert = NULL;
}

QSampleSizeConverter::QSampleSizeConverter(int inputSize, QExtendedAudioFormat::SampleType inputType, int outputSize, QExtendedAudioFormat::SampleType outputType)
{
	QSampleSizeConverter();
	initialize(inputSize, inputType, outputSize, outputType);
}

bool QSampleSizeConverter::initialize(int inputSize, QExtendedAudioFormat::SampleType inputType, int outputSize, QExtendedAudioFormat::SampleType outputType)
{
	convert = NULL;
	if(inputType == QExtendedAudioFormat::SignedInt)
	{
		if(outputType == QExtendedAudioFormat::SignedInt)
		{
			if(inputSize == 8)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert8sTo8s;
				if(outputSize == 16) convert = &QSampleSizeConverter::convert8sTo16s;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert8sTo32s;
			}
			else if(inputSize == 16)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert16sTo8s;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert16sTo16s;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert16sTo32s;
			}
			else if(inputSize == 32)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert32sTo8s;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert32sTo16s;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert32sTo32s;
			}
		}
		else if(outputType == QExtendedAudioFormat::UnSignedInt)
		{
			if(inputSize == 8)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert8sTo8u;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert8sTo16u;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert8sTo32u;
			}
			else if(inputSize == 16)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert16sTo8u;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert16sTo16u;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert16sTo32u;
			}
			else if(inputSize == 32)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert32sTo8u;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert32sTo16u;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert32sTo32u;
			}
		}
		else if(outputType == QExtendedAudioFormat::Float)
		{
			if(inputSize == 8) convert = &QSampleSizeConverter::convert8sToFloat;
			else if(inputSize == 16) convert = &QSampleSizeConverter::convert16sToFloat;
			else if(inputSize == 32) convert = &QSampleSizeConverter::convert32sToFloat;
		}
		else if(outputType == QExtendedAudioFormat::Real)
		{
			if(inputSize == 8) convert = &QSampleSizeConverter::convert8sToReal;
			else if(inputSize == 16) convert = &QSampleSizeConverter::convert16sToReal;
			else if(inputSize == 32) convert = &QSampleSizeConverter::convert32sToReal;
		}
	}
	else if(inputType == QExtendedAudioFormat::UnSignedInt)
	{
		if(outputType == QExtendedAudioFormat::SignedInt)
		{
			if(inputSize == 8)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert8uTo8s;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert8uTo16s;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert8uTo32s;
			}
			else if(inputSize == 16)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert16uTo8s;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert16uTo16s;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert16uTo32s;
			}
			else if(inputSize == 32)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert32uTo8s;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert32uTo16s;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert32uTo32s;
			}
		}
		else if(outputType == QExtendedAudioFormat::UnSignedInt)
		{
			if(inputSize == 8)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert8uTo8u;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert8uTo16u;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert8uTo32u;
			}
			else if(inputSize == 16)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert16uTo8u;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert16uTo16u;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert16uTo32u;
			}
			else if(inputSize == 32)
			{
				if(outputSize == 8) convert = &QSampleSizeConverter::convert32uTo8u;
				else if(outputSize == 16) convert = &QSampleSizeConverter::convert32uTo16u;
				else if(outputSize == 32) convert = &QSampleSizeConverter::convert32uTo32u;
			}
		}
		else if(outputType == QExtendedAudioFormat::Float)
		{
			if(inputSize == 8) convert = &QSampleSizeConverter::convert8uToFloat;
			else if(inputSize == 16) convert = &QSampleSizeConverter::convert16uToFloat;
			else if(inputSize == 32) convert = &QSampleSizeConverter::convert32uToFloat;
		}
		else if(outputType == QExtendedAudioFormat::Real)
		{
			if(inputSize == 8) convert = &QSampleSizeConverter::convert8uToReal;
			else if(inputSize == 16) convert = &QSampleSizeConverter::convert16uToReal;
			else if(inputSize == 32) convert = &QSampleSizeConverter::convert32uToReal;
		}
	}
	else if(inputType == QExtendedAudioFormat::Float)
	{
		if(outputType == QExtendedAudioFormat::SignedInt)
		{
			if(outputSize == 8) convert = &QSampleSizeConverter::convertFloatTo8s;
			else if(outputSize == 16) convert = &QSampleSizeConverter::convertFloatTo16s;
			else if(outputSize == 32) convert = &QSampleSizeConverter::convertFloatTo32s;
		}
		else if(outputType == QExtendedAudioFormat::UnSignedInt)
		{
			if(outputSize == 8) convert = &QSampleSizeConverter::convertFloatTo8u;
			else if(outputSize == 16) convert = &QSampleSizeConverter::convertFloatTo16u;
			else if(outputSize == 32) convert = &QSampleSizeConverter::convertFloatTo32u;
		}
		else if(outputType == QExtendedAudioFormat::Float)
		{
			convert = &QSampleSizeConverter::convertFloatToReal;
		}
		else if(outputType == QExtendedAudioFormat::Real)
		{
			convert = &QSampleSizeConverter::convertFloatToFloat;
		}
	}
	else if(inputType == QExtendedAudioFormat::Real)
	{
		if(outputType == QExtendedAudioFormat::SignedInt)
		{
			if(outputSize == 8) convert = &QSampleSizeConverter::convertRealTo8s;
			else if(outputSize == 16) convert = &QSampleSizeConverter::convertRealTo16s;
			else if(outputSize == 32) convert = &QSampleSizeConverter::convertRealTo32s;
		}
		else if(outputType == QExtendedAudioFormat::UnSignedInt)
		{
			if(outputSize == 8) convert = &QSampleSizeConverter::convertRealTo8u;
			else if(outputSize == 16) convert = &QSampleSizeConverter::convertRealTo16u;
			else if(outputSize == 32) convert = &QSampleSizeConverter::convertRealTo32u;
		}
		else if(outputType == QExtendedAudioFormat::Float)
		{
			convert = &QSampleSizeConverter::convertRealToFloat;
		}
		else if(outputType == QExtendedAudioFormat::Real)
		{
			convert = &QSampleSizeConverter::convertRealToReal;
		}
	}

	return convert != NULL;
}


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
	memcpy(output, input, samples * sizeof(qbyte8u));
}

void QSampleSizeConverter::convert8uTo16u(const void *input, void *output, const int samples)
{
	qbyte8u *inputData = (qbyte8u*) input;
	qbyte16u *outputData = (qbyte16u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16u(inputData[i]);
	}
}

void QSampleSizeConverter::convert8uTo32u(const void *input, void *output, const int samples)
{
	qbyte8u *inputData = (qbyte8u*) input;
	qbyte32u *outputData = (qbyte32u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32u(inputData[i]);
	}
}

void QSampleSizeConverter::convert8uTo8s(const void *input, void *output, const int samples)
{
	qbyte8u *inputData = (qbyte8u*) input;
	qbyte8s *outputData = (qbyte8s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8s(inputData[i]);
	}
}

void QSampleSizeConverter::convert8uTo16s(const void *input, void *output, const int samples)
{
	qbyte8u *inputData = (qbyte8u*) input;
	qbyte16s *outputData = (qbyte16s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16s(inputData[i]);
	}
}

void QSampleSizeConverter::convert8uTo32s(const void *input, void *output, const int samples)
{
	qbyte8u *inputData = (qbyte8u*) input;
	qbyte32s *outputData = (qbyte32s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32s(inputData[i]);
	}
}

void QSampleSizeConverter::convert8uToFloat(const void *input, void *output, const int samples)
{
	qbyte8u *inputData = (qbyte8u*) input;
	qfloat *outputData = (qfloat*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToFloat(inputData[i]);
	}
}

void QSampleSizeConverter::convert8uToReal(const void *input, void *output, const int samples)
{
	qbyte8u *inputData = (qbyte8u*) input;
	qreal *outputData = (qreal*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToReal(inputData[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 16
**********************************************************************/

void QSampleSizeConverter::convert16uTo8u(const void *input, void *output, const int samples)
{
	qbyte16u *inputData = (qbyte16u*) input;
	qbyte8u *outputData = (qbyte8u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8u(inputData[i]);
	}
}

void QSampleSizeConverter::convert16uTo16u(const void *input, void *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte16u));
}

void QSampleSizeConverter::convert16uTo32u(const void *input, void *output, const int samples)
{
	qbyte16u *inputData = (qbyte16u*) input;
	qbyte32u *outputData = (qbyte32u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32u(inputData[i]);
	}
}

void QSampleSizeConverter::convert16uTo8s(const void *input, void *output, const int samples)
{
	qbyte16u *inputData = (qbyte16u*) input;
	qbyte8s *outputData = (qbyte8s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8s(inputData[i]);
	}
}

void QSampleSizeConverter::convert16uTo16s(const void *input, void *output, const int samples)
{
	qbyte16u *inputData = (qbyte16u*) input;
	qbyte16s *outputData = (qbyte16s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16s(inputData[i]);
	}
}

void QSampleSizeConverter::convert16uTo32s(const void *input, void *output, const int samples)
{
	qbyte16u *inputData = (qbyte16u*) input;
	qbyte32s *outputData = (qbyte32s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32s(inputData[i]);
	}
}

void QSampleSizeConverter::convert16uToFloat(const void *input, void *output, const int samples)
{
	qbyte16u *inputData = (qbyte16u*) input;
	qfloat *outputData = (qfloat*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToFloat(inputData[i]);
	}
}

void QSampleSizeConverter::convert16uToReal(const void *input, void *output, const int samples)
{
	qbyte16u *inputData = (qbyte16u*) input;
	qreal *outputData = (qreal*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToReal(inputData[i]);
	}
}

/**********************************************************************
Array conversion - unsigned 32
**********************************************************************/

void QSampleSizeConverter::convert32uTo8u(const void *input, void *output, const int samples)
{
	qbyte32u *inputData = (qbyte32u*) input;
	qbyte8u *outputData = (qbyte8u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8u(inputData[i]);
	}
}

void QSampleSizeConverter::convert32uTo16u(const void *input, void *output, const int samples)
{
	qbyte32u *inputData = (qbyte32u*) input;
	qbyte16u *outputData = (qbyte16u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16u(inputData[i]);
	}
}

void QSampleSizeConverter::convert32uTo32u(const void *input, void *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte32u));
}

void QSampleSizeConverter::convert32uTo8s(const void *input, void *output, const int samples)
{
	qbyte32u *inputData = (qbyte32u*) input;
	qbyte8s *outputData = (qbyte8s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8s(inputData[i]);
	}
}

void QSampleSizeConverter::convert32uTo16s(const void *input, void *output, const int samples)
{
	qbyte32u *inputData = (qbyte32u*) input;
	qbyte16s *outputData = (qbyte16s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16s(inputData[i]);
	}
}

void QSampleSizeConverter::convert32uTo32s(const void *input, void *output, const int samples)
{
	qbyte32u *inputData = (qbyte32u*) input;
	qbyte32s *outputData = (qbyte32s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32s(inputData[i]);
	}
}

void QSampleSizeConverter::convert32uToFloat(const void *input, void *output, const int samples)
{
	qbyte32u *inputData = (qbyte32u*) input;
	qfloat *outputData = (qfloat*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToFloat(inputData[i]);
	}
}

void QSampleSizeConverter::convert32uToReal(const void *input, void *output, const int samples)
{
	qbyte32u *inputData = (qbyte32u*) input;
	qreal *outputData = (qreal*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToReal(inputData[i]);
	}
}

/**********************************************************************
Array conversion - signed 8
**********************************************************************/

void QSampleSizeConverter::convert8sTo8u(const void *input, void *output, const int samples)
{
	qbyte8s *inputData = (qbyte8s*) input;
	qbyte8u *outputData = (qbyte8u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8u(inputData[i]);
	}
}

void QSampleSizeConverter::convert8sTo16u(const void *input, void *output, const int samples)
{
	qbyte8s *inputData = (qbyte8s*) input;
	qbyte16u *outputData = (qbyte16u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16u(inputData[i]);
	}
}

void QSampleSizeConverter::convert8sTo32u(const void *input, void *output, const int samples)
{
	qbyte8s *inputData = (qbyte8s*) input;
	qbyte32u *outputData = (qbyte32u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32u(inputData[i]);
	}
}

void QSampleSizeConverter::convert8sTo8s(const void *input, void *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte8s));
}

void QSampleSizeConverter::convert8sTo16s(const void *input, void *output, const int samples)
{
	qbyte8s *inputData = (qbyte8s*) input;
	qbyte16s *outputData = (qbyte16s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16s(inputData[i]);
	}
}

void QSampleSizeConverter::convert8sTo32s(const void *input, void *output, const int samples)
{
	qbyte8s *inputData = (qbyte8s*) input;
	qbyte32s *outputData = (qbyte32s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32s(inputData[i]);
	}
}

void QSampleSizeConverter::convert8sToFloat(const void *input, void *output, const int samples)
{
	qbyte8s *inputData = (qbyte8s*) input;
	qfloat *outputData = (qfloat*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToFloat(inputData[i]);
	}
}

void QSampleSizeConverter::convert8sToReal(const void *input, void *output, const int samples)
{
	qbyte8s *inputData = (qbyte8s*) input;
	qreal *outputData = (qreal*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToReal(inputData[i]);
	}
}

/**********************************************************************
Array conversion - signed 16
**********************************************************************/

void QSampleSizeConverter::convert16sTo8u(const void *input, void *output, const int samples)
{
	qbyte16s *inputData = (qbyte16s*) input;
	qbyte8u *outputData = (qbyte8u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8u(inputData[i]);
	}
}

void QSampleSizeConverter::convert16sTo16u(const void *input, void *output, const int samples)
{
	qbyte16s *inputData = (qbyte16s*) input;
	qbyte16u *outputData = (qbyte16u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16u(inputData[i]);
	}
}

void QSampleSizeConverter::convert16sTo32u(const void *input, void *output, const int samples)
{
	qbyte16s *inputData = (qbyte16s*) input;
	qbyte32u *outputData = (qbyte32u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32u(inputData[i]);
	}
}

void QSampleSizeConverter::convert16sTo8s(const void *input, void *output, const int samples)
{
	qbyte16s *inputData = (qbyte16s*) input;
	qbyte8s *outputData = (qbyte8s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8s(inputData[i]);
	}
}

void QSampleSizeConverter::convert16sTo16s(const void *input, void *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte16s));
}

void QSampleSizeConverter::convert16sTo32s(const void *input, void *output, const int samples)
{
	qbyte16s *inputData = (qbyte16s*) input;
	qbyte32s *outputData = (qbyte32s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32s(inputData[i]);
	}
}

void QSampleSizeConverter::convert16sToFloat(const void *input, void *output, const int samples)
{
	qbyte16s *inputData = (qbyte16s*) input;
	 qfloat *outputData = ( qfloat*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToFloat(inputData[i]);
	}
}

void QSampleSizeConverter::convert16sToReal(const void *input, void *output, const int samples)
{
	qbyte16s *inputData = (qbyte16s*) input;
	qreal *outputData = (qreal*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToReal(inputData[i]);
	}
}

/**********************************************************************
Array conversion - signed 32
**********************************************************************/

void QSampleSizeConverter::convert32sTo8u(const void *input, void *output, const int samples)
{
	qbyte32s *inputData = (qbyte32s*) input;
	qbyte8u *outputData = (qbyte8u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8u(inputData[i]);
	}
}

void QSampleSizeConverter::convert32sTo16u(const void *input, void *output, const int samples)
{
	qbyte32s *inputData = (qbyte32s*) input;
	qbyte16u *outputData = (qbyte16u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16u(inputData[i]);
	}
}

void QSampleSizeConverter::convert32sTo32u(const void *input, void *output, const int samples)
{
	qbyte32s *inputData = (qbyte32s*) input;
	qbyte32u *outputData = (qbyte32u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32u(inputData[i]);
	}
}

void QSampleSizeConverter::convert32sTo8s(const void *input, void *output, const int samples)
{
	qbyte32s *inputData = (qbyte32s*) input;
	qbyte8s *outputData = (qbyte8s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8s(inputData[i]);
	}
}

void QSampleSizeConverter::convert32sTo16s(const void *input, void *output, const int samples)
{
	qbyte32s *inputData = (qbyte32s*) input;
	qbyte16s *outputData = (qbyte16s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16s(inputData[i]);
	}
}

void QSampleSizeConverter::convert32sTo32s(const void *input, void *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qbyte32s));
}

void QSampleSizeConverter::convert32sToFloat(const void *input, void *output, const int samples)
{
	qbyte32s *inputData = (qbyte32s*) input;
	qfloat *outputData = (qfloat*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToFloat(inputData[i]);
	}
}

void QSampleSizeConverter::convert32sToReal(const void *input, void *output, const int samples)
{
	qbyte32s *inputData = (qbyte32s*) input;
	qreal *outputData = (qreal*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToReal(inputData[i]);
	}
}

/**********************************************************************
Array conversion - float
**********************************************************************/

void QSampleSizeConverter::convertFloatTo8u(const void *input, void *output, const int samples)
{
	qfloat *inputData = (qfloat*) input;
	qbyte8u *outputData = (qbyte8u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8u(inputData[i]);
	}
}

void QSampleSizeConverter::convertFloatTo16u(const void *input, void *output, const int samples)
{
	qfloat *inputData = (qfloat*) input;
	qbyte16u *outputData = (qbyte16u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16u(inputData[i]);
	}
}

void QSampleSizeConverter::convertFloatTo32u(const void *input, void *output, const int samples)
{
	qfloat *inputData = (qfloat*) input;
	qbyte32u *outputData = (qbyte32u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32u(inputData[i]);
	}
}

void QSampleSizeConverter::convertFloatTo8s(const void *input, void *output, const int samples)
{
	qfloat *inputData = (qfloat*) input;
	qbyte8s *outputData = (qbyte8s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8s(inputData[i]);
	}
}

void QSampleSizeConverter::convertFloatTo16s(const void *input, void *output, const int samples)
{
	qfloat *inputData = (qfloat*) input;
	qbyte16s *outputData = (qbyte16s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16s(inputData[i]);
	}
}

void QSampleSizeConverter::convertFloatTo32s(const void *input, void *output, const int samples)
{
	qfloat *inputData = (qfloat*) input;
	qbyte32s *outputData = (qbyte32s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32s(inputData[i]);
	}
}

void QSampleSizeConverter::convertFloatToFloat(const void *input, void *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qfloat));
}

void QSampleSizeConverter::convertFloatToReal(const void *input, void *output, const int samples)
{
	qfloat *inputData = (qfloat*) input;
	qreal *outputData = (qreal*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToReal(inputData[i]);
	}
}

/**********************************************************************
Array conversion - real
**********************************************************************/

void QSampleSizeConverter::convertRealTo8u(const void *input, void *output, const int samples)
{
	qreal *inputData = (qreal*) input;
	qbyte8u *outputData = (qbyte8u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8u(inputData[i]);
	}
}

void QSampleSizeConverter::convertRealTo16u(const void *input, void *output, const int samples)
{
	qreal *inputData = (qreal*) input;
	qbyte16u *outputData = (qbyte16u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16u(inputData[i]);
	}
}

void QSampleSizeConverter::convertRealTo32u(const void *input, void *output, const int samples)
{
	qreal *inputData = (qreal*) input;
	qbyte32u *outputData = (qbyte32u*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32u(inputData[i]);
	}
}

void QSampleSizeConverter::convertRealTo8s(const void *input, void *output, const int samples)
{
	qreal *inputData = (qreal*) input;
	qbyte8s *outputData = (qbyte8s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo8s(inputData[i]);
	}
}

void QSampleSizeConverter::convertRealTo16s(const void *input, void *output, const int samples)
{
	qreal *inputData = (qreal*) input;
	qbyte16s *outputData = (qbyte16s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo16s(inputData[i]);
	}
}

void QSampleSizeConverter::convertRealTo32s(const void *input, void *output, const int samples)
{
	qreal *inputData = (qreal*) input;
	qbyte32s *outputData = (qbyte32s*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertTo32s(inputData[i]);
	}
}

void QSampleSizeConverter::convertRealToFloat(const void *input, void *output, const int samples)
{
	qreal *inputData = (qreal*) input;
	qfloat *outputData = (qfloat*) output;
	for(int i = 0; i < samples; ++i)
	{
		outputData[i] = QSampleSizeConverter::convertToFloat(inputData[i]);
	}
}

void QSampleSizeConverter::convertRealToReal(const void *input, void *output, const int samples)
{
	memcpy(output, input, samples * sizeof(qreal));
}

