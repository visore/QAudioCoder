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

QCodecFormat format;
format.setChannelCount(2);
format.setSampleRate(44100);
format.setSampleSize(16);
format.setBitrate(128);

QAudioCoder coder;
coder.convert("/home/visore/a.wav", "/home/visore/meee.wav", format);



signed int g = 40000;
unsigned int a = g;

QMainWindow w;
w.show();
application.exec();

}
