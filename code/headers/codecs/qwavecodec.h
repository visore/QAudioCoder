#ifndef QWAVECODEC_H
#define QWAVECODEC_H

#include <qabstractcodec.h>

class QWaveCodec : public QAbstractCodec
{

	public:

		bool initialize();
		bool finalize();

		void encode8(const qbyte input[], int samples);
		void encode16(const qbyte input[], int samples);
		void encode32(const qbyte input[], int samples);

		void decode8(const qbyte input[], int size);
		void decode16(const qbyte input[], int size);
		void decode32(const qbyte input[], int size);

	protected:

		QAbstractCodec::Error initializeLibrary();

};

#endif
