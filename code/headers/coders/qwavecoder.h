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

		bool initializeEncode();
		bool finalizeEncode();
		void encode(const void *input, int samples);

		bool initializeDecode();
		bool finalizeDecode();
		void decode(const void *input, int size);

	protected:

		QAbstractCoder::Header inspectHeader(const QByteArray &header, QExtendedAudioFormat &format, QAudioInfo &content);
		void createHeader(QByteArray &header, const QExtendedAudioFormat &format, QAudioInfo &content);

		QAbstractCoder::Error initializeLibrary();
		short toShort(char data[]);
		int toInt(char data[]);

	private:

		QSampleConverter mConverter;

};

#endif
