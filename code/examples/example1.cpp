#include <qaudiocoder.h>
#include <QApplication>
#include <QMainWindow>


#include <iostream>
using namespace std;

#include <QString>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);

			QExtendedAudioFormat format;
			format.setSampleSize(16);
			format.setSampleType(QExtendedAudioFormat::SignedInt);
			format.setSampleRate(44100);
			format.setChannelCount(2);
			format.setBitrateMode(QExtendedAudioFormat::ConstantBitrate);
			format.setBitrate(320);
			format.setBitrate(320, QExtendedAudioFormat::MinimumBitrate);
			format.setBitrate(320, QExtendedAudioFormat::MaximumBitrate);
			format.setQuality(QExtendedAudioFormat::Minimum);
			format.setCodec("WAV");

QByteArray a;

QAudioCoder coder;
//coder.convert("/home/visore/data/cold.flac", a, format);
coder.convert("/home/visore/data/ev.mp3", "/home/visore/meee.wav", format);
//coder.decode(QString("/home/visore/data/ev.mp3"), a);

QMainWindow w;
w.show();
application.exec();

}
