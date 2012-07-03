#include <qaudiocoder.h>

QAudioCoder::QAudioCoder()
	: QObject()
{
	/*mDecoder = NULL;
	mEncoder = NULL;*/
	
	QObject::connect(&mChain, SIGNAL(finished()), this, SIGNAL(finished()));
}

void QAudioCoder::encode(const QByteArray *data, const QString filePath)
{

}

void QAudioCoder::convert(const QString inputFilePath, const QString outputFilePath, QCodecFormat outputFormat)
{
	mChain.setInputFilePath(inputFilePath);
	mChain.setOutputFilePath(outputFilePath);

	mChain.start();


	//mCodecExecutor.setFormat(QAudio::AudioOutput, outputFormat);
	//mCodecExecutor.setData(inputFilePath, outputFilePath);

	/*mDecoder = &mFileDecoder;
	mEncoder = &mFileEncoder;

	mFileDecoder.setFilePath(inputFilePath);
	mFileEncoder.setFilePath(outputFilePath);
	QObject::connect(&mFileDecoder, SIGNAL(finished()), &mFileEncoder, SLOT(finalize()));

	QCodecFormat format;
	format.setChannelCount(2);
	format.setSampleSize(16);
	format.setSampleRate(44100);
	format.setSampleType(QAudioFormat::SignedInt);

	QList<QAbstractCodec*> codecs = mCodecManager.availableCodecs();
	if(codecs.size()!=1)
	{
		cout<<"No enough codecs available!"<<endl;
	}
	else
	{
		codecs[0]->load();

		startDecoder(codecs[0], format);
		startEncoder(codecs[0], outputFormat);

		codecs[0]->unload();
	}*/
}

void QAudioCoder::startDecoder(QAbstractCodec *codec, QCodecFormat format)
{
	/*codec->setFormat(QAudio::AudioInput, format);
	mDecoder->setCodec(codec);
	mDecoder->start();*/
}

void QAudioCoder::startEncoder(QAbstractCodec *codec, QCodecFormat format)
{
	/*codec->setFormat(QAudio::AudioOutput, format);
	mEncoder->setCodec(codec);
	mEncoder->start();*/
}
