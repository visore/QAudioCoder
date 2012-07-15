#ifndef QLAMECODER_H
#define QLAMECODER_H

#include <qabstractcoder.h>
#include <qsamplesizeconverter.h>
#include <lame.h>

class QLameCoder : public QAbstractCoder
{

	public:

		QLameCoder();

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

		void encodeConvert(const void *input, int samples);
		void encode16Convert(const void *input, int samples);
		void encode32Convert(const void *input, int samples);
		void encode16Normal(const void *input, int samples);
		void encode32Normal(const void *input, int samples);

		int sequentialFrames(QList<int> positions);

		QCoder::Error initializeLibrary();

	private:

		const char* (*m_get_lame_short_version)();
		int (*m_lame_get_version)(lame_t);

		int (*m_InitVbrTag)(lame_global_flags*);

		//Decode

		hip_t (*m_hip_decode_init)(void);
		int (*m_hip_decode_exit)(hip_t);

		int (*m_hip_decode)(hip_t, unsigned char*, int, short[], short[]);
		int (*m_hip_decode_headers)(hip_t, unsigned char*, int, short[], short[], mp3data_struct*);

		//Encode

		lame_t (*m_lame_init)();
		int (*m_lame_init_params)(lame_t);
		int (*m_lame_close)(lame_t);
		int (*m_lame_get_lametag_frame)(lame_t, unsigned char*, int);

		int (*m_lame_set_in_samplerate)(lame_t, int);
		int (*m_lame_set_num_channels)(lame_t, int);

		int (*m_lame_set_VBR)(lame_t, vbr_mode);
		int (*m_lame_set_VBR_q)(lame_t, int);
		int (*m_lame_set_VBR_mean_bitrate_kbps)(lame_t, int);
		int (*m_lame_set_VBR_min_bitrate_kbps)(lame_t, int);
		int (*m_lame_set_VBR_max_bitrate_kbps)(lame_t, int);

		int (*m_lame_set_quality)(lame_t, int);
		int (*m_lame_set_out_samplerate)(lame_t, int);
		int (*m_lame_set_mode)(lame_t, MPEG_mode);

		int (*m_lame_encode_flush)(lame_t, unsigned char*, int);
		int (*m_lame_encode_buffer_interleaved)(lame_t, short int[], int, unsigned char*, int);
		int (*m_lame_encode_buffer_int)(lame_t, int[], int[], int, unsigned char*, int);

	private:

		QSampleSizeConverter mConverter;
		void (QLameCoder::*encodePointer)(const void *input, int samples);

		lame_t mLameEncoder;
		hip_t mLameDecoder;

		qreal mTotalBitrate;
		qint32 mMinimumBitrate;
		qint32 mMaximumBitrate;
		qint32 mBitrateCounter;

		bool mFormatWasDetected;

};

#endif
