#ifndef QCODINGCHAINCOMPONENT_H
#define QCODINGCHAINCOMPONENT_H

#include <QMutex>
#include <QThread>
#include <QFile>
#include <qabstractcodec.h>

/**********************************************************
QCodingChainComponent
**********************************************************/

class QCodingChainComponent : public QThread
{

	Q_OBJECT

	signals:

		void available(QAudioChunk *chunk);

	public slots:

		virtual bool initialize() = 0;
		virtual bool finalize() = 0;
		void addChunk(QAudioChunk *chunk);

	public:

		QCodingChainComponent();
		bool hasChunk();
		int numberOfChunks();
		QAudioChunk* takeChunk();
		virtual void run() = 0;

	private:

		QMutex mMutex;
		QQueue<QAudioChunk*> mChunks;

};

/**********************************************************
QCodingChainInput
**********************************************************/

class QCodingChainInput : public QCodingChainComponent
{

	Q_OBJECT

	signals:

		void atEnd();

	public:

		QCodingChainInput();
		void skipHeader(int bytes);

	protected:

		int mHeaderSize;
		bool mAtEnd;

};

/**********************************************************
QCodingChainFileInput
**********************************************************/

class QCodingChainFileInput : public QCodingChainInput
{

	Q_OBJECT

	public slots:

		bool initialize();
		bool finalize();

	public:

		QCodingChainFileInput();
		void setFilePath(QString filePath);
		void run();

	protected:

		QString mFilePath;
		QFile mFile;

};

/**********************************************************
QCodingChainCoder
**********************************************************/

class QCodingChainCoder : public QCodingChainComponent
{

	Q_OBJECT

	public:

		QCodingChainCoder();
		void setCodec(QAbstractCodec *codec);

	protected:

		QAbstractCodec *mCodec;

};

/**********************************************************
QCodingChainDecoder
**********************************************************/

class QCodingChainDecoder : public QCodingChainCoder
{

	Q_OBJECT

	public slots:

		bool initialize();
		bool finalize();

	public:

		QCodingChainDecoder();
		void run();

};

/**********************************************************
QCodingChainEncoder
**********************************************************/

class QCodingChainEncoder : public QCodingChainCoder
{

	Q_OBJECT

	public slots:

		bool initialize();
		bool finalize();

	public:

		QCodingChainEncoder();
		void run();

};

/**********************************************************
QCodingChainOutput
**********************************************************/

class QCodingChainOutput : public QCodingChainComponent
{

	Q_OBJECT

	public:

		QCodingChainOutput();
		void setHeader(QByteArray header);

	protected:

		QByteArray mHeader;

};

/**********************************************************
QCodingChainFileOutput
**********************************************************/

class QCodingChainFileOutput : public QCodingChainOutput
{

	Q_OBJECT

	public slots:

		bool initialize();
		bool finalize();

	public:

		QCodingChainFileOutput();
		void setFilePath(QString filePath);
		void run();

	protected:

		QString mFilePath;
		QFile mFile;

};

#endif
