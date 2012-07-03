#ifndef QWAVECODEC_H
#define QWAVECODEC_H

#include <qabstractcodec.h>

class QWaveCodec : public QAbstractCodec
{

	public:

		QWaveCodec();

		QAbstractCodec::Error load();
		QAbstractCodec::Error load(QString filePath);
		bool unload();

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

		qreal mOuputSizeDifference;

};

#endif
