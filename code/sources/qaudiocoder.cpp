#include <qaudiocoder.h>

QAudioCoder::QAudioCoder()
	: QObject()
{
	/*mDecoder = NULL;
	mEncoder = NULL;*/
	mChain = new QCodingChain();
	//QObject::connect(mChain, SIGNAL(finished()), this, SLOT(s()));
	//QObject::connect(mChain, SIGNAL(finished()), this, SIGNAL(finished()));
}

void QAudioCoder::encode(const QByteArray *data, const QString filePath)
{

}

void QAudioCoder::convert(const QString inputFilePath, const QString outputFilePath, QExtendedAudioFormat outputFormat)
{
	mChain->setInputFilePath(inputFilePath);
	mChain->setOutputFilePath(outputFilePath);

a = inputFilePath;
b = outputFilePath;

	mChain->start();

	//mCoderExecutor.setFormat(QAudio::AudioOutput, outputFormat);
	//mCoderExecutor.setData(inputFilePath, outputFilePath);

	/*mDecoder = &mFileDecoder;
	mEncoder = &mFileEncoder;

	mFileDecoder.setFilePath(inputFilePath);
	mFileEncoder.setFilePath(outputFilePath);
	QObject::connect(&mFileDecoder, SIGNAL(finished()), &mFileEncoder, SLOT(finalize()));

	QExtendedAudioFormat format;
	format.setChannelCount(2);
	format.setSampleSize(16);
	format.setSampleRate(44100);
	format.setSampleType(QAudioFormat::SignedInt);

	QList<QAbstractCoder*> coders = mCoderManager.availableCoders();
	if(coders.size()!=1)
	{
		cout<<"No enough coders available!"<<endl;
	}
	else
	{
		coders[0]->load();

		startDecoder(coders[0], format);
		startEncoder(coders[0], outputFormat);

		coders[0]->unload();
	}*/
}

void QAudioCoder::startDecoder(QAbstractCoder *coder, QExtendedAudioFormat format)
{
	/*coder->setFormat(QAudio::AudioInput, format);
	mDecoder->setCoder(coder);
	mDecoder->start();*/
}

void QAudioCoder::startEncoder(QAbstractCoder *coder, QExtendedAudioFormat format)
{
	/*coder->setFormat(QAudio::AudioOutput, format);
	mEncoder->setCoder(coder);
	mEncoder->start();*/
}
