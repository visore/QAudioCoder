#include <qlamecodec.h>

QLameCodec::QLameCodec()
	: QAbstractCodec()
{
	mName = "Lame";
	
	addFileName("mp3lame");
	addFileName("lame");
}

bool QLameCodec::initialize()
{
	mError = QAbstractCodec::NoError;

	mLame = m_lame_init();

	m_lame_set_in_samplerate(mLame, mInputFormat.sampleRate());
	m_lame_set_num_channels(mLame, mInputFormat.channelCount());

	if(mOutputFormat.bitrateMode() == QCodecFormat::ConstantBitrate)
	{
		m_lame_set_VBR(mLame, vbr_off);
	}
	else if(mOutputFormat.bitrateMode() == QCodecFormat::VariableBitrate)
	{
		m_lame_set_VBR(mLame, vbr_default);
	}
	else if(mOutputFormat.bitrateMode() == QCodecFormat::AverageBitrate)
	{
		m_lame_set_VBR(mLame, vbr_abr);
	}
	else
	{
		m_lame_set_VBR(mLame, vbr_off);
	}
	m_lame_set_VBR_q(mLame, mOutputFormat.quality());
	m_lame_set_VBR_mean_bitrate_kbps(mLame, mOutputFormat.bitrate(QCodecFormat::NormalBitrate));
	m_lame_set_VBR_min_bitrate_kbps(mLame, mOutputFormat.bitrate(QCodecFormat::MinimumBitrate));
	m_lame_set_VBR_max_bitrate_kbps(mLame, mOutputFormat.bitrate(QCodecFormat::MaximumBitrate));

	m_lame_set_quality(mLame, mOutputFormat.quality());
	m_lame_set_out_samplerate(mLame, mOutputFormat.sampleRate());
	if(mOutputFormat.channelCount() == 1)
	{
		m_lame_set_mode(mLame, MONO);
	}
	else
	{
		m_lame_set_mode(mLame, STEREO);
	}

	m_lame_init_params(mLame);

	return true;
}

bool QLameCodec::finalize()
{
	m_lame_close(mLame);

	return true;
}

int QLameCodec::encode(const qint8 input[], int inputSize, qint8 output[], int outputSize)
{
	/*if(inputSize == 0)
	{
		return m_lame_encode_flush(mLame, (unsigned char*) output, outputSize);
	}
	else
	{
		//Input size is devided by 2, size Lame wants the samples per channel, not the samples in the array
		return m_lame_encode_buffer_interleaved(mLame, (short int*) input, inputSize / 2, (unsigned char*) output, outputSize);
	}*/
}

int QLameCodec::encode(const qint16 input[], int inputSize, qint8 output[], int outputSize)
{
	if(inputSize == 0)
	{
		return m_lame_encode_flush(mLame, (unsigned char*) output, outputSize);
	}
	else
	{
		//Input size is devided by 2, size Lame wants the samples per channel, not the samples in the array
		return m_lame_encode_buffer_interleaved(mLame, (short int*) input, inputSize / 2, (unsigned char*) output, outputSize);
	}
}

int QLameCodec::encode(const qint32 input[], int inputSize, qint8 output[], int outputSize)
{
	/*if(inputSize == 0)
	{
		return m_lame_encode_flush(mLame, (unsigned char*) output, outputSize);
	}
	else
	{
		//Input size is devided by 2, size Lame wants the samples per channel, not the samples in the array
		return m_lame_encode_buffer_interleaved(mLame, (short int*) input, inputSize / 2, (unsigned char*) output, outputSize);
	}*/
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
