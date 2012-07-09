#ifndef QWAVECODEC_H
#define QWAVECODEC_H

#include <qaudiocodec.h>

class QWaveCodec : public QAudioCodecHolder<QWaveCodec>
{

	protected:

		void initialize();

};

#endif
