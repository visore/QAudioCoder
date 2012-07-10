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
			format.setBitrateMode(QExtendedAudioFormat::VariableBitrate);
			format.setBitrate(256);
			format.setBitrate(128, QExtendedAudioFormat::MinimumBitrate);
			format.setBitrate(320, QExtendedAudioFormat::MaximumBitrate);
			format.setCodec("WAV");

QAudioCoder coder;
coder.convert("/home/visore/a.wav", "/home/visore/meee.wav", format);
//coder.convert("/home/visore/data/ev.mp3", "/home/visore/meee.mp3", format);


QMainWindow w;
w.show();
application.exec();

}
