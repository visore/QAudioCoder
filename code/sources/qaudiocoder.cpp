#include <qaudiocoder.h>

QAudioCoder::QAudioCoder()
	: QObject()
{
	qRegisterMetaType<QExtendedAudioFormat>("QExtendedAudioFormat");
	qRegisterMetaType<QCoder::Error>("QCoder::Error");

	mChain = new QCodingChain();
	QObject::connect(mChain, SIGNAL(finished()), this, SIGNAL(finished()));
	QObject::connect(mChain, SIGNAL(progressed(qreal)), this, SIGNAL(progressed(qreal)));
	QObject::connect(mChain, SIGNAL(failed(QCoder::Error)), this, SLOT(setError(QCoder::Error)));
}

QAudioCoder::~QAudioCoder()
{
	delete mChain;
}

void QAudioCoder::setError(QCoder::Error error)
{
	mError = error;
	if(mError != QCoder::NoError)
	{
		emit failed(mError);
	}
}

QCoder::Error QAudioCoder::error()
{
	return mError;
}

QString QAudioCoder::errorString()
{
	return QCoder::errorString(mError);
}

void QAudioCoder::convert(QString inputFilePath, QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain->setMode(QCodingChain::ConvertFileToFile);
	mChain->setInputPath(inputFilePath);
	mChain->setOutputPath(outputFilePath);
	mChain->setOutputFormat(outputFormat);
	mChain->start();
}

void QAudioCoder::convert(QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat)
{
	mChain->setMode(QCodingChain::ConvertDataToData);
	mChain->setInputData(input);
	mChain->setOutputData(output);
	mChain->setInputFormat(inputFormat);
	mChain->setOutputFormat(outputFormat);
	mChain->start();
}

void QAudioCoder::convert(QString inputFilePath, QByteArray &output, QExtendedAudioFormat outputFormat)
{
	mChain->setMode(QCodingChain::ConvertFileToData);
	mChain->setInputPath(inputFilePath);
	mChain->setOutputData(output);
	mChain->setOutputFormat(outputFormat);
	mChain->start();
}

void QAudioCoder::convert(QByteArray &input, QExtendedAudioFormat inputFormat, QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain->setMode(QCodingChain::ConvertDataToFile);
	mChain->setInputData(input);
	mChain->setOutputPath(outputFilePath);
	mChain->setInputFormat(inputFormat);
	mChain->setOutputFormat(outputFormat);
	mChain->start();
}

void QAudioCoder::decode(QString inputFilePath, QByteArray &output, QExtendedAudioFormat &inputFormat)
{
	mChain->setMode(QCodingChain::DecodeFile);
	mChain->setInputPath(inputFilePath);
	mChain->setOutputData(output);
	mChain->setInputFormat(&inputFormat);
	mChain->start();
}

void QAudioCoder::decode(QByteArray &input, QByteArray &output, QExtendedAudioFormat &inputFormat)
{
	mChain->setMode(QCodingChain::DecodeData);
	mChain->setInputData(input);
	mChain->setOutputData(output);
	mChain->setInputFormat(&inputFormat);
	mChain->start();
}

void QAudioCoder::encode(QByteArray &input, QExtendedAudioFormat inputFormat, QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain->setMode(QCodingChain::EncodeData);
	mChain->setInputData(input);
	mChain->setOutputPath(outputFilePath);
	mChain->setInputFormat(inputFormat);
	mChain->setOutputFormat(outputFormat);
	mChain->start();
}

void QAudioCoder::encode(QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output, QExtendedAudioFormat outputFormat)
{
	mChain->setMode(QCodingChain::EncodeData);
	mChain->setInputData(input);
	mChain->setOutputData(output);
	mChain->setInputFormat(inputFormat);
	mChain->setOutputFormat(outputFormat);
	mChain->start();
}

QCoderList QAudioCoder::coders(QAudioManager::Mode mode)
{
	return QAudioManager::instance().coders(mode);
}

QCodecList QAudioCoder::codecs(QAudioManager::Mode mode)
{
	return QAudioManager::instance().codecs(mode);
}
