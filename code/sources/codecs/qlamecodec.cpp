#include <qlamecodec.h>
#include <qchannelconverter.h>

#define MINIMUM_HEADER_FRAMES 5

QLameCodec::QLameCodec()
	: QAbstractCodec()
{
	mName = "Lame";

	mLameEncoder = NULL;
	mLameDecoder = NULL;
	
	addFileName("mp3lame");
	addFileName("lame");
}

bool QLameCodec::initializeEncode()
{
	mError = QAbstractCodec::NoError;

	mLameEncoder = m_lame_init();

	m_lame_set_in_samplerate(mLameEncoder, mDecoderFormat.sampleRate());
	m_lame_set_num_channels(mLameEncoder, mDecoderFormat.channelCount());

	if(mEncoderFormat.bitrateMode() == QCodecFormat::ConstantBitrate)
	{
		m_lame_set_VBR(mLameEncoder, vbr_off);
	}
	else if(mEncoderFormat.bitrateMode() == QCodecFormat::VariableBitrate)
	{
		m_lame_set_VBR(mLameEncoder, vbr_default);
	}
	else if(mEncoderFormat.bitrateMode() == QCodecFormat::AverageBitrate)
	{
		m_lame_set_VBR(mLameEncoder, vbr_abr);
	}
	else
	{
		m_lame_set_VBR(mLameEncoder, vbr_off);
	}
	m_lame_set_VBR_q(mLameEncoder, mEncoderFormat.quality());
	m_lame_set_VBR_mean_bitrate_kbps(mLameEncoder, mEncoderFormat.bitrate(QCodecFormat::NormalBitrate));
	m_lame_set_VBR_min_bitrate_kbps(mLameEncoder, mEncoderFormat.bitrate(QCodecFormat::MinimumBitrate));
	m_lame_set_VBR_max_bitrate_kbps(mLameEncoder, mEncoderFormat.bitrate(QCodecFormat::MaximumBitrate));

	m_lame_set_quality(mLameEncoder, mEncoderFormat.quality());
	m_lame_set_out_samplerate(mLameEncoder, mEncoderFormat.sampleRate());
	if(mEncoderFormat.channelCount() == 1)
	{
		m_lame_set_mode(mLameEncoder, MONO);
	}
	else
	{
		m_lame_set_mode(mLameEncoder, STEREO);
	}

	m_lame_init_params(mLameEncoder);


	int sampleSize = mDecoderFormat.sampleSize();
	QAudio::SampleType sampleType = QAudio::toAudioSampleType(mDecoderFormat.sampleType());

	if(sampleType == QAudio::Float)
	{
		if(mConverter.initialize(16, QAudio::Float, 16, QAudio::SignedInt))
		{
			encodePointer = &QLameCodec::encode16Convert;
		}
		else
		{
			mError = QAbstractCodec::SampleSizeError;
			return false;
		}
	}
	else if(sampleType == QAudio::Real)
	{
		if(mConverter.initialize(32, QAudio::Real, 32, QAudio::SignedInt))
		{
			encodePointer = &QLameCodec::encode32Convert;
		}
		else
		{
			mError = QAbstractCodec::SampleSizeError;
			return false;
		}
	}
	else if(sampleType == QAudio::SignedInt)
	{
		if(sampleSize == 8)
		{
			if(mConverter.initialize(8, QAudio::SignedInt, 16, QAudio::SignedInt))
			{
				encodePointer = &QLameCodec::encode16Convert;
			}
			else
			{
				mError = QAbstractCodec::SampleSizeError;
				return false;
			}
		}
		else if(sampleSize == 16)
		{
			encodePointer = &QLameCodec::encode16Normal;
		}
		else if(sampleSize == 32)
		{
			encodePointer = &QLameCodec::encode32Normal;
		}
	}
	else if(sampleType == QAudio::UnSignedInt)
	{
		if(sampleSize == 8)
		{
			if(mConverter.initialize(8, QAudio::UnSignedInt, 16, QAudio::SignedInt))
			{
				encodePointer = &QLameCodec::encode16Convert;
			}
			else
			{
				mError = QAbstractCodec::SampleSizeError;
				return false;
			}
		}
		else if(sampleSize == 16)
		{
			if(mConverter.initialize(16, QAudio::UnSignedInt, 16, QAudio::SignedInt))
			{
				encodePointer = &QLameCodec::encode16Convert;
			}
			else
			{
				mError = QAbstractCodec::SampleSizeError;
				return false;
			}
		}
		else if(sampleSize == 32)
		{
			if(mConverter.initialize(32, QAudio::UnSignedInt, 32, QAudio::SignedInt))
			{
				encodePointer = &QLameCodec::encode32Convert;
			}
			else
			{
				mError = QAbstractCodec::SampleSizeError;
				return false;
			}
		}
	}

	return true;
}

bool QLameCodec::finalizeEncode()
{
	m_lame_close(mLameEncoder);
	return true;
}

void QLameCodec::encode(const void *input, int samples)
{
	(this->*encodePointer)(input, samples);
}

void QLameCodec::encode16Convert(const void *input, int samples)
{
	if(samples == 0)
	{
		m_lame_encode_flush(mLameEncoder, (unsigned char*) input, samples);
	}
	else
	{
		short data[samples];
		mConverter.convert(input, data, samples);

		int bytes = samples * 2;
		qbyte *output = new qbyte[bytes];
		bytes = m_lame_encode_buffer_interleaved(mLameEncoder, data, samples / 2, output, bytes);
		emit encoded(new QSampleArray(output, bytes, samples));
	}
}

void QLameCodec::encode32Convert(const void *input, int samples)
{
	if(samples == 0)
	{
		m_lame_encode_flush(mLameEncoder, (unsigned char*) input, samples);
	}
	else
	{
		int data[samples];
		int left[samples / 2];
		int right[samples / 2];
		mConverter.convert(input, data, samples);
		QChannelConverter<int>::splitChannels(data, left, right, samples);

		int bytes = samples * 4;
		qbyte *output = new qbyte[bytes];
		bytes = m_lame_encode_buffer_int(mLameEncoder, left, right, samples / 2, output, bytes);
		emit encoded(new QSampleArray(output, bytes, samples));
	}
}

void QLameCodec::encode16Normal(const void *input, int samples)
{
	if(samples == 0)
	{
		m_lame_encode_flush(mLameEncoder, (unsigned char*) input, samples);
	}
	else
	{
		int bytes = samples * 2;
		qbyte *output = new qbyte[bytes];
		bytes = m_lame_encode_buffer_interleaved(mLameEncoder, (short int*) input, samples / 2, output, bytes);
		emit encoded(new QSampleArray(output, bytes, samples));
	}
}

void QLameCodec::encode32Normal(const void *input, int samples)
{
	if(samples == 0)
	{
		m_lame_encode_flush(mLameEncoder, (unsigned char*) input, samples);
	}
	else
	{
		int left[samples / 2];
		int right[samples / 2];
		QChannelConverter<int>::splitChannels(input, left, right, samples);

		int bytes = samples * 4;
		qbyte *output = new qbyte[bytes];
		bytes = m_lame_encode_buffer_int(mLameEncoder, left, right, samples / 2, output, bytes);
		emit encoded(new QSampleArray(output, bytes, samples));
	}
}

bool QLameCodec::initializeDecode()
{
	mError = QAbstractCodec::NoError;

	mLameDecoder = m_hip_decode_init();

	return true;
}

bool QLameCodec::finalizeDecode()
{
	m_hip_decode_exit(mLameDecoder);
	return true;
}

void QLameCodec::decode(const void *input, int size)
{
/*
int CDECL hip_decode( hip_t           gfp
                    , unsigned char * mp3buf
                    , size_t          len
                    , short           pcm_l[]
                    , short           pcm_r[]
                    );*/




}

QAbstractCodec::Header QLameCodec::inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content)
{
	/*

	Check for MP3 frame header
	The following is in binary:
	
	MP3 sync word: 111111111111
	Version (Mpeg): 1
	Layer (3): 01
	Error protection (yes or no): 0 or 1

	Hence the total:
	Binary: 1111111111111010 or 1111111111111011
	Hex: FFFA or FFFB
	Char: 255_250 or 255_251

	*/

	QList<int> syncPositions;
	char sync1(255);
	char sync2(250);
	char sync3(251);

	int end = header.size() - 1;

	for(int i = 0; i < end; ++i)
	{
		if(header[i] == sync1 && (header[i + 1] == sync2 || header[i + 1] == sync3))
		{
			syncPositions.append(i);

			if(sequentialFrames(syncPositions) >= MINIMUM_HEADER_FRAMES)
			{
				load();
	
				hip_t decoder = m_hip_decode_init();
				mp3data_struct mp3Header;
				short data[header.size() * 10]; //TODO: What (minimum) size should this array be?
				m_hip_decode_headers(decoder, (unsigned char *) header.data(), header.size(), data, data, &mp3Header);
				m_hip_decode_exit(decoder);

				format.setChannels(mp3Header.stereo);
				format.setSampleRate(mp3Header.samplerate);
				format.setBitrate(mp3Header.bitrate);

				content.setSamples(mp3Header.nsamp);
				content.setHeaderSize(0);
				content.setTrailerSize(0);
				content.setDataSize(mp3Header.nsamp * 2); // * 2 because 16bit data

				return QAbstractCodec::ValidHeader;
			}
		}
	}

	return QAbstractCodec::NeedMoreData;
}

void QLameCodec::createHeader(QByteArray &header, const QCodecFormat &format, QCodecContent &content)
{

}

int QLameCodec::sequentialFrames(QList<int> positions)
{
	int end = positions.size() - 1;
	int difference = 0;
	int newDifference = 0;
	int sequential = 0;

	for(int i = 0; i < end; ++i)
	{
		newDifference = positions[i + 1] - positions[i];
		if(newDifference == difference)
		{
			++sequential;
		}
		//If same pattern coincidentally appears in frame, ignore it.
		//Else iff position is greater than previous frame size
		else if(newDifference > difference)
		{
			difference = newDifference;
			sequential = 0;
		}
	}
	return sequential;
}

QAbstractCodec::Error QLameCodec::initializeLibrary()
{
	QList<bool> loaded;
	int success = 0;
	int failure = 0;
	
	bool version = (m_get_lame_short_version = (const char* (*)()) mLibrary.resolve("get_lame_short_version")) != NULL;
	if(version)
	{
		mVersion = QString(m_get_lame_short_version());
	}
	loaded.append(version);

	//Decode

	loaded.append((m_hip_decode_init = (hip_t (*)()) mLibrary.resolve("hip_decode_init")) != NULL);
	loaded.append((m_hip_decode_exit = (int (*)(hip_t)) mLibrary.resolve("hip_decode_exit")) != NULL);

	loaded.append((m_hip_decode = (int (*)(hip_t, unsigned char*, size_t, short[], short[])) mLibrary.resolve("hip_decode")) != NULL);
	loaded.append((m_hip_decode_headers = (int (*)(hip_t, unsigned char*, size_t, short[], short[], mp3data_struct*)) mLibrary.resolve("hip_decode_headers")) != NULL);

	//Encode

	loaded.append((m_lame_init = (lame_t (*)()) mLibrary.resolve("lame_init")) != NULL);
	loaded.append((m_lame_init_params = (int (*)(lame_t)) mLibrary.resolve("lame_init_params")) != NULL);
	loaded.append((m_lame_close = (int (*)(lame_t)) mLibrary.resolve("lame_close")) != NULL);

	loaded.append((m_lame_set_in_samplerate = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_in_samplerate")) != NULL);
	loaded.append((m_lame_set_num_channels = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_num_channels")) != NULL);

	loaded.append((m_lame_set_VBR = (int (*)(lame_t, vbr_mode)) mLibrary.resolve("lame_set_VBR")) != NULL);
	loaded.append((m_lame_set_VBR_q = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_VBR_q")) != NULL);
	loaded.append((m_lame_set_VBR_mean_bitrate_kbps = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_VBR_mean_bitrate_kbps")) != NULL);
	loaded.append((m_lame_set_VBR_min_bitrate_kbps = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_VBR_min_bitrate_kbps")) != NULL);
	loaded.append((m_lame_set_VBR_max_bitrate_kbps = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_VBR_max_bitrate_kbps")) != NULL);

	loaded.append((m_lame_set_quality = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_quality")) != NULL);
	loaded.append((m_lame_set_out_samplerate = (int (*)(lame_t, int)) mLibrary.resolve("lame_set_out_samplerate")) != NULL);
	loaded.append((m_lame_set_mode = (int (*)(lame_t, MPEG_mode)) mLibrary.resolve("lame_set_mode")) != NULL);

	loaded.append((m_lame_encode_flush = (int (*)(lame_t, unsigned char*, int)) mLibrary.resolve("lame_encode_flush")) != NULL);
	loaded.append((m_lame_encode_buffer_interleaved = (int (*)(lame_t, short int[], int, unsigned char*, int)) mLibrary.resolve("lame_encode_buffer_interleaved")) != NULL);
	loaded.append((m_lame_encode_buffer_int = (int (*)(lame_t, const int[], const int[], int, unsigned char*, const int)) mLibrary.resolve("lame_encode_buffer_int")) != NULL);

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
cout<<failure<<endl;
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
