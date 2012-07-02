#ifndef QCODINGCHAINCOMPONENT_H
#define QCODINGCHAINCOMPONENT_H

#include <QThread>
#include <QMutex>
#include <QFile>
#include <qabstractcodec.h>

/**********************************************************
QCodingChainComponent
**********************************************************/

class QCodingChainComponent : public QThread
{

	Q_OBJECT

	signals:

		void chunkAvailable();

	public slots:

		virtual bool initialize() = 0;
		virtual bool finalize() = 0;
		void addInputChunk(QAudioChunk chunk);
		void addOutputChunk(QAudioChunk chunk);

	public:

		QCodingChainComponent();
		bool hasInputChunk();
		bool hasOutputChunk();
		int numberOfInputChunks();
		int numberOfOutputChunks();
		QAudioChunk takeInputChunk();
		QAudioChunk takeOutputChunk();
		virtual void run() = 0;

	private:

		QMutex mMutex;
		QQueue<QAudioChunk> mInputChunks;
		QQueue<QAudioChunk> mOutputChunks;

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
