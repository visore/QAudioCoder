#ifndef QCODINGCHAIN_H
#define QCODINGCHAIN_H

#include <qcodingchaincomponents.h>

class QCodingChain : public QObject
{

	Q_OBJECT

	public:

		QCodingChain();

		void setInputFilePath(QString filePath);
		void setOutputFilePath(QString filePath);

		void execute();

	private:

		QCodingChainInput *mInput;
		QCodingChainOutput *mOutput;

		QCodingChainFileInput mFileInput;
		QCodingChainFileOutput mFileOutput;

		QCodingChainDecoder mDecoder;
		QCodingChainEncoder mEncoder;

};

#endif
