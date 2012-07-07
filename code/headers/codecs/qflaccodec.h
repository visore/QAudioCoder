#ifndef QFLACCODEC_H
#define QFLACCODEC_H

#include <qabstractcodec.h>
#include <all.h>

class QFlacCodec;

struct ExtendedFlacStreamEncoder : FLAC__StreamEncoder
{
    QFlacCodec *codec;
};

class QFlacCodec : public QAbstractCodec
{

	public:

		QFlacCodec();
		~QFlacCodec();

		bool initializeEncode();
		bool finalizeEncode();
		void encode(const void *input, int samples);

		bool initializeDecode();
		bool finalizeDecode();
		void decode(const void *input, int size);

	protected:

		ExtendedFlacStreamEncoder* createExtendedEncoder();
		static FLAC__StreamEncoderWriteStatus flacWriteCallback(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData);

		QAbstractCodec::Header inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content);
		void createHeader(QByteArray &header, const QCodecFormat &format, QCodecContent &content);

		QAbstractCodec::Error initializeLibrary();


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

	private:

		ExtendedFlacStreamEncoder *mEncoder;

};

#endif
