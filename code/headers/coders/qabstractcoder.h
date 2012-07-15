#ifndef QABSTRACTCODER_H
#define QABSTRACTCODER_H

#include <QQueue>
#include <QMutex>
#include <QByteArray>
#include <QStringList>
#include <QLibrary>
#include <qaudio.h>
#include <qextendedaudioformat.h>
#include <qaudioinfo.h>
#include <qsamplearray.h>

class QAbstractCoder : public QObject
{

	Q_OBJECT

	signals:

		void failed(QCoder::Error error);
		void decoded(QSampleArray *array);
		void encoded(QSampleArray *array);
		void formatChanged(QExtendedAudioFormat format);

	public:

		QAbstractCoder();
		~QAbstractCoder();

		const QList<QAudioCodec*> supportedCodecs() const;
		virtual QAudioCodec* detectCodec(const QByteArray &data) = 0;
		virtual QByteArray& header() = 0;
		virtual int headerSize() = 0;

		virtual bool initializeDecode() = 0;
		virtual bool finalizeDecode() = 0;
		virtual void decode(const void *input, int size) = 0;

		virtual bool initializeEncode() = 0;
		virtual bool finalizeEncode() = 0;
		virtual void encode(const void *input, int samples) = 0;
		
		virtual QCoder::Error load();
		virtual QCoder::Error load(QString filePath);
		virtual bool unload();

		QString filePath() const;
		void setFilePath(QString filePath);

		QExtendedAudioFormat format(QAudio::Mode mode) const;
		void setFormat(QAudio::Mode mode, QExtendedAudioFormat format);

		QString name() const;
		QString version() const;
		QStringList fileNames() const;
		QStringList fileExtensions() const;
		void addFileName(QString name);
		void addFileExtension(QString extension);

		QCoder::Error error() const;

		bool operator == (const QAbstractCoder &other) const;
		bool operator != (const QAbstractCoder &other) const;

	protected:

		virtual QCoder::Error initializeLibrary() = 0;
		void setError(QCoder::Error error);

	protected:

		QLibrary mLibrary;

		QString mName;
		QString mVersion;
		QStringList mFileNames;
		QStringList mFileExtensions;

		QByteArray mHeader;

		QList<QAudioCodec*> mSupportedCodecs;

		QExtendedAudioFormat mInputFormat;
		QExtendedAudioFormat mOutputFormat;

	private:

		QCoder::Error mError;

};

#endif
