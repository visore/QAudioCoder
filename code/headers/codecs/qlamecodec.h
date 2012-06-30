#ifndef QLAMECODEC_H
#define QLAMECODEC_H

#include <qabstractcodec.h>
#include <lame.h>

class QLameCodec : public QAbstractCodec
{

	public:

		QLameCodec();

		bool initialize();
		bool finalize();

		int encode(const qint8 input[], int inputSize);
		int encode(const qint16 input[], int inputSize);
		int encode(const qint32 input[], int inputSize);

	protected:

		QAbstractCodec::Error initializeLibrary();

	private:

		const char* (*m_get_lame_short_version)();
		lame_t (*m_lame_init)();
		int (*m_lame_init_params)(lame_t);
		int (*m_lame_close)(lame_t);

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

	private:

		lame_t mLame;

};

#endif
