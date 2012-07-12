#include <qflaccoder.h>
#include <qflaccodec.h>
#include <qchannelconverter.h>

#include<iostream>
using namespace std;

/*void QFlacCoderThread::setDecoder(FLAC__StreamDecoder *decoder)
{
	mDecoder = decoder;
}

void QFlacCoderThread::addData(void *data, int size)
{
	mMutex.lock();
	mData.append((char*) data, size);
	mMutex.unlock();
	if(!isRunning())
	{
		start();
	}
}

void QFlacCoderThread::run()
{
	m_FLAC__stream_decoder_process_until_end_of_stream(mDecoder);
}*/

QFlacCoder::QFlacCoder()
	: QAbstractCoder(), QThread()
{
	mName = "Flac";
	addFileName("FLAC");
	addFileName("flac");
	addFileName("Flac");
	mSupportedCodecs.append(&QFlacCodec::instance());

	mEncoder = NULL;
	mDecoder = NULL;
}

QFlacCoder::~QFlacCoder()
{
	if(mEncoder != NULL)
	{
		m_FLAC__stream_encoder_delete(mEncoder);
		mEncoder = NULL;
	}
	if(mDecoder != NULL)
	{
		m_FLAC__stream_decoder_delete(mDecoder);
		mDecoder = NULL;
	}
}

QAudioCodec* QFlacCoder::detectCodec(const QByteArray &data)
{
	if(	data.size() >= 4 &&
		(data[0] == 'f' || data[0] == 'F') &&
		(data[1] == 'l' || data[1] == 'L') &&
		(data[2] == 'a' || data[2] == 'A') &&
		(data[3] == 'c' || data[3] == 'C'))
	{
		return &QFlacCodec::instance();
	}
	return NULL;
}

QByteArray& QFlacCoder::header()
{
	return mHeader;
}

int QFlacCoder::headerSize()
{
	return mHeader.size();
}

bool QFlacCoder::initializeEncode()
{
	mError = QAbstractCoder::NoError;

	mHeader.clear();
	mHeaderPosition = 0;

	int inputSampleSize = mInputFormat.sampleSize();
	int outputSampleSize = mOutputFormat.sampleSize();
	QExtendedAudioFormat::SampleType sampleType = mInputFormat.sampleType();

	if(sampleType == QExtendedAudioFormat::SignedInt)
	{
		if(inputSampleSize == outputSampleSize)
		{
			if(inputSampleSize == 8) encodePointer = &QFlacCoder::encode8Normal;
			else if(inputSampleSize == 16) encodePointer = &QFlacCoder::encode16Normal;
			else if(inputSampleSize == 32) encodePointer = &QFlacCoder::encode32Normal;
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
	}
	else
	{
		if(mConverter.initialize(inputSampleSize, sampleType, outputSampleSize, QExtendedAudioFormat::SignedInt))
		{
			if(outputSampleSize == 8) encodePointer = &QFlacCoder::encode8Convert;
			else if(outputSampleSize == 16) encodePointer = &QFlacCoder::encode16Convert;
			else if(outputSampleSize == 32) encodePointer = &QFlacCoder::encode32Convert;
			else
			{
				mError = QAbstractCoder::SampleSizeError;
				return false;
			}
		}
		else
		{
			mError = QAbstractCoder::SampleSizeError;
			return false;
		}
	}

	if(mEncoder != NULL)
	{
		m_FLAC__stream_encoder_delete(mEncoder);
	}
	if((mEncoder = m_FLAC__stream_encoder_new()) == NULL)
	{
		mError = QAbstractCoder::InitializationError;
		return false;
	}

	FLAC__bool ok = true;
	ok &= m_FLAC__stream_encoder_set_verify(mEncoder, true);
	ok &= m_FLAC__stream_encoder_set_compression_level(mEncoder, QExtendedAudioFormat::Minimum - mOutputFormat.quality());
	ok &= m_FLAC__stream_encoder_set_channels(mEncoder, mOutputFormat.channelCount());
	ok &= m_FLAC__stream_encoder_set_bits_per_sample(mEncoder, mOutputFormat.sampleSize());
	ok &= m_FLAC__stream_encoder_set_sample_rate(mEncoder, mOutputFormat.sampleRate());

	if(ok)
	{
		flacWriteEncodePointer = &QFlacCoder::flacWriteEncodeHeader;
		FLAC__StreamEncoderInitStatus initStatus = m_FLAC__stream_encoder_init_stream(mEncoder, flacWriteEncode, flacSeekEncode, flacTellEncode, NULL, this);
		if(initStatus == FLAC__STREAM_ENCODER_INIT_STATUS_INVALID_NUMBER_OF_CHANNELS)
		{
			mError = QAbstractCoder::NumberOfChannelsError;
		}
		else if(initStatus == FLAC__STREAM_ENCODER_INIT_STATUS_INVALID_BITS_PER_SAMPLE)
		{
			mError = QAbstractCoder::SampleSizeError;
		}
		else if(initStatus == FLAC__STREAM_ENCODER_INIT_STATUS_INVALID_SAMPLE_RATE)
		{
			mError = QAbstractCoder::SampleRateError;
		}
		else if(initStatus != FLAC__STREAM_ENCODER_INIT_STATUS_OK)
		{
			ok = false;
		}
		flacWriteEncodePointer = &QFlacCoder::flacWriteEncodeData;
	}
	if(ok)
	{
		return true;
	}
	else if(mError = QAbstractCoder::NoError) //Only if there isn't another error
	{
		mError = QAbstractCoder::InitializationError;
	}
	return false;
}

bool QFlacCoder::finalizeEncode()
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

void QFlacCoder::encode(const void *input, int samples)
{
	(this->*encodePointer)(input, samples);
}

void QFlacCoder::encode8Convert(const void *input, int samples)
{
	qbyte8s data[samples];
	mConverter.convert(input, data, samples);
	FLAC__int32 inputData[samples];
	for(int i = 0; i < samples; ++i)
	{
		inputData[i] = data[i];
	}
	m_FLAC__stream_encoder_process_interleaved(mEncoder, inputData, samples / mInputFormat.channels());
}

void QFlacCoder::encode16Convert(const void *input, int samples)
{
	qbyte16s data[samples];
	mConverter.convert(input, data, samples);
	FLAC__int32 inputData[samples];
	for(int i = 0; i < samples; ++i)
	{
		inputData[i] = data[i];
	}
	m_FLAC__stream_encoder_process_interleaved(mEncoder, inputData, samples / mInputFormat.channels());
}

void QFlacCoder::encode32Convert(const void *input, int samples)
{
	qbyte32s data[samples];
	mConverter.convert(input, data, samples);
	FLAC__int32 inputData[samples];
	for(int i = 0; i < samples; ++i)
	{
		inputData[i] = data[i];
	}
	m_FLAC__stream_encoder_process_interleaved(mEncoder, inputData, samples / mInputFormat.channels());
}

void QFlacCoder::encode8Normal(const void *input, int samples)
{
	qbyte8s *data = (qbyte8s*) input;
	FLAC__int32 inputData[samples];
	for(int i = 0; i < samples; ++i)
	{
		inputData[i] = data[i];
	}
	m_FLAC__stream_encoder_process_interleaved(mEncoder, inputData, samples / mInputFormat.channels());
}

void QFlacCoder::encode16Normal(const void *input, int samples)
{
	qbyte16s *data = (qbyte16s*) input;
	FLAC__int32 inputData[samples];
	for(int i = 0; i < samples; ++i)
	{
		inputData[i] = data[i];
	}
	m_FLAC__stream_encoder_process_interleaved(mEncoder, inputData, samples / mInputFormat.channels());
}

void QFlacCoder::encode32Normal(const void *input, int samples)
{
	qbyte32s *data = (qbyte32s*) input;
	FLAC__int32 inputData[samples];
	for(int i = 0; i < samples; ++i)
	{
		inputData[i] = data[i];
	}
	m_FLAC__stream_encoder_process_interleaved(mEncoder, inputData, samples / mInputFormat.channels());
}

bool QFlacCoder::initializeDecode()
{
	mIsPaused = false;
	mAtEnd = false;

	if(mDecoder != NULL)
	{
		m_FLAC__stream_decoder_delete(mDecoder);
	}
	if((mDecoder = m_FLAC__stream_decoder_new()) == NULL)
	{
		mError = QAbstractCoder::InitializationError;
		return false;
	}

	if(m_FLAC__stream_decoder_init_stream(mDecoder, flacReadDecode, NULL, NULL, NULL, NULL, flacWriteDecode, flacMetadataDecode, flacErrorDecode, this) != FLAC__STREAM_DECODER_INIT_STATUS_OK)
	{
		mError = QAbstractCoder::InitializationError;
		return false;
	}

	return true;
}

bool QFlacCoder::finalizeDecode()
{
	mAtEnd = true;
	if(isPaused())
	{
		resume();
	}
	else if(!isRunning())
	{
		start();
	}
	while(isRunning());

	if(mDecoder != NULL)
	{
		m_FLAC__stream_decoder_finish(mDecoder);
		m_FLAC__stream_decoder_delete(mDecoder);
		mDecoder = NULL;
		return true;
	}
	return false;
}

void QFlacCoder::decode(const void *input, int size)
{
	mMutex.lock();
	mData.append((char*)input, size);
	mMutex.unlock();

	if(isPaused())
	{
		resume();
	}
	else if(!isRunning())
	{
		start();
	}
	if(isRunning())
	{
		mWaiter.lock();
		mWaitCondition.wait(&mWaiter);
		mWaiter.unlock();
	}
}

void QFlacCoder::run()
{
	m_FLAC__stream_decoder_process_until_end_of_stream(mDecoder);
}

void QFlacCoder::pause()
{
	mPauser.lock();
	mIsPaused = true;
	mPauser.unlock();
}

void QFlacCoder::resume()
{
	mPauser.lock();
	mIsPaused = false;
	mPauser.unlock();
	mPauseCondition.wakeAll();
}

void QFlacCoder::wait()
{
	mPauser.lock();
	if(mIsPaused)
	{
		mWaitCondition.wakeAll();
		mPauseCondition.wait(&mPauser);
	}
	mPauser.unlock();
}

int QFlacCoder::dataSize()
{
	mMutex.lock();
	int size = mData.size();
	mMutex.unlock();
	return size;
}

bool QFlacCoder::isPaused()
{
	mMutex.lock();
	bool paused = mIsPaused;
	mMutex.unlock();
	return paused;
}

FLAC__StreamEncoderWriteStatus QFlacCoder::flacWriteEncode(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	coder->flacWriteEncodePointer(encoder, buffer, numberOfBytes, numberOfSamples, currentFrame, client);
}

FLAC__StreamEncoderWriteStatus QFlacCoder::flacWriteEncodeHeader(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	if(coder->mHeaderPosition < coder->mHeader.size())
	{
		coder->mHeader.replace(coder->mHeaderPosition, numberOfBytes, (char*) buffer, numberOfBytes);
	}
	else
	{
		coder->mHeader.append((char*) buffer, numberOfBytes);
		coder->mHeaderPosition += numberOfBytes;
	}
	return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
}

FLAC__StreamEncoderWriteStatus QFlacCoder::flacWriteEncodeData(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	qbyte *data = new qbyte[numberOfBytes];
	memcpy(data, buffer, numberOfBytes);
	emit coder->encoded(new QSampleArray(data, numberOfBytes, numberOfSamples));
	return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
}

FLAC__StreamEncoderSeekStatus QFlacCoder::flacSeekEncode(const FLAC__StreamEncoder *encoder, FLAC__uint64 absolute_byte_offset, void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	coder->mHeaderPosition = absolute_byte_offset + 4; // + 4, because the "fLaC" word at the start is not considered data
	coder->flacWriteEncodePointer = &QFlacCoder::flacWriteEncodeHeader;
	return FLAC__STREAM_ENCODER_SEEK_STATUS_OK;
}

FLAC__StreamEncoderTellStatus QFlacCoder::flacTellEncode(const FLAC__StreamEncoder *encoder, FLAC__uint64 *absolute_byte_offset, void *client)
{
	return FLAC__STREAM_ENCODER_TELL_STATUS_OK;
}

void QFlacCoder::flacErrorDecode(const FLAC__StreamDecoder *decoder, FLAC__StreamDecoderErrorStatus status, void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	coder->mError = QAbstractCoder::DecoderError;
}

void QFlacCoder::flacMetadataDecode(const FLAC__StreamDecoder *decoder, const FLAC__StreamMetadata *metadata, void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;

	coder->mInputFormat.setChannels(metadata->data.stream_info.channels);
	coder->mInputFormat.setSampleSize(metadata->data.stream_info.bits_per_sample);
	coder->mInputFormat.setSampleRate(metadata->data.stream_info.sample_rate);
	coder->mInputFormat.setSampleType(QExtendedAudioFormat::SignedInt);
	coder->mInputFormat.setCodec(&QFlacCodec::instance());

	emit coder->formatChanged(coder->mInputFormat);
}

FLAC__StreamDecoderReadStatus QFlacCoder::flacReadDecode(const FLAC__StreamDecoder *decoder, FLAC__byte buffer[], size_t *bytes, void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	while(!coder->mAtEnd && *bytes > coder->dataSize())
	{
		coder->pause();
		coder->wait();
	}
	if(!coder->mAtEnd && *bytes > coder->dataSize())
	{
		*bytes = coder->dataSize();
	}
	coder->mMutex.lock();
	memcpy(buffer,coder->mData.data(), *bytes);
	coder->mData.remove(0, *bytes);
	coder->mMutex.unlock();
	return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
}

FLAC__StreamDecoderWriteStatus QFlacCoder::flacWriteDecode(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client)
{
	if(frame->header.channels > 2)
	{
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}
	else if(frame->header.bits_per_sample == 8)
	{
		return flacWriteDecode8(decoder, frame, buffer, client);
	}
	else if(frame->header.bits_per_sample == 16)
	{
		return flacWriteDecode16(decoder, frame, buffer, client);
	}
	else if(frame->header.bits_per_sample == 32)
	{
		return flacWriteDecode32(decoder, frame, buffer, client);
	}
	else 
	{
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}
}

FLAC__StreamDecoderWriteStatus QFlacCoder::flacWriteDecode8(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	int samples = frame->header.blocksize;
	int size = frame->header.channels * samples;
	qbyte8s *data = new qbyte8s[size];
	if(frame->header.channels == 1)
	{
		for(int i = 0; i < size; ++i)
		{
			data[i] = buffer[0][i];
		}
	}
	else if(frame->header.channels == 2)
	{
		qbyte8s left[samples];
		qbyte8s right[samples];
		for(int i = 0; i < samples; ++i)
		{
			left[i] = buffer[0][i];
			right[i] = buffer[1][i];
		}
		samples = QChannelConverter<qbyte8s>::combineChannels(left, right, data, samples);
	}
	else
	{
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}

	emit coder->decoded(new QSampleArray(data, size, samples));
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

FLAC__StreamDecoderWriteStatus QFlacCoder::flacWriteDecode16(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	int samples = frame->header.blocksize;
	int size = frame->header.channels * samples;
	qbyte16s *data = new qbyte16s[size];
	if(frame->header.channels == 1)
	{
		for(int i = 0; i < size; ++i)
		{
			data[i] = buffer[0][i];
		}
	}
	else if(frame->header.channels == 2)
	{
		qbyte16s left[samples];
		qbyte16s right[samples];
		for(int i = 0; i < samples; ++i)
		{
			left[i] = buffer[0][i];
			right[i] = buffer[1][i];
		}
		samples = QChannelConverter<qbyte16s>::combineChannels(left, right, data, samples);
	}
	else
	{
		return FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
	}

	emit coder->decoded(new QSampleArray(data, size, samples));
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

FLAC__StreamDecoderWriteStatus QFlacCoder::flacWriteDecode32(const FLAC__StreamDecoder *decoder, const FLAC__Frame *frame, const FLAC__int32 * const buffer[], void *client)
{
	QFlacCoder *coder = (QFlacCoder*) client;
	int samples = frame->header.blocksize;
	int size = frame->header.channels * samples;
	qbyte32s *data = new qbyte32s[size];
	if(frame->header.channels == 1)
	{
		for(int i = 0; i < size; ++i)
		{
			data[i] = buffer[0][i];
		}
	}
	else if(frame->header.channels == 2)
	{
		qbyte32s left[samples];
		qbyte32s right[samples];
		for(int i = 0; i < samples; ++i)
		{
			left[i] = buffer[0][i];
			right[i] = buffer[1][i];
		}
		samples = QChannelConverter<qbyte32s>::combineChannels(left, right, data, samples);
	}
	emit coder->decoded(new QSampleArray(data, size, samples));
	return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

QAbstractCoder::Error QFlacCoder::initializeLibrary()
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

	loaded.append((m_FLAC__stream_decoder_new = (FLAC__StreamDecoder* (*)()) mLibrary.resolve("FLAC__stream_decoder_new")) != NULL);
	loaded.append((m_FLAC__stream_decoder_delete = (void (*)(FLAC__StreamDecoder*)) mLibrary.resolve("FLAC__stream_decoder_delete")) != NULL);
	loaded.append((m_FLAC__stream_decoder_finish = (FLAC__bool (*)(FLAC__StreamDecoder*)) mLibrary.resolve("FLAC__stream_decoder_finish")) != NULL);
	loaded.append((m_FLAC__stream_decoder_init_stream = (FLAC__StreamDecoderInitStatus (*)(FLAC__StreamDecoder*, FLAC__StreamDecoderReadCallback, FLAC__StreamDecoderSeekCallback, FLAC__StreamDecoderTellCallback, FLAC__StreamDecoderLengthCallback, FLAC__StreamDecoderEofCallback, FLAC__StreamDecoderWriteCallback, FLAC__StreamDecoderMetadataCallback, FLAC__StreamDecoderErrorCallback, void*)) mLibrary.resolve("FLAC__stream_decoder_init_stream")) != NULL);

	loaded.append((m_FLAC__stream_decoder_process_until_end_of_stream = (FLAC__bool (*)(FLAC__StreamDecoder*)) mLibrary.resolve("FLAC__stream_decoder_process_until_end_of_stream")) != NULL);

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
		return QAbstractCoder::NoError;
	}
	else if(failure == loaded.size())
	{
		return QAbstractCoder::LibraryError;
	}
	return QAbstractCoder::VersionError;
}

/*
FLAC__StreamEncoderWriteStatus QFlacCoder::flacWriteData(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData)
{
	if(mCurrentBuffer == NULL)
	{
		mError = QAbstractCoder::BufferError;
		return FLAC__STREAM_ENCODER_WRITE_STATUS_FATAL_ERROR;
	}
	memcpy(mCurrentBuffer, buffer, numberOfBytes);
	return FLAC__STREAM_ENCODER_WRITE_STATUS_OK;
}*/
