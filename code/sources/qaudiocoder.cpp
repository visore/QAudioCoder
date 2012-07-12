#include <qaudiocoder.h>

QAudioCoder::QAudioCoder()
	: QObject()
{
	QObject::connect(&mChain, SIGNAL(finished()), this, SIGNAL(finished()));
	QObject::connect(&mChain, SIGNAL(progressed(qreal)), this, SIGNAL(progressed(qreal)));
}

void QAudioCoder::convert(const QString inputFilePath, const QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain.setMode(QCodingChain::ConvertFileToFile);
	mChain.setInput(inputFilePath);
	mChain.setOutput(outputFilePath);
	mChain.setOutput(outputFormat);
	mChain.start();
}

void QAudioCoder::convert(const QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat)
{
	mChain.setMode(QCodingChain::ConvertDataToData);
	mChain.setInput(input);
	mChain.setOutput(output);
	mChain.setInput(inputFormat);
	mChain.setOutput(outputFormat);
	mChain.start();
}

void QAudioCoder::convert(const QString inputFilePath, QByteArray &output, QExtendedAudioFormat outputFormat)
{
	mChain.setMode(QCodingChain::ConvertFileToData);
	mChain.setInput(inputFilePath);
	mChain.setOutput(output);
	mChain.setOutput(outputFormat);
	mChain.start();
}

void QAudioCoder::convert(const QByteArray &input, QExtendedAudioFormat inputFormat, const QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain.setMode(QCodingChain::ConvertDataToFile);
	mChain.setInput(input);
	mChain.setOutput(outputFilePath);
	mChain.setInput(inputFormat);
	mChain.setOutput(outputFormat);
	mChain.start();
}

void QAudioCoder::decode(const QString inputFilePath, QByteArray &output, QExtendedAudioFormat &inputFormat)
{
	mChain.setMode(QCodingChain::DecodeFile);
	mChain.setInput(inputFilePath);
	mChain.setOutput(output);
	mChain.setInput(inputFormat);
	mChain.start();
}

void QAudioCoder::decode(const QByteArray &input, QByteArray &output, QExtendedAudioFormat &inputFormat)
{
	mChain.setMode(QCodingChain::DecodeData);
	mChain.setInput(input);
	mChain.setOutput(output);
	mChain.setInput(inputFormat);
	mChain.start();
}

void QAudioCoder::encode(const QByteArray &input, QExtendedAudioFormat inputFormat, const QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain.setMode(QCodingChain::EncodeData);
	mChain.setInput(input);
	mChain.setOutput(outputFilePath);
	mChain.setInput(inputFormat);
	mChain.setOutput(outputFormat);
	mChain.start();
}

void QAudioCoder::encode(const QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat)
{
	mChain.setMode(QCodingChain::EncodeData);
	mChain.setInput(input);
	mChain.setOutput(output);
	mChain.setInput(inputFormat);
	mChain.setOutput(outputFormat);
	mChain.start();
}
