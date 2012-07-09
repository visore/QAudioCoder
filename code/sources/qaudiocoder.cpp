#include <qaudiocoder.h>

QAudioCoder::QAudioCoder()
	: QObject()
{
	mChain = new QCodingChain();
	QObject::connect(mChain, SIGNAL(finished()), this, SIGNAL(finished()));
}

void QAudioCoder::encode(const QByteArray *data, const QString filePath)
{

}

void QAudioCoder::convert(const QString inputFilePath, const QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain->setInputFilePath(inputFilePath);
	mChain->setOutputFilePath(outputFilePath);
	mChain->setOutputFormat(outputFormat);
	mChain->start();
}
