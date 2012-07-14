#include <qaudiocoder.h>
#include <QApplication>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QAudioInput>
#include <QAudioDeviceInfo>
#include <QBuffer>
#include <QString>
#include <QFile>

#define INTERVAL 0.2

QAudioCoder coder;
QExtendedAudioFormat format;
QByteArray data;
QBuffer buffer;
QAudioInput *input = NULL;

QWidget *window = NULL;
QGridLayout *layout = NULL;
QLineEdit *lineEdit = NULL;
QPushButton *selectButton = NULL;
QPushButton *saveButton = NULL;
QProgressBar *progressBar = NULL;
QComboBox *comboBox = NULL;
QLabel *label = NULL;

QString fileTypes()
{
	QString types = "";
	QAudioCodec *codec = QAudioManager::instance().codec(comboBox->currentText());
	types += codec->abbreviations()[0] + " Files (";
	QStringList extensions = codec->extensions("*.");
	for(int j = 0; j < extensions.size(); ++j)
	{
		types += extensions[j];
		if(j != extensions.size() - 1)
		{
			types += " ";
		}
	}
	types += ")";
	return types;
}


void selectFile()
{
	QString filePath = QFileDialog::getSaveFileName(window, "Save Audio File", QDir::homePath(), fileTypes());
	lineEdit->setText(filePath);
}

void saveFile()
{
	if(lineEdit->text() == "")
	{
		QMessageBox::warning(window, "Invalid File", "Please provide a valid file path.");
		return;
	}
	input->stop();
	
	label->setText("Encoding");
	format.setCodec(comboBox->currentText());
	progressBar->setRange(0, 100);
	coder.encode(data, format, lineEdit->text(), format);
}

void finish()
{
	label->setText("Finished");
}

void initialize()
{
	QAudioFormat audioFormat;
	audioFormat.setSampleSize(16);
	audioFormat.setSampleRate(44100);
	audioFormat.setSampleType(QAudioFormat::SignedInt);
	audioFormat.setChannelCount(2);
	audioFormat.setByteOrder(QAudioFormat::LittleEndian);
	audioFormat.setCodec("audio/pcm");
	
	format = QExtendedAudioFormat(audioFormat);
	format.setBitrateMode(QExtendedAudioFormat::ConstantBitrate);
	format.setBitrate(256);

	input = new QAudioInput(audioFormat);
	buffer.setBuffer(&data);
	buffer.open(QIODevice::WriteOnly);
	input->start(&buffer);

	window = new QWidget();
	window->resize(600, 50);
	window->setWindowTitle("QAudioCoder - Record and Save");

	layout = new QGridLayout(window);
	lineEdit = new QLineEdit(window);
	selectButton = new QPushButton("Select", window);
	saveButton = new QPushButton("Save", window);
	progressBar = new QProgressBar(window);
	progressBar->setValue(0);
	progressBar->setRange(0, 0);
	progressBar->setTextVisible(false);
	comboBox = new QComboBox(window);
	QCodecList codecs = QAudioCoder::codecs();
	for(int i = 0; i < codecs.size(); ++i)
	{
		comboBox->addItem(codecs[i]->abbreviations()[0], codecs[i]->abbreviations()[0]);
	}
	label = new QLabel(window);
	label->setText("Recording");

	layout->addWidget(comboBox, 0, 0);
	layout->addWidget(lineEdit, 0, 1);
	layout->addWidget(selectButton, 0, 2);
	layout->addWidget(label, 1, 0);
	layout->addWidget(progressBar, 1, 1);
	layout->addWidget(saveButton, 1, 2);

	QObject::connect(selectButton, &QPushButton::clicked, selectFile);
	QObject::connect(saveButton, &QPushButton::clicked, saveFile);
	QObject::connect(&coder, &QAudioCoder::progressed, progressBar, &QProgressBar::setValue);
	QObject::connect(&coder, &QAudioCoder::finished, finish);

	window->show();
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	initialize();
	application.exec();
	delete window;
	if(input != NULL)
	{
		delete input;
	}
	return 0;
}
