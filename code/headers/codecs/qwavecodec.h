#ifndef QWAVECODEC_H
#define QWAVECODEC_H

#include <qabstractcodec.h>

class QWaveCodec : public QAbstractCodec
{

	public:

		bool initializeEncode();
		bool finalizeEncode();
		void encode(const void *input, int samples);

		bool initializeDecode();
		bool finalizeDecode();
		void decode(const void *input, int size);

	protected:

		QAbstractCodec::Error initializeLibrary();

	private:

		void (*convert)(const void*, void*, int);

		int mOuputSizeDifference;

};

#endif
