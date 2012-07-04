#ifndef QCODINGCHAINCOMPONENT_H
#define QCODINGCHAINCOMPONENT_H

#include <QMutex>
#include <QThread>
#include <QFile>
#include <qabstractcodec.h>
#include <qsharedbuffer.h>

/**********************************************************
QCodingChainComponent
**********************************************************/

class QCodingChainComponent : public QThread
{

	Q_OBJECT

	public slots:

		virtual bool initialize() = 0;
		virtual bool finalize() = 0;
		virtual void dataAvailable();
		virtual void addData(int size);

	public:

		QCodingChainComponent();
		void setInputBuffer(QSharedBuffer *buffer);
		void setOutputBuffer(QSharedBuffer *buffer);
		virtual void run() = 0;

	protected:

		QSharedBuffer *mInputBuffer;
		QSharedBuffer *mOutputBuffer;	

};

/**********************************************************
QCodingChainInput
**********************************************************/

class QCodingChainInput : public QCodingChainComponent
{

	Q_OBJECT

	signals:

		void atEnd();

	public slots:

		void addData(int size);

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
