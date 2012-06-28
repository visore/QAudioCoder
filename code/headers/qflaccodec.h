#ifndef QFLACCODEC_H
#define QFLACCODEC_H

#include <qabstractcodec.h>
#include <all.h>

class QFlacCodec : public QAbstractCodec
{

	public:

		static QFlacCodec *callbackObject;
		static FLAC__StreamEncoderWriteStatus flacWriteCallback(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData)
		{
			if(QFlacCodec::callbackObject==NULL)cout<<"pop"<<endl;
		}

		QFlacCodec();
		~QFlacCodec();

		bool initialize();
		bool finalize();

		int encode(const qint8 input[], int inputSize, qint8 output[], int outputSize);
		int encode(const qint16 input[], int inputSize, qint8 output[], int outputSize);
		int encode(const qint32 input[], int inputSize, qint8 output[], int outputSize);

	protected:

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

	private:

		//static FLAC__StreamEncoderWriteStatus flacWriteData(const FLAC__StreamEncoder *encoder, const FLAC__byte buffer[], size_t numberOfBytes, unsigned numberOfSamples, unsigned currentFrame, void *clientData);

	private:

		FLAC__StreamEncoder *mEncoder;
		qint8 *mCurrentBuffer;

};

#endif
