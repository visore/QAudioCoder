#ifndef QMP3CODEC_H
#define QMP3CODEC_H

#include <qaudiocodec.h>

class QMp3Codec : public QAudioCodecHolder<QMp3Codec>
{

	protected:

		void initialize();

};

#endif
