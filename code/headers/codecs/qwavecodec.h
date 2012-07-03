#ifndef QWAVECODEC_H
#define QWAVECODEC_H

#include <qabstractcodec.h>
#include <qsampleconverter.h>

class QWaveCodec : public QAbstractCodec
{

	public:

		QWaveCodec();

		QAbstractCodec::Error load();
		QAbstractCodec::Error load(QString filePath);
		bool unload();

		bool inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content);
		void createHeader(QByteArray &header, const QCodecFormat &format, const QCodecContent &content);

		bool initializeEncode();
		bool finalizeEncode();
		void encode(const void *input, int samples);

		bool initializeDecode();
		bool finalizeDecode();
		void decode(const void *input, int size);

	protected:

		QAbstractCodec::Error initializeLibrary();
		short toShort(char data[]);
		int toInt(char data[]);

	private:

		QSampleConverter mConverter;

		qreal mOuputSizeDifference;

};

#endif
