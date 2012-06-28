#ifndef QAUDIOCODER_H
#define QAUDIOCODER_H

#include <QThread>
#include <qcodecmanager.h>

class QAudioCoderThread;

class QAudioCoder : public QObject
{

	Q_OBJECT

	signals:

		void finished();

	public:

		enum Error
		{
			NoError = 0,
			InputFileError = 1,
			OutputFileError = 2
		};

		QAudioCoder();
		~QAudioCoder();

		void addSearchPath(QString path);
		void addFileName(QString codec, QString name);
		void addFileExtension(QString codec, QString extension);

		void encode(const QByteArray *data, const QString filePath);
		void convert(const QString inputFilePath, const QString outputFilePath, QCodecFormat outputFormat);

	private:

		QAudioCoderThread *mThread;
		QCodecManager mCodecManager;

};

class QAudioCoderThread : public QThread
{

	public:

		enum Mode
		{
			Undefinied = 0,
			FileToFile = 1,
			FileToData = 2,
			DataToData = 3,
			DataToFile = 4
		};

		QAudioCoderThread();

		void setCodec(QAbstractCodec *codec);

		void setData(const QString inputFilePath, const QString outputFilePath);

		QCodecFormat format(QAudio::Mode mode);
		void setFormat(QAudio::Mode mode, QCodecFormat format);

		QAudioCoder::Error error();

		void run();

	protected:

		void fileToFile();

		void setError(QAudioCoder::Error error);

		int encode8(const char input[], int inputSize, char output[], int outputSize);
		int encode16(const char input[], int inputSize, char output[], int outputSize);
		int encode32(const char input[], int inputSize, char output[], int outputSize);

	private:

		int (QAudioCoderThread::*encode)(const char[], int, char[], int);

		QAudioCoderThread::Mode mMode;
		QAudioCoder::Error mError;
		QAbstractCodec *mCodec;

		QByteArray *mInputData;
		QByteArray *mOutputData;
		QString mInputPath;
		QString mOutputPath;

		QCodecFormat mInputFormat;
		QCodecFormat mOutputFormat;
		int mSampleDifference;

};

#endif
