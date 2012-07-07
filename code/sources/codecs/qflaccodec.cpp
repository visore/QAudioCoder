#include <qflaccodec.h>

QFlacCodec::QFlacCodec()
	: QAbstractCodec()
{
	mName = "Flac";
	
	addFileName("FLAC");
	addFileName("flac");
	addFileName("Flac");

	mEncoder = NULL;
}

QFlacCodec::~QFlacCodec()
{
	if(mEncoder != NULL)
	{
		m_FLAC__stream_encoder_delete(mEncoder);
		mEncoder = NULL;
	}
}

bool QFlacCodec::initializeEncode()
{
mError = QAbstractCodec::NoError;

	if(mEncoder != NULL)
	{
		m_FLAC__stream_encoder_delete(mEncoder);
	}
	if((mEncoder = createExtendedEncoder()) == NULL)
	{
		return false;
	}



	FLAC__bool ok = true;
	ok &= m_FLAC__stream_encoder_set_verify(mEncoder, true);
	//ok &= m_FLAC__stream_encoder_set_compression_level(mEncoder, mEncoderFormat.quality());
	ok &= m_FLAC__stream_encoder_set_compression_level(mEncoder, 5);
	ok &= m_FLAC__stream_encoder_set_channels(mEncoder, mEncoderFormat.channelCount());
	ok &= m_FLAC__stream_encoder_set_bits_per_sample(mEncoder, mEncoderFormat.sampleSize());
	ok &= m_FLAC__stream_encoder_set_sample_rate(mEncoder, mEncoderFormat.sampleRate());
	//ok &= FLAC__stream_encoder_set_total_samples_estimate(encoder, total_samples);

	if(ok)
	{
		FLAC__StreamEncoderInitStatus initStatus = m_FLAC__stream_encoder_init_stream(mEncoder, flacWriteCallback, NULL, NULL, NULL, NULL);
		if(initStatus == FLAC__STREAM_ENCODER_INIT_STATUS_INVALID_NUMBER_OF_CHANNELS)
		{
			mError = QAbstractCodec::NumberOfChannelsError;
		}
		else if(initStatus == FLAC__STREAM_ENCODER_INIT_STATUS_INVALID_BITS_PER_SAMPLE)
		{
			mError = QAbstractCodec::SampleSizeError;
		}
		else if(initStatus == FLAC__STREAM_ENCODER_INIT_STATUS_INVALID_SAMPLE_RATE)
		{
			mError = QAbstractCodec::SampleRateError;
		}
		else if(initStatus != FLAC__STREAM_ENCODER_INIT_STATUS_OK)
		{
			ok = false;
		}
	}
	if(ok)
	{
		return true;
	}
	else if(mError = QAbstractCodec::NoError) //Only if there isn't another error
	{
		mError = QAbstractCodec::InitializationError;
	}
	return false;
}

bool QFlacCodec::finalizeEncode()
{
	if(mEncoder != NULL)
	{
		m_FLAC__stream_encoder_finish(mEncoder);
		m_FLAC__stream_encoder_delete(mEncoder);
		mEncoder = NULL;
		return true;
	}
	return false;
}

void QFlacCodec::encode(const void *input, int samples)
{
	if(!m_FLAC__stream_encoder_process_interleaved(mEncoder, (FLAC__int32*) input, samples/2)) ////////////////// Change conversion
	{
		cout<<"fail"<<endl;
	}
}

bool QFlacCodec::initializeDecode()
{

}

bool QFlacCodec::finalizeDecode()
{

}

void QFlacCodec::decode(const void *input, int size)
{

}

ExtendedFlacStreamEncoder* QFlacCodec::createExtendedEncoder()
{
	FLAC__StreamEncoder *encoder = m_FLAC__stream_encoder_new();
	ExtendedFlacStreamEncoder *extended = new ExtendedFlacStreamEncoder;
	extended->protected_ = encoder->protected_;
	extended->private_ = encoder->private_;
	extended->codec = this;
	delete encoder;
	return extended;
}

FLAC__StreamEncoderWriteStatus QFlacCodec::flacWriteCallback(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData)
{
	ExtendedFlacStreamEncoder *extended = (ExtendedFlacStreamEncoder*) encoder;
	emit extended->codec->encoded(new QSampleArray((qbyte*) buffer, numberOfBytes, numberOfSamples));
}

QAbstractCodec::Header QFlacCodec::inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content)
{

}

void QFlacCodec::createHeader(QByteArray &header, const QCodecFormat &format, QCodecContent &content)
{

}

QAbstractCodec::Error QFlacCodec::initializeLibrary()
{
	QList<bool> loaded;
	int success = 0;
	int failure = 0;
	
	char *versionString;
	bool version = (versionString = (char*) mLibrary.resolve("FLAC__VERSION_STRING")) != NULL;
	if(version)
	{
		mVersion = QString(versionString);
	}
	loaded.append(version);
//cout<<"version: *"<<(const char*) mLibrary.resolve("FLAC__VENDOR_STRING")<<"*"<<endl;

	loaded.append((m_FLAC__stream_encoder_new = (FLAC__StreamEncoder* (*)()) mLibrary.resolve("FLAC__stream_encoder_new")) != NULL);
	loaded.append((m_FLAC__stream_encoder_delete = (void (*)(FLAC__StreamEncoder*)) mLibrary.resolve("FLAC__stream_encoder_delete")) != NULL);
	loaded.append((m_FLAC__stream_encoder_init_stream = (FLAC__StreamEncoderInitStatus (*)(FLAC__StreamEncoder*, FLAC__StreamEncoderWriteCallback, FLAC__StreamEncoderSeekCallback, FLAC__StreamEncoderTellCallback, FLAC__StreamEncoderMetadataCallback, void*)) mLibrary.resolve("FLAC__stream_encoder_init_stream")) != NULL);
	loaded.append((m_FLAC__stream_encoder_finish = (FLAC__bool (*)(FLAC__StreamEncoder*)) mLibrary.resolve("FLAC__stream_encoder_finish")) != NULL);

	loaded.append((m_FLAC__stream_encoder_set_verify = (FLAC__bool (*)(FLAC__StreamEncoder*, FLAC__bool)) mLibrary.resolve("FLAC__stream_encoder_set_verify")) != NULL);
	loaded.append((m_FLAC__stream_encoder_set_compression_level = (FLAC__bool (*)(FLAC__StreamEncoder*, unsigned)) mLibrary.resolve("FLAC__stream_encoder_set_compression_level")) != NULL);
	loaded.append((m_FLAC__stream_encoder_set_channels = (FLAC__bool (*)(FLAC__StreamEncoder*, unsigned)) mLibrary.resolve("FLAC__stream_encoder_set_channels")) != NULL);
	loaded.append((m_FLAC__stream_encoder_set_bits_per_sample = (FLAC__bool (*)(FLAC__StreamEncoder*, unsigned)) mLibrary.resolve("FLAC__stream_encoder_set_bits_per_sample")) != NULL);
	loaded.append((m_FLAC__stream_encoder_set_sample_rate = (FLAC__bool (*)(FLAC__StreamEncoder*, unsigned)) mLibrary.resolve("FLAC__stream_encoder_set_sample_rate")) != NULL);

	loaded.append((m_FLAC__stream_encoder_process_interleaved = (FLAC__bool (*)(FLAC__StreamEncoder*, const FLAC__int32[], unsigned)) mLibrary.resolve("FLAC__stream_encoder_process_interleaved")) != NULL);

	for(int i = 0; i < loaded.size(); ++i)
	{
		if(loaded[i])
		{
			++success;
		}
		else
		{
			++failure;
		}
	}

	if(success == loaded.size())
	{
		return QAbstractCodec::NoError;
	}
	else if(failure == loaded.size())
	{
		return QAbstractCodec::LibraryError;
	}
	return QAbstractCodec::VersionError;
}

/*
FLAC__StreamEncoderWriteStatus QFlacCodec::flacWriteData(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData)
{
	if(mCurrentBuffer == NULL)
	{
		mError = QAbstractCodec::BufferError;
		return FLAC__STREAM_ENCODER_WRITE_STATUS_FATAL_ERROR;
	}
	memcpy(mCurrentBuffer, buffer, numberOfBytes);
	return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
}*/
