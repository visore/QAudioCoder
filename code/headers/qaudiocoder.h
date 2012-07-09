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

	private:

		QCodingChain *mChain;

};

#endif
