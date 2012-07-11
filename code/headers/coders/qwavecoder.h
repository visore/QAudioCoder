#ifndef QWAVECODER_H
#define QWAVECODER_H

#include <qabstractcoder.h>
#include <qsampleconverter.h>

class QWaveCoder : public QAbstractCoder
{

	public:

		QWaveCoder();

		QAbstractCoder::Error load();
		QAbstractCoder::Error load(QString filePath);
		bool unload();

		QAudioCodec* detectCodec(const QByteArray &data);
		QByteArray& header();
		int headerSize();

		bool initializeEncode();
		bool finalizeEncode();
		void encode(const void *input, int samples);

		bool initializeDecode();
		bool finalizeDecode();
		void decode(const void *input, int size);

	protected:

		void decodeHeader(const void *input, int size);
		void decodeData(const void *input, int size);

		QAbstractCoder::Error initializeLibrary();
		short toShort(char data[]);
		int toInt(char data[]);

	private:

		void (QWaveCoder::*decodePointer)(const void *input, int size);

		QSampleConverter mConverter;
		qint64 mSamples;

};

#endif
