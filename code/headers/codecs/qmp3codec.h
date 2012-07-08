#ifndef QMP3CODEC_H
#define QMP3CODEC_H

#include <qaudiocodec.cpp>

class QMp3Codec : public QAudioCodec<QMp3Codec>
{

	protected:

		void initialize();

};

#endif
