#include <qaudiocoder.h>

QAudioCoder::QAudioCoder()
	: QObject()
{
	QObject::connect(&mChain, SIGNAL(finished()), this, SIGNAL(finished()));
}

void QAudioCoder::convert(const QString inputFilePath, const QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain.setInputFilePath(inputFilePath);
	mChain.setOutputFilePath(outputFilePath);
	mChain.setOutputFormat(outputFormat);
	mChain.start();
}
