#ifndef QCODINGCHAINCOMPONENT_H
#define QCODINGCHAINCOMPONENT_H

#include <QMutex>
#include <QThread>
#include <QFile>
#include <qabstractcoder.h>

#include<iostream>
using namespace std;

/**********************************************************
QCodingChainComponent
**********************************************************/

class QCodingChainFileInput;
class QCodingChainDataInput;
class QCodingChainDecoder;
class QCodingChainEncoder;
class QCodingChainFileOutput;
class QCodingChainDataOutput;

class QCodingChainComponent : public QObject
{

	Q_OBJECT

	friend class QCodingChainFileInput;
	friend class QCodingChainDataInput;
	friend class QCodingChainDecoder;
	friend class QCodingChainEncoder;
	friend class QCodingChainFileOutput;
	friend class QCodingChainDataOutput;

	protected slots:

		virtual void changeFormat(QExtendedAudioFormat format);
		void addData(QSampleArray *data);
		void addData(QSampleArray *data, qint64 position);

	public:

		QCodingChainComponent();

		void setNext(QCodingChainComponent *next);
		int chunkSize();

		virtual void initialize() = 0;
		virtual void execute() = 0;
		virtual void finalize() = 0;

	protected:

		virtual void seek(qint64 position);

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
QCodingChainDataInput
**********************************************************/

class QCodingChainDataInput : public QCodingChainInput
{

	Q_OBJECT

	public:

		QCodingChainDataInput();
		~QCodingChainDataInput();
		void setData(QByteArray &data);
		bool hasData();
		int size();
		void initialize();
		void execute();
		void finalize();

	protected:

		QByteArray *mByteArray;
		QDataStream *mStream;

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
		void seek(qint64 position);
		void initialize();
		void execute();
		void finalize();

	protected:

		QString mFilePath;
		QFile mFile;

};

/**********************************************************
QCodingChainDataOutput
**********************************************************/

class QCodingChainDataOutput : public QCodingChainOutput
{

	Q_OBJECT

	public:

		QCodingChainDataOutput();
		~QCodingChainDataOutput();
		void setData(QByteArray &data);
		void seek(qint64 position);
		void initialize();
		void execute();
		void finalize();

	protected:

		QByteArray *mByteArray;
		QDataStream *mStream;

};

#endif
