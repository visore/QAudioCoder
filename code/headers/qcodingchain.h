#ifndef QCODINGCHAIN_H
#define QCODINGCHAIN_H

#include <qcodingchaincomponent.h>
#include <qaudiomanager.h>

class QCodingChain : public QThread
{

	Q_OBJECT

	signals:

		void progressed(qreal percentage);

	public:

		QCodingChain();

		void setInputFilePath(QString filePath);
		void setOutputFilePath(QString filePath);
		void setOutputFormat(QExtendedAudioFormat format);

		void run();

	private:

		QString mInputFilePath;
		QString mOutputFilePath;
		QExtendedAudioFormat mOutputFormat;

		QAudioManager *mManager; //If not here, will automatically destruct coders

		QAbstractCoder *mInputCoder;
		QAbstractCoder *mOutputCoder;

		QCodingChainInput *mInput;
		QCodingChainOutput *mOutput;

		QCodingChainFileInput mFileInput;
		QCodingChainFileOutput mFileOutput;

		QCodingChainDecoder mDecoder;
		QCodingChainEncoder mEncoder;

};

#endif
