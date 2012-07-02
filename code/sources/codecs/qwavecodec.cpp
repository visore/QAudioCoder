#include <qwavecodec.h>

bool QWaveCodec::initializeDecode()
{
	mError = QAbstractCodec::NoError;
	return true;
}

bool QWaveCodec::finalizeDecode()
{
	return true;
}

void QWaveCodec::decode(const void *input, int size)
{
	qbyte *output = new qbyte[size];
	memcpy(output, input, size);
	QAudioChunk chunk(output, size, size / (mInputFormat.sampleSize() / 8));
	emit decoded(chunk);
}

bool QWaveCodec::initializeEncode()
{
	int inSize = mInputFormat.sampleSize();
	int outSize = mOutputFormat.sampleSize();
	QAudioFormat::SampleType inType = mInputFormat.sampleType();
	QAudioFormat::SampleType outType = mOutputFormat.sampleType();

	if((inSize != 8 || inSize != 16 || inSize != 32) && (outSize != 8 || outSize != 16 || outSize != 32))
	{
		mError = QAbstractCodec::SampleSizeError;
		return false;
	}

	if(inType == QAudioFormat::Unknown || outType == QAudioFormat::Unknown)
	{
		mError = QAbstractCodec::SampleTypeError;
		return false;
	}

	mOuputSizeDifference = outSize / inSize;

	if(inType == QAudioFormat::SignedInt)
	{
		if(outType == QAudioFormat::SignedInt)
		{
			if(inSize == 8)
			{
				if(outSize == 8) convert = &QSampleConverter::convert8sTo8s;
				else if(outSize == 16) convert = &QSampleConverter::convert8sTo16s;
				else if(outSize == 32) convert = &QSampleConverter::convert8sTo32s;
			}
			else if(inSize == 16)
			{
				if(outSize == 8) convert = &QSampleConverter::convert16sTo8s;
				else if(outSize == 16) convert = &QSampleConverter::convert16sTo16s;
				else if(outSize == 32) convert = &QSampleConverter::convert16sTo32s;
			}
			else if(inSize == 32)
			{
				if(outSize == 8) convert = &QSampleConverter::convert32sTo8s;
				else if(outSize == 16) convert = &QSampleConverter::convert32sTo16s;
				else if(outSize == 32) convert = &QSampleConverter::convert32sTo32s;
			}
		}
		else if(outType == QAudioFormat::UnSignedInt)
		{
			if(inSize == 8)
			{
				if(outSize == 8) convert = &QSampleConverter::convert8sTo8u;
				else if(outSize == 16) convert = &QSampleConverter::convert8sTo16u;
				else if(outSize == 32) convert = &QSampleConverter::convert8sTo32u;
			}
			else if(inSize == 16)
			{
				if(outSize == 8) convert = &QSampleConverter::convert16sTo8u;
				else if(outSize == 16) convert = &QSampleConverter::convert16sTo16u;
				else if(outSize == 32) convert = &QSampleConverter::convert16sTo32u;
			}
			else if(inSize == 32)
			{
				if(outSize == 8) convert = &QSampleConverter::convert32sTo8u;
				else if(outSize == 16) convert = &QSampleConverter::convert32sTo16u;
				else if(outSize == 32) convert = &QSampleConverter::convert32sTo32u;
			}
		}
		else if(outType == QAudioFormat::Float)
		{
			if(inSize == 8) convert = &QSampleConverter::convert8sToFloat;
			else if(inSize == 16) convert = &QSampleConverter::convert16sToFloat;
			else if(inSize == 32) convert = &QSampleConverter::convert32sToFloat;
		}
	}
	else if(inType == QAudioFormat::UnSignedInt)
	{
		if(outType == QAudioFormat::SignedInt)
		{
			if(inSize == 8)
			{
				if(outSize == 8) convert = &QSampleConverter::convert8uTo8s;
				else if(outSize == 16) convert = &QSampleConverter::convert8uTo16s;
				else if(outSize == 32) convert = &QSampleConverter::convert8uTo32s;
			}
			else if(inSize == 16)
			{
				if(outSize == 8) convert = &QSampleConverter::convert16uTo8s;
				else if(outSize == 16) convert = &QSampleConverter::convert16uTo16s;
				else if(outSize == 32) convert = &QSampleConverter::convert16uTo32s;
			}
			else if(inSize == 32)
			{
				if(outSize == 8) convert = &QSampleConverter::convert32uTo8s;
				else if(outSize == 16) convert = &QSampleConverter::convert32uTo16s;
				else if(outSize == 32) convert = &QSampleConverter::convert32uTo32s;
			}
		}
		else if(outType == QAudioFormat::UnSignedInt)
		{
			if(inSize == 8)
			{
				if(outSize == 8) convert = &QSampleConverter::convert8uTo8u;
				else if(outSize == 16) convert = &QSampleConverter::convert8uTo16u;
				else if(outSize == 32) convert = &QSampleConverter::convert8uTo32u;
			}
			else if(inSize == 16)
			{
				if(outSize == 8) convert = &QSampleConverter::convert16uTo8u;
				else if(outSize == 16) convert = &QSampleConverter::convert16uTo16u;
				else if(outSize == 32) convert = &QSampleConverter::convert16uTo32u;
			}
			else if(inSize == 32)
			{
				if(outSize == 8) convert = &QSampleConverter::convert32uTo8u;
				else if(outSize == 16) convert = &QSampleConverter::convert32uTo16u;
				else if(outSize == 32) convert = &QSampleConverter::convert32uTo32u;
			}
		}
		else if(outType == QAudioFormat::Float)
		{
			if(inSize == 8) convert = &QSampleConverter::convert8uToFloat;
			else if(inSize == 16) convert = &QSampleConverter::convert16uToFloat;
			else if(inSize == 32) convert = &QSampleConverter::convert32uToFloat;
		}
	}
	else if(inType == QAudioFormat::Float)
	{
		if(outType == QAudioFormat::SignedInt)
		{
			if(outSize == 8) convert = &QSampleConverter::convertFloatTo8s;
			else if(outSize == 16) convert = &QSampleConverter::convertFloatTo16s;
			else if(outSize == 32) convert = &QSampleConverter::convertFloatTo32s;
		}
		else if(outType == QAudioFormat::UnSignedInt)
		{
			if(outSize == 8) convert = &QSampleConverter::convertFloatTo8u;
			else if(outSize == 16) convert = &QSampleConverter::convertFloatTo16u;
			else if(outSize == 32) convert = &QSampleConverter::convertFloatTo32u;
		}
		else if(outType == QAudioFormat::Float)
		{
			convert = &QSampleConverter::convertFloatToFloat;
		}
	}

	mError = QAbstractCodec::NoError;
	return true;
}

bool QWaveCodec::finalizeEncode()
{
	return true;
}

void QWaveCodec::encode(const void *input, int samples)
{
	int outputSize = samples * mOuputSizeDifference;
	qbyte *output = new qbyte[outputSize];
	(*convert)(input, output, samples);
	QAudioChunk chunk(output, samples, outputSize);
	emit encoded(chunk);
}


QAbstractCodec::Error QWaveCodec::initializeLibrary()
{
	return QAbstractCodec::NoError;
}
