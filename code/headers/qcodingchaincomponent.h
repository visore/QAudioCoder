#ifndef QCODINGCHAINCOMPONENT_H
#define QCODINGCHAINCOMPONENT_H

#include <QMutex>
#include <QThread>
#include <QFile>
#include <qabstractcoder.h>
#include <qsharedbuffer.h>

/**********************************************************
QCodingChainComponent
**********************************************************/

class QCodingChainComponent : public QThread
{

	Q_OBJECT

	signals:

		void wasFinished();

	public slots:

		virtual void dataAvailable();
		virtual void processData(int size);

		void finish();

	public:

		QCodingChainComponent();
		~QCodingChainComponent();
		void setInputBuffer(QSharedBuffer *buffer);
		void setOutputBuffer(QSharedBuffer *buffer);

		void setNext(QCodingChainComponent *next);

		void initialize();
		void run();
		void finalize();

		virtual void initializeComponent() = 0;
		virtual void executeComponent() = 0;
		virtual void finalizeComponent() = 0;

	protected:

		void (QCodingChainComponent::*runPointer)();

		QCodingChainComponent *mNext;
		QSharedBuffer *mInputBuffer;
		QSharedBuffer *mOutputBuffer;
		int mChunksToRead;
		bool mFinishUp;

};

/**********************************************************
QCodingChainInput
**********************************************************/

class QCodingChainInput : public QCodingChainComponent
{

	Q_OBJECT

	public:

		QCodingChainInput();

};

/**********************************************************
QCodingChainFileInput
**********************************************************/

class QCodingChainFileInput : public QCodingChainInput
{

	Q_OBJECT

	public slots:

		void initializeComponent();
		void executeComponent();
		void finalizeComponent();

	public:

		QCodingChainFileInput();
		void setFilePath(QString filePath);

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
		void setCoder(QAbstractCoder *coder);

	protected:

		QAbstractCoder *mCoder;

};

/**********************************************************
QCodingChainDecoder
**********************************************************/

class QCodingChainDecoder : public QCodingChainCoder
{

	Q_OBJECT

	public slots:

		void initializeComponent();
		void finalizeComponent();

	public:

		QCodingChainDecoder();
		void executeComponent();

};

/**********************************************************
QCodingChainEncoder
**********************************************************/

class QCodingChainEncoder : public QCodingChainCoder
{

	Q_OBJECT

	public slots:

		void initializeComponent();
		void finalizeComponent();

	public:

		QCodingChainEncoder();
		void executeComponent(){}

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

		void initializeComponent();
		void finalizeComponent();

	public:

		QCodingChainFileOutput();
		void setFilePath(QString filePath);
		void executeComponent(){}

	protected:

		QString mFilePath;
		QFile mFile;

};

#endif
