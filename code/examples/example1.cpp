#include <qaudiocoder.h>
#include <qmp3codec.h>
#include <qflaccodec.h>
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
format.setChannelCount(2);
format.setSampleRate(44100);
format.setSampleSize(16);
format.setBitrate(128);

QAudioCoder coder;
coder.convert("/home/visore/a.wav", "/home/visore/meee.mp3", format);
//coder.convert("/home/visore/data/ev.mp3", "/home/visore/meee.mp3", format);

QMp3Codec codec = QMp3Codec::instance();
QMp3Codec codec2 = QMp3Codec::instance();

QFlacCodec codec3 = QFlacCodec::instance();
QFlacCodec codec4 = QFlacCodec::instance();

QMainWindow w;
w.show();
application.exec();

}
