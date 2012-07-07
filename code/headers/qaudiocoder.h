#ifndef QAUDIOCODER_H
#define QAUDIOCODER_H

#include <qcodingchain.h>

class QAudioCoder : public QObject
{

	Q_OBJECT

	signals:

		void finished();

public slots: 
/*
void s()
{
QObject::disconnect(mChain, SIGNAL(finished()));
delete mChain;
	
	mChain = new QCodingChain();
	QObject::connect(mChain, SIGNAL(finished()), this, SLOT(s()));
mChain->setInputFilePath(a);
	mChain->setOutputFilePath(b);



	mChain->start();

}*/

	public:

		QAudioCoder();

		void addSearchPath(QString path);
		void addFileName(QString coder, QString name);
		void addFileExtension(QString coder, QString extension);

		void encode(const QByteArray *data, const QString filePath);
		void convert(const QString inputFilePath, const QString outputFilePath, QExtendedAudioFormat outputFormat);

	protected:

		void startDecoder(QAbstractCoder *coder, QExtendedAudioFormat format);
		void startEncoder(QAbstractCoder *coder, QExtendedAudioFormat format);

	private:

		QCodingChain *mChain;

QString a;
QString b;

};

#endif
