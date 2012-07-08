#ifndef QMP3CODEC_H
#define QMP3CODEC_H

#include <qaudiocodec.h>

class QMp3Codec : public QAudioCodecHolder<QMp3Codec>
{

	public:

		QByteArray createHeader(const QExtendedAudioFormat &format, const QAudioInfo &info);
		QByteArray createTrailer(const QExtendedAudioFormat &format, const QAudioInfo &info);
		Qt::Validity interpretHeader(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info);
		Qt::Validity interpretTrailer(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info);

	protected:

		void initialize();

};

#endif
