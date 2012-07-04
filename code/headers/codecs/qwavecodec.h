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

		bool initializeEncode();
		bool finalizeEncode();
		void encode(const void *input, int samples);

		bool initializeDecode();
		bool finalizeDecode();
		void decode(const void *input, int size);

	protected:

		QAbstractCodec::Header inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content);
		void createHeader(QByteArray &header, const QCodecFormat &format, QCodecContent &content);

		QAbstractCodec::Error initializeLibrary();
		short toShort(char data[]);
		int toInt(char data[]);

	private:

		QSampleConverter mConverter;

};

#endif
