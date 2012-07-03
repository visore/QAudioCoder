#ifndef QAUDIOCODER_H
#define QAUDIOCODER_H

#include <qcodingchain.h>

class QAudioCoder : public QObject
{

	Q_OBJECT

	signals:

		void finished();

	public:

		QAudioCoder();

		void addSearchPath(QString path);
		void addFileName(QString codec, QString name);
		void addFileExtension(QString codec, QString extension);

		void encode(const QByteArray *data, const QString filePath);
		void convert(const QString inputFilePath, const QString outputFilePath, QCodecFormat outputFormat);

	protected:

		void startDecoder(QAbstractCodec *codec, QCodecFormat format);
		void startEncoder(QAbstractCodec *codec, QCodecFormat format);

	private:

		QCodingChain mChain;

};

#endif
