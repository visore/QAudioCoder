#ifndef QWAVECODEC_H
#define QWAVECODEC_H

#include <qaudiocodec.cpp>

class QWaveCodec : public QAudioCodec<QWaveCodec>
{

	protected:

		void initialize();

};

#endif
