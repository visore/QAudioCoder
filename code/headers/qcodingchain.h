#ifndef QCODINGCHAIN_H
#define QCODINGCHAIN_H

#include <qcodingchaincomponent.h>

class QCodingChain : public QThread
{

	Q_OBJECT

	signals:

		void finished();

	private slots:

		void inputFinished();
		void checkFinished();

	public:

		QCodingChain();

		void setInputFilePath(QString filePath);
		void setOutputFilePath(QString filePath);
		void setOutputFormat(QExtendedFormat format);

		void run();

	private:

		QString mInputFilePath;
		QString mOutputFilePath;
		QExtendedFormat mOutputFormat

		QAbstractCoder *mInputCoder;
		QAbstractCoder *mOutputCoder;

		QCodingChainInput *mInput;
		QCodingChainOutput *mOutput;

		QCodingChainFileInput mFileInput;
		QCodingChainFileOutput mFileOutput;

		QCodingChainDecoder mDecoder;
		QCodingChainEncoder mEncoder;

		QSharedBuffer mBuffer1;
		QSharedBuffer mBuffer2;
		QSharedBuffer mBuffer3;

		bool mInputAtEnd;
		bool mIsFinished;

};

#endif
