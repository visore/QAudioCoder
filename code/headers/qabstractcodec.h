#ifndef QABSTRACTCODEC_H
#define QABSTRACTCODEC_H

#include <QQueue>
#include <QByteArray>
#include <QStringList>
#include <QLibrary>
#include <qaudio.h>
#include <qcodecformat.h>
#include <qcodeccontent.h>
#include <qsamplearray.h>
#include <qsharedbuffer.h>

class QAbstractCodec : public QObject
{

	Q_OBJECT

	signals:

		void decoded(QSampleArray *array);
		void encoded(QSampleArray *array);

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
			SampleTypeError = 10,
			SampleRateError = 11,
			NumberOfChannelsError = 12
		};

		enum Header
		{
			ValidHeader = 0,
			NeedMoreData = 1,
			InvalidHeader = 2
		};

		QAbstractCodec();
		~QAbstractCodec();

		QAbstractCodec::Header inspectHeader(const QByteArray &header, QCodecContent &content);
		void createHeader(QByteArray &header, QCodecContent &content);

		virtual bool initializeDecode() = 0;
		virtual bool finalizeDecode() = 0;
		virtual void decode(const void *input, int size) = 0;

		virtual bool initializeEncode() = 0;
		virtual bool finalizeEncode() = 0;
		virtual void encode(const void *input, int samples) = 0;
		
		virtual QAbstractCodec::Error load();
		virtual QAbstractCodec::Error load(QString filePath);
		virtual bool unload();

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

		virtual QAbstractCodec::Header inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content) = 0;
		virtual void createHeader(QByteArray &header, const QCodecFormat &format, QCodecContent &content) = 0;

		virtual QAbstractCodec::Error initializeLibrary() = 0;

	protected:

		QLibrary mLibrary;

		QString mName;
		QString mVersion;
		QStringList mFileNames;
		QStringList mFileExtensions;
		int mHeaderSize;

		QAbstractCodec::Error mError;

		QCodecFormat mDecoderFormat;
		QCodecFormat mEncoderFormat;

};

#endif
