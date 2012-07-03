#ifndef QCODINGCHAIN_H
#define QCODINGCHAIN_H

#include <qcodingchaincomponent.h>
#include <qcodecmanager.h>

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

		bool isFinished();

		void setInputFilePath(QString filePath);
		void setOutputFilePath(QString filePath);

		void run();

	private:

		QCodecManager mCodecManager;

		QCodingChainInput *mInput;
		QCodingChainOutput *mOutput;

		QCodingChainFileInput mFileInput;
		QCodingChainFileOutput mFileOutput;

		QCodingChainDecoder mDecoder;
		QCodingChainEncoder mEncoder;

		bool mInputAtEnd;

};

#endif
