#ifndef QCODECEXECUTOR_H
#define QCODECEXECUTOR_H

#include <QThread>
#include <qabstractcodec.h>

class QCodecExecutor : public QThread
{

	public:

		enum Error
		{
			NoError = 0,
			InputFileError = 1,
			OutputFileError = 2
		};

		QCodecExecutor();

		void setCodec(QAbstractCodec *codec);
		void setFormat(QCodecFormat format);

		QCodecFormat format();
		QCodecExecutor::Error error();

		virtual void run() = 0;

	protected:

		void setError(QCodecExecutor::Error error);

	protected:

		int (QCodecExecutor::*encode)(const char[], int);

		QCodecExecutor::Error mError;
		QAbstractCodec *mCodec;
		QCodecFormat mFormat;

};

/**********************************************************

File Executor

**********************************************************/

class QCodecFileExecutor : public QCodecExecutor
{

	public:

		QCodecFileExecutor();

		void setFilePath(QString filePath);
		QString filePath();
		
		virtual void run() = 0;

	protected:

		QString mFilePath;

};

class QFileEncoder : public QCodecFileExecutor
{

	public:

		void run();

	protected:

		void encode8(char *data, int size);
		void encode16(char *data, int size);
		void encode32(char *data, int size);

};

class QFileDecoder : public QCodecFileExecutor
{

	public:

		void run();

};

/**********************************************************

Buffer Executor

**********************************************************/

class QCodecBufferExecutor : public QCodecExecutor
{

};

class QBufferEncoder : public QCodecBufferExecutor
{

};

class QBufferDecoder : public QCodecBufferExecutor
{

};

#endif
