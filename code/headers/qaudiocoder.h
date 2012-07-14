#ifndef QAUDIOCODER_H
#define QAUDIOCODER_H

#include <qcodingchain.h>

class QAudioCoder : public QObject
{

	Q_OBJECT

	signals:

		void progressed(qreal percentage);
		void finished();

	public:

		QAudioCoder();

		void addSearchPath(QString path);
		void addFileName(QString coder, QString name);
		void addFileExtension(QString coder, QString extension);

		void convert(QString inputFilePath, QString outputFilePath, QExtendedAudioFormat outputFormat);
		void convert(QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat);
		void convert(QString inputFilePath, QByteArray &output, QExtendedAudioFormat outputFormat);
		void convert(QByteArray &input, QExtendedAudioFormat inputFormat, QString outputFilePath, QExtendedAudioFormat outputFormat);

		void decode(QString inputFilePath, QByteArray &output, QExtendedAudioFormat &inputFormat);
		void decode(QByteArray &input, QByteArray &output, QExtendedAudioFormat &inputFormat);

		void encode(QByteArray &input, QExtendedAudioFormat inputFormat, QString outputFilePath, QExtendedAudioFormat outputFormat);
		void encode(QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat);

		static QCoderList coders(QAudioManager::Mode mode = QAudioManager::Available);
		static QCodecList codecs(QAudioManager::Mode mode = QAudioManager::Available);

	private:

		QCodingChain mChain;

};

#endif
