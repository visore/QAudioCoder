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
		void addFileName(QString coder, QString name);
		void addFileExtension(QString coder, QString extension);

		void convert(const QString inputFilePath, const QString outputFilePath, QExtendedAudioFormat outputFormat);
		void convert(const QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat);
		void convert(const QString inputFilePath, QByteArray &output, QExtendedAudioFormat outputFormat);
		void convert(const QByteArray &input, QExtendedAudioFormat inputFormat, const QString outputFilePath, QExtendedAudioFormat outputFormat);

		void decode(const QString inputFilePath, QByteArray &output);
		void decode(const QByteArray &input, QByteArray &output);

		void encode(const QByteArray &input, QExtendedAudioFormat inputFormat, const QString outputFilePath, QExtendedAudioFormat outputFormat);
		void encode(const QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat);

	private:

		QCodingChain mChain;

};

#endif
