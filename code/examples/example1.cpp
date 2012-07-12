#include <qaudiocoder.h>
#include <QApplication>
#include <QMainWindow>


#include <iostream>
using namespace std;

#include <QString>
#include <QFile>

QExtendedAudioFormat format;

int printProgress(qreal progress)
{
	cout<<"Progress: "<<progress<<"%"<<endl;
	if(progress==100)
	{
		cout<<format.bitrate()<<endl;
	}
}


int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

			
			format.setSampleSize(32);
			format.setSampleType(QExtendedAudioFormat::SignedInt);
			format.setSampleRate(44100);
			format.setChannelCount(2);
			format.setBitrateMode(QExtendedAudioFormat::VariableBitrate);
			format.setBitrate(256);
			format.setBitrate(128, QExtendedAudioFormat::MinimumBitrate);
			format.setBitrate(320, QExtendedAudioFormat::MaximumBitrate);
			format.setQuality(QExtendedAudioFormat::Average);
			format.setCodec("MP3");

QByteArray a;

QAudioCoder coder;
QObject::connect(&coder, &QAudioCoder::progressed, printProgress);
//coder.convert("/home/visore/data/cold.flac", "/home/visore/meee.mp3", format);
//coder.convert("/home/visore/data/ev.mp3", "/home/visore/meee.wav", format)
coder.decode(QString("/home/visore/meee.mp3"), a, format);

QMainWindow w;
w.show();
application.exec();

}
