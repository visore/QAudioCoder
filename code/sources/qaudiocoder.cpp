#include <qaudiocoder.h>

QAudioCoder::QAudioCoder()
	: QObject()
{
	QObject::connect(&mCodecExecutor, SIGNAL(finished()), this, SIGNAL(finished()));
}

QAudioCoder::~QAudioCoder()
{
	delete mThread;
	mThread = NULL;
}

void QAudioCoder::encode(const QByteArray *data, const QString filePath)
{

}

void QAudioCoder::convert(const QString inputFilePath, const QString outputFilePath, QCodecFormat outputFormat)
{
	//mCodecExecutor.setFormat(QAudio::AudioOutput, outputFormat);
	//mCodecExecutor.setData(inputFilePath, outputFilePath);

	QList<QAbstractCodec*> codecs = mCodecManager.availableCodecs();
	if(codecs.size()!=2)
	{
		cout<<"No enough codecs available!"<<endl;
	}
	else
	{
		/*mCodecExecutor.setCodec(codecs[0]);
		mCodecExecutor.start();
		while(!mCodecExecutor.isFinished());*/
	}
}
