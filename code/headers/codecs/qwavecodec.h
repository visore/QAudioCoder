#ifndef QWAVECODEC_H
#define QWAVECODEC_H

#include <qabstractcodec.h>

class QWaveCodec : public QAbstractCodec
{

	public:

		bool initialize();
		bool finalize();

		int encode(const qint8 input[], int inputSize);
		int encode(const qint16 input[], int inputSize);
		int encode(const qint32 input[], int inputSize);

	protected:

		QAbstractCodec::Error initializeLibrary();

};

#endif
