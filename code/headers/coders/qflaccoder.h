#ifndef QFLACCODER_H
#define QFLACCODER_H

#include <qabstractcoder.h>
#include <qsamplesizeconverter.h>
#include <all.h>

class QFlacCoder;

struct ExtendedFlacStreamEncoder : FLAC__StreamEncoder
{
    QFlacCoder *coder;
};

class QFlacCoder : public QAbstractCoder
{

	public:

		QFlacCoder();
		~QFlacCoder();

		QAudioCodec* detectCodec(const QByteArray &data);
		QByteArray& header();
		int headerSize();

		bool initializeEncode();
		bool finalizeEncode();
		void encode(const void *input, int samples);

		bool initializeDecode();
		bool finalizeDecode();
		void decode(const void *input, int size);

	protected:

		void encode8Convert(const void *input, int samples);
		void encode16Convert(const void *input, int samples);
		void encode32Convert(const void *input, int samples);
		void encode8Normal(const void *input, int samples);
		void encode16Normal(const void *input, int samples);
		void encode32Normal(const void *input, int samples);

		ExtendedFlacStreamEncoder* createExtendedEncoder();

		FLAC__StreamEncoderWriteStatus (*flacWriteCallback)(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData);
		static FLAC__StreamEncoderWriteStatus flacWriteCallbackHeader(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData);
		static FLAC__StreamEncoderWriteStatus flacWriteCallbackData(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData);

		QAbstractCoder::Error initializeLibrary();

	private:

		FLAC__StreamEncoder* (*m_FLAC__stream_encoder_new)();
		void (*m_FLAC__stream_encoder_delete)(FLAC__StreamEncoder*);
		FLAC__StreamEncoderInitStatus (*m_FLAC__stream_encoder_init_stream)(FLAC__StreamEncoder*, FLAC__StreamEncoderWriteCallback, FLAC__StreamEncoderSeekCallback, FLAC__StreamEncoderTellCallback, FLAC__StreamEncoderMetadataCallback, void*);
		FLAC__bool (*m_FLAC__stream_encoder_finish)(FLAC__StreamEncoder*);

		FLAC__bool (*m_FLAC__stream_encoder_set_verify)(FLAC__StreamEncoder*, FLAC__bool);
		FLAC__bool (*m_FLAC__stream_encoder_set_compression_level)(FLAC__StreamEncoder*, unsigned);
		FLAC__bool (*m_FLAC__stream_encoder_set_channels)(FLAC__StreamEncoder*, unsigned);
		FLAC__bool (*m_FLAC__stream_encoder_set_bits_per_sample)(FLAC__StreamEncoder*, unsigned);
		FLAC__bool (*m_FLAC__stream_encoder_set_sample_rate)(FLAC__StreamEncoder*, unsigned);

		FLAC__bool (*m_FLAC__stream_encoder_process_interleaved)(FLAC__StreamEncoder*, const FLAC__int32[], unsigned);



FLAC__StreamEncoderState (*m_FLAC__stream_encoder_get_state)(const FLAC__StreamEncoder*);

	private:

		void (QFlacCoder::*encodePointer)(const void *input, int samples);

		QSampleSizeConverter mConverter;
		ExtendedFlacStreamEncoder *mEncoder;

};

#endif
