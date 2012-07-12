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

		enum Mode
		{
			Unknown = 0,
			ConvertFileToFile = 1,
			ConvertFileToData = 2,
			ConvertDataToData = 3,
			ConvertDataToFile = 4,
			DecodeFile = 5,
			DecodeData = 6,
			EncodeFile = 7,
			EncodeData = 8
		};

		QCodingChain();

		void setMode(QCodingChain::Mode mode);

		void setInput(QString filePath);
		void setOutput(QString filePath);

		void setInput(QByteArray &array);
		void setOutput(QByteArray &array);

		void setInput(QExtendedAudioFormat &format);
		void setOutput(QExtendedAudioFormat &format);

		void run();

	protected:

		void reset();

		void detectCoderData();
		void detectCoderFile();

	private:

		void (QCodingChain::*detectCoder)();

		QCodingChain::Mode mMode;

		QString mInputFilePath;
		QByteArray *mInputData;

		QExtendedAudioFormat *mInputFormat;
		QExtendedAudioFormat *mOutputFormat;

		QAudioManager *mManager; //If not here, will automatically destruct coders

		QAbstractCoder *mInputCoder;
		QAbstractCoder *mOutputCoder;

		QCodingChainInput *mInput;
		QCodingChainOutput *mOutput;

		QCodingChainFileInput mFileInput;
		QCodingChainFileOutput mFileOutput;

		QCodingChainDataInput mDataInput;
		QCodingChainDataOutput mDataOutput;

		QCodingChainDecoder mDecoder;
		QCodingChainEncoder mEncoder;

};

#endif
