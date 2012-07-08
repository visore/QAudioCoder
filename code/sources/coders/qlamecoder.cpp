#include <qlamecoder.h>
#include <qchannelconverter.h>
#include <qmp3codec.h>

#define MINIMUM_HEADER_FRAMES 5

QLameCoder::QLameCoder()
	: QAbstractCoder()
{
	mName = "Lame";
	addFileName("mp3lame");
	addFileName("lame");
	mSupportedCodecs.append(QMp3Codec::instance());

	mLameEncoder = NULL;
	mLameDecoder = NULL;
}

bool QLameCoder::initializeEncode()
{
	mError = QAbstractCoder::NoError;

	mLameEncoder = m_lame_init();

	m_lame_set_in_samplerate(mLameEncoder, mInputFormat.sampleRate());
	m_lame_set_num_channels(mLameEncoder, mInputFormat.channelCount());

	if(mOutputFormat.bitrateMode() == QExtendedAudioFormat::ConstantBitrate)
	{
		m_lame_set_VBR(mLameEncoder, vbr_off);
	}
	else if(mOutputFormat.bitrateMode() == QExtendedAudioFormat::VariableBitrate)
	{
		m_lame_set_VBR(mLameEncoder, vbr_default);
	}
	else if(mOutputFormat.bitrateMode() == QExtendedAudioFormat::AverageBitrate)
	{
		m_lame_set_VBR(mLameEncoder, vbr_abr);
	}
	else
	{
		m_lame_set_VBR(mLameEncoder, vbr_off);
	}
	m_lame_set_VBR_q(mLameEncoder, mOutputFormat.quality());
	m_lame_set_VBR_mean_bitrate_kbps(mLameEncoder, mOutputFormat.bitrate(QExtendedAudioFormat::NormalBitrate));
	m_lame_set_VBR_min_bitrate_kbps(mLameEncoder, mOutputFormat.bitrate(QExtendedAudioFormat::MinimumBitrate));
	m_lame_set_VBR_max_bitrate_kbps(mLameEncoder, mOutputFormat.bitrate(QExtendedAudioFormat::MaximumBitrate));

	m_lame_set_quality(mLameEncoder, mOutputFormat.quality());
	m_lame_set_out_samplerate(mLameEncoder, mOutputFormat.sampleRate());
	if(mOutputFormat.channelCount() == 1)
	{
		m_lame_set_mode(mLameEncoder, MONO);
	}
	else
	{
		m_lame_set_mode(mLameEncoder, STEREO);
	}

	m_lame_init_params(mLameEncoder);


	int inputSampleSize = mInputFormat.sampleSize();
	int outputSampleSize = mOutputFormat.sampleSize();
	QExtendedAudioFormat::SampleType sampleType = mInputFormat.sampleType();

	if(outputSampleSize != 16 && outputSampleSize != 32)
	{
		if(outputSampleSize < 16) outputSampleSize = 16;
		else outputSampleSize = 32;
	}

	if(sampleType == QExtendedAudioFormat::Float)
	{
		if(mConverter.initialize(16, QExtendedAudioFormat::Float, outputSampleSize, QExtendedAudioFormat::SignedInt))
		{
			if(outputSampleSize == 16) encodePointer = &QLameCoder::encode16Convert;
			else encodePointer = &QLameCoder::encode32Convert;
		}
		else
		{
			mError = QAbstractCoder::SampleSizeError;
			return false;
		}
	}
	else if(sampleType == QExtendedAudioFormat::Real)
	{
		if(mConverter.initialize(32, QExtendedAudioFormat::Real, outputSampleSize, QExtendedAudioFormat::SignedInt))
		{
			if(outputSampleSize == 16) encodePointer = &QLameCoder::encode16Convert;
			else encodePointer = &QLameCoder::encode32Convert;
		}
		else
		{
			mError = QAbstractCoder::SampleSizeError;
			return false;
		}
	}
	else if(sampleType == QExtendedAudioFormat::SignedInt)
	{
		if(inputSampleSize == 8)
		{
			if(mConverter.initialize(8, QExtendedAudioFormat::SignedInt, outputSampleSize, QExtendedAudioFormat::SignedInt))
			{
				if(outputSampleSize == 16) encodePointer = &QLameCoder::encode16Convert;
				else encodePointer = &QLameCoder::encode32Convert;
			}
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
		else if(inputSampleSize == 16)
		{
			if(outputSampleSize == 16)
			{
				encodePointer = &QLameCoder::encode16Normal;
			}
			else if(mConverter.initialize(16, QExtendedAudioFormat::SignedInt, outputSampleSize, QExtendedAudioFormat::SignedInt))
			{
				encodePointer = &QLameCoder::encode32Convert;
			}
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
		else if(inputSampleSize == 32)
		{
			if(outputSampleSize == 32)
			{
				encodePointer = &QLameCoder::encode32Normal;
			}
			else if(mConverter.initialize(32, QExtendedAudioFormat::SignedInt, outputSampleSize, QExtendedAudioFormat::SignedInt))
			{
				encodePointer = &QLameCoder::encode16Convert;
			}
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
	}
	else if(sampleType == QExtendedAudioFormat::UnSignedInt)
	{
		if(inputSampleSize == 8)
		{
			if(mConverter.initialize(8, QExtendedAudioFormat::UnSignedInt, outputSampleSize, QExtendedAudioFormat::SignedInt))
			{
				if(outputSampleSize == 16) encodePointer = &QLameCoder::encode16Convert;
				else encodePointer = &QLameCoder::encode32Convert;
			}
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
		else if(inputSampleSize == 16)
		{
			if(mConverter.initialize(16, QExtendedAudioFormat::UnSignedInt, outputSampleSize, QExtendedAudioFormat::SignedInt))
			{
				if(outputSampleSize == 16) encodePointer = &QLameCoder::encode16Convert;
				else encodePointer = &QLameCoder::encode32Convert;
			}
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
		else if(inputSampleSize == 32)
		{
			if(mConverter.initialize(32, QExtendedAudioFormat::UnSignedInt, outputSampleSize, QExtendedAudioFormat::SignedInt))
			{
				if(outputSampleSize == 16) encodePointer = &QLameCoder::encode16Convert;
				else encodePointer = &QLameCoder::encode32Convert;
			}
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
	}

	return true;
}

bool QLameCoder::finalizeEncode()
{
	m_lame_close(mLameEncoder);
	return true;
}

void QLameCoder::encode(const void *input, int samples)
{
	(this->*encodePointer)(input, samples);
}

void QLameCoder::encode16Convert(const void *input, int samples)
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

void QLameCoder::encode32Convert(const void *input, int samples)
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

void QLameCoder::encode16Normal(const void *input, int samples)
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

void QLameCoder::encode32Normal(const void *input, int samples)
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

bool QLameCoder::initializeDecode()
{
	mError = QAbstractCoder::NoError;

	mLameDecoder = m_hip_decode_init();

	return true;
}

bool QLameCoder::finalizeDecode()
{
	m_hip_decode_exit(mLameDecoder);
	return true;
}

void QLameCoder::decode(const void *input, int size)
{
/*
int CDECL hip_decode( hip_t           gfp
                    , unsigned char * mp3buf
                    , size_t          len
                    , short           pcm_l[]
                    , short           pcm_r[]
                    );*/




}

QAbstractCoder::Header QLameCoder::inspectHeader(const QByteArray &header, QExtendedAudioFormat &format, QAudioInfo &content)
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

				return QAbstractCoder::ValidHeader;
			}
		}
	}

	return QAbstractCoder::NeedMoreData;
}

void QLameCoder::createHeader(QByteArray &header, const QExtendedAudioFormat &format, QAudioInfo &content)
{

}

int QLameCoder::sequentialFrames(QList<int> positions)
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

QAbstractCoder::Error QLameCoder::initializeLibrary()
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
		return QAbstractCoder::NoError;
	}
	else if(failure == loaded.size())
	{
		return QAbstractCoder::LibraryError;
	}
	return QAbstractCoder::VersionError;
}
