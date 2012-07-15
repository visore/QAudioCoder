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

QAudioCoder coder;
QExtendedAudioFormat format;

QWidget *window = NULL;
QGridLayout *layout = NULL;
QLineEdit *lineEdit1 = NULL;
QLineEdit *lineEdit2 = NULL;
QPushButton *selectButton1 = NULL;
QPushButton *selectButton2 = NULL;
QPushButton *convertButton = NULL;
QProgressBar *progressBar = NULL;
QComboBox *comboBox = NULL;
QLabel *label1 = NULL;
QLabel *label2 = NULL;

void showError()
{
	QMessageBox::critical(window, "Error", coder.errorString());
	progressBar->setValue(0);
	progressBar->setFormat("Error");
}

QString fileFormats()
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

void selectFile1()
{
	QString selectedFilter = supportedFileTypes();
	QString filePath = QFileDialog::getOpenFileName(window, "Open Audio File", QDir::homePath(), fileTypes(), &selectedFilter);
	lineEdit1->setText(filePath);
}

void selectFile2()
{
	QString filePath = QFileDialog::getSaveFileName(window, "Save Audio File", QDir::homePath(), fileFormats());
	lineEdit2->setText(filePath);
}

void convertFile()
{
	progressBar->setTextVisible(true);
	progressBar->setFormat("Converting");
	format.setCodec(comboBox->currentText());
	coder.convert(lineEdit1->text(), lineEdit2->text(), format);
}

void finish()
{
	progressBar->setFormat("Finished");
}

void initialize()
{
	QAudioFormat audioFormat;
	format.setSampleSize(16);
	format.setSampleRate(44100);
	format.setSampleType(QExtendedAudioFormat::SignedInt);
	format.setChannelCount(2);
	format.setByteOrder(QExtendedAudioFormat::LittleEndian);
	format.setBitrateMode(QExtendedAudioFormat::VariableBitrate);
	format.setBitrate(128, QExtendedAudioFormat::MinimumBitrate);
	format.setBitrate(320, QExtendedAudioFormat::MaximumBitrate);

	window = new QWidget();
	window->resize(600, 50);
	window->setWindowTitle("QAudioCoder - Convert Audio Files");

	layout = new QGridLayout(window);

	lineEdit1 = new QLineEdit(window);
	selectButton1 = new QPushButton("Select", window);
	label1 = new QLabel(window);
	label1->setText("Input:");

	lineEdit2 = new QLineEdit(window);
	selectButton2 = new QPushButton("Select", window);
	label2 = new QLabel(window);
	label2->setText("Output:");
	comboBox = new QComboBox(window);
	QCodecList codecs = QAudioCoder::codecs();
	for(int i = 0; i < codecs.size(); ++i)
	{
		comboBox->addItem(codecs[i]->abbreviations()[0], codecs[i]->abbreviations()[0]);
	}

	convertButton = new QPushButton("Convert", window);
	progressBar = new QProgressBar(window);
	progressBar->setValue(0);
	progressBar->setRange(0, 100);
	progressBar->setTextVisible(false);

	layout->addWidget(label1, 0, 0);
	layout->addWidget(lineEdit1, 0, 1, 1, 2);
	layout->addWidget(selectButton1, 0, 3);
	layout->addWidget(label2, 1, 0);
	layout->addWidget(comboBox, 1, 1);
	layout->addWidget(lineEdit2, 1, 2);
	layout->addWidget(selectButton2, 1, 3);
	layout->addWidget(progressBar, 2, 0, 1, 3);
	layout->addWidget(convertButton, 2, 3);

	QObject::connect(selectButton1, &QPushButton::clicked, selectFile1);
	QObject::connect(selectButton2, &QPushButton::clicked, selectFile2);
	QObject::connect(convertButton, &QPushButton::clicked, convertFile);
	QObject::connect(&coder, &QAudioCoder::progressed, progressBar, &QProgressBar::setValue);
	QObject::connect(&coder, &QAudioCoder::finished, finish);
	QObject::connect(&coder, &QAudioCoder::failed, showError);

	window->show();
}

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	initialize();
	application.exec();
	delete window;
	return 0;
}
