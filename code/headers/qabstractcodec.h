#ifndef QABSTRACTCODEC_H
#define QABSTRACTCODEC_H

#include <QByteArray>
#include <QStringList>
#include <QLibrary>
#include <qaudio.h>
#include <qcodecformat.h>


#include <iostream>
using namespace std;

class QAbstractCodec
{

	public:

		enum Error
		{
			NoError = 0,

			PathError = 1,	//File does not exist
			FileError = 2,	//File exists, but is not a library
			LibraryError = 3,	//File exists and is a library, but not the required library
			VersionError = 4,	//File exists and is the required library, but the version is not supported

			InitializationError = 5,
			EncoderError = 6,
			DecoderError = 7,
			BufferError = 8,

			SampleSizeError = 9,
			SampleRateError = 10,
			NumberOfChannelsError = 11
		};

		QAbstractCodec();
		~QAbstractCodec();

		virtual bool initialize() = 0;
		virtual bool finalize() = 0;

		virtual int encode(const qint8 input[], int inputSize, qint8 output[], int outputSize) = 0;
		virtual int encode(const qint16 input[], int inputSize, qint8 output[], int outputSize) = 0;
		virtual int encode(const qint32 input[], int inputSize, qint8 output[], int outputSize) = 0;

		QAbstractCodec::Error load();
		QAbstractCodec::Error load(QString filePath);
		bool unload();

		QString filePath();
		void setFilePath(QString filePath);

		QCodecFormat format(QAudio::Mode mode);
		void setFormat(QAudio::Mode mode, QCodecFormat format);

		QString name();
		QString version();
		QStringList fileNames();
		QStringList fileExtensions();
		void addFileName(QString name);
		void addFileExtension(QString extension);

		QAbstractCodec::Error error();

		bool operator == (const QAbstractCodec &other) const;

	protected:

		virtual QAbstractCodec::Error initializeLibrary() = 0;

	protected:

		QLibrary mLibrary;

		QString mName;
		QString mVersion;
		QStringList mFileNames;
		QStringList mFileExtensions;

		QAbstractCodec::Error mError;

		QCodecFormat mInputFormat;
		QCodecFormat mOutputFormat;

};

#endif
