#ifndef QCODINGCHAINCOMPONENT_H
#define QCODINGCHAINCOMPONENT_H

#include <QMutex>
#include <QThread>
#include <QFile>
#include <qabstractcoder.h>
#include <qsharedbuffer.h>

#include<iostream>
using namespace std;

/**********************************************************
QCodingChainComponent
**********************************************************/

class QCodingChainComponent : public QObject
{

	Q_OBJECT

	public slots:

		virtual void changeFormat(QExtendedAudioFormat format);
		void addData(QSampleArray *data);

	public:

		QCodingChainComponent();

		void setNext(QCodingChainComponent *next);
		int chunkSize();

		virtual void initialize() = 0;
		virtual void execute() = 0;
		virtual void finalize() = 0;

	protected:

		QQueue<QSampleArray*> mData;
		QCodingChainComponent *mNext;

};

/**********************************************************
QCodingChainInput
**********************************************************/

class QCodingChainInput : public QCodingChainComponent
{

	Q_OBJECT

	public:

		QCodingChainInput();
		virtual bool hasData() = 0;
		virtual int size() = 0;

};

/**********************************************************
QCodingChainFileInput
**********************************************************/

class QCodingChainFileInput : public QCodingChainInput
{

	Q_OBJECT

	public:

		QCodingChainFileInput();
		void setFilePath(QString filePath);
		bool hasData();
		int size();
		void initialize();
		void execute();
		void finalize();

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
		virtual void setCoder(QAbstractCoder *coder);

	protected:

		QAbstractCoder *mCoder;

};

/**********************************************************
QCodingChainDecoder
**********************************************************/

class QCodingChainDecoder : public QCodingChainCoder
{

	Q_OBJECT

	public:

		QCodingChainDecoder();
		void setCoder(QAbstractCoder *coder);
		void initialize();
		void execute();
		void finalize();

};

/**********************************************************
QCodingChainEncoder
**********************************************************/

class QCodingChainEncoder : public QCodingChainCoder
{

	Q_OBJECT

	public slots:

		void changeFormat(QExtendedAudioFormat format);

	public:

		QCodingChainEncoder();
		void initialize();
		void execute();
		void finalize();

};

/**********************************************************
QCodingChainOutput
**********************************************************/

class QCodingChainOutput : public QCodingChainComponent
{

	Q_OBJECT

	public:

		QCodingChainOutput();
		void setHeader(QByteArray data);

	protected:

		QByteArray mHeader;

};

/**********************************************************
QCodingChainFileOutput
**********************************************************/

class QCodingChainFileOutput : public QCodingChainOutput
{

	Q_OBJECT

	public:

		QCodingChainFileOutput();
		void setFilePath(QString filePath);
		void initialize();
		void execute();
		void finalize();

	protected:

		QString mFilePath;
		QFile mFile;

};

#endif
