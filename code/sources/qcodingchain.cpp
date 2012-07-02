#include <qcodingchain.h>

QCodingChain::QCodingChain()
	: QObject()
{
	mInput = NULL;
	mOutput = NULL;
}

void QCodingChain::setInputFilePath(QString filePath)
{
	mFileInput.setFilePath(filePath);
	mInput = mFileInput;
}

void QCodingChain::setOutputFilePath(QString filePath)
{
	mFileOutput.setFilePath(filePath);
	mOutput = mFileOutput;
}

void QCodingChain::execute()
{
	if(mInput != NULL && mOutput != NULL)
	{
		QObject::connect(mInput, SIGNAL(), &mDecoder, SLOT());
	}
}
