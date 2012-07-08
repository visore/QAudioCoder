#ifndef QFLACCODEC_H
#define QFLACCODEC_H

#include <qaudiocodec.cpp>

class QFlacCodec : public QAudioCodec<QFlacCodec>
{

	protected:

		void initialize();

};

#endif
