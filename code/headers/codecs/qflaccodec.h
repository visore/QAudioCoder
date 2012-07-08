#ifndef QFLACCODEC_H
#define QFLACCODEC_H

#include <qaudiocodec.h>

class QFlacCodec : public QAudioCodecHolder<QFlacCodec>
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
