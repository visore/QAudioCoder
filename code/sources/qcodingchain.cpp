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
	mInput = &mFileInput;
}

void QCodingChain::setOutputFilePath(QString filePath)
{
	mFileOutput.setFilePath(filePath);
	mOutput = &mFileOutput;
}

void QCodingChain::execute()
{
	if(mInput != NULL && mOutput != NULL)
	{
		QObject::connect(mInput, SIGNAL(available(QAudioChunk)), &mDecoder, SLOT(addChunk(QAudioChunk)));
		QObject::connect(&mDecoder, SIGNAL(available(QAudioChunk)), &mEncoder, SLOT(addChunk(QAudioChunk)));
		QObject::connect(&mEncoder, SIGNAL(available(QAudioChunk)), mOutput, SLOT(addChunk(QAudioChunk)));
	}
}
