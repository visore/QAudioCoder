#include <qaudiocoder.h>
#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <QBuffer>
#include <QString>

#define INTERVAL 0.2

QAudioCoder coder;
QExtendedAudioFormat format;
QByteArray data;
QBuffer buffer;
QAudioOutput *output = NULL;
int songLength = 0;
QString songLengthString;

QWidget *window = NULL;
QGridLayout *layout = NULL;
QLineEdit *lineEdit = NULL;
QPushButton *openButton = NULL;
QPushButton *playButton = NULL;
QProgressBar *progressBar = NULL;

void showError()
{
	QMessageBox::critical(window, "Error", coder.errorString());
	progressBar->setValue(0);
	progressBar->setFormat("Error");
}

QString supportedFileTypes()
{
	QString types = "All Supported Files (";
	QStringList allExtensions;
	QCodecList codecs = QAudioCoder::codecs();
	for(int i = 0; i < codecs.size(); ++i)
	{
		QStringList extensions = codecs[i]->extensions("*.");
		allExtensions.append(extensions);
	}
	for(int i = 0; i < allExtensions.size(); ++i)
	{
		types += allExtensions[i];
		if(i != allExtensions.size() - 1)
		{
			types += " ";
		}
	}
	types += ")";
	return types;
}

QString fileTypes()
{
	QString types = "All Files (*.*);;";
	QString otherTypes = "";
	QCodecList codecs = QAudioCoder::codecs();

	for(int i = 0; i < codecs.size(); ++i)
	{
		otherTypes += codecs[i]->abbreviations()[0] + " Files (";
		QStringList extensions = codecs[i]->extensions("*.");
		for(int j = 0; j < extensions.size(); ++j)
		{
			otherTypes += extensions[j];
			if(j != extensions.size() - 1)
			{
				otherTypes += " ";
			}
		}
		otherTypes += ")";
		if(i != codecs.size() - 1)
		{
			otherTypes += ";;";
		}
	}

	types += supportedFileTypes() + ";;" + otherTypes;
	return types;
}

QString timeString(int seconds)
{
	QString result = "";
	int value = seconds / 60;
	if(value < 10)
	{
		result += "0";
	}
	result += QString::number(value) + ":";
	value = seconds % 60;
	if(value < 10)
	{
		result += "0";
	}
	result += QString::number(value);
	return result;
}

void openFile()
{
	QString selectedFilter = supportedFileTypes();
	QString filePath = QFileDialog::getOpenFileName(window, "Open Audio File", QDir::homePath(), fileTypes(), &selectedFilter);
	lineEdit->setText(filePath);
}

void progressPlay()
{
	qreal seconds = (output->processedUSecs() / 1000000.0) - ((output->bufferSize() - output->bytesFree()) / (format.channelCount() * format.sampleSize() / 8) / format.sampleRate());
	progressBar->setFormat(timeString(seconds) + songLengthString);
	progressBar->setValue((seconds / songLength) * 100);
}

void playFile()
{
	songLength = data.size() / ((format.sampleSize() / 8) * format.sampleRate() * format.channelCount());
	songLengthString = " / " + timeString(songLength);

	progressBar->setFormat("00:00" + songLengthString);
	progressBar->setValue(0);
	QAudioFormat audioFormat = format.toQAudioFormat();
	audioFormat.setCodec("audio/pcm");

	if(output != NULL)
	{
		delete output;
	}

	output = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), audioFormat);
	output->setNotifyInterval(INTERVAL * 100);
	QObject::connect(output, &QAudioOutput::notify, progressPlay);
	buffer.setBuffer(&data);
	buffer.open(QIODevice::ReadOnly);
	output->start(&buffer);

	//For ALSA underrun problem
	output->suspend();
	output->resume();
}

void decodeFile()
{
	if(output != NULL)
	{
		output->stop();
	}
	buffer.close();
	data.clear();
	progressBar->setTextVisible(true);
	progressBar->setFormat("Decoding");
	coder.decode(lineEdit->text(), data, format);
}

void initialize()
{
	window = new QWidget();
	window->resize(600, 50);
	window->setWindowTitle("QAudioCoder - Decode and Play");

	layout = new QGridLayout(window);
	lineEdit = new QLineEdit(window);
	openButton = new QPushButton("Open", window);
	playButton = new QPushButton("Play", window);
	progressBar = new QProgressBar(window);
	progressBar->setRange(0, 100);
	progressBar->setTextVisible(false);

	layout->addWidget(lineEdit, 0, 0);
	layout->addWidget(openButton, 0, 1);
	layout->addWidget(progressBar, 1, 0);
	layout->addWidget(playButton, 1, 1);

	QObject::connect(openButton, &QPushButton::clicked, openFile);
	QObject::connect(playButton, &QPushButton::clicked, decodeFile);
	QObject::connect(&coder, &QAudioCoder::progressed, progressBar, &QProgressBar::setValue);
	QObject::connect(&coder, &QAudioCoder::finished, playFile);
	QObject::connect(&coder, &QAudioCoder::failed, showError);

	window->show();
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	initialize();
	application.exec();
	delete window;
	if(output != NULL)
	{
		delete output;
	}
	return 0;
}
