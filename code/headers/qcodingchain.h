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
		~QCodingChain();

		void setMode(QCodingChain::Mode mode);

		void setInputPath(QString filePath);
		void setOutputPath(QString filePath);

		void setInputData(QByteArray &array);
		void setOutputData(QByteArray &array);

		void setInputFormat(QExtendedAudioFormat *format);
		void setInputFormat(QExtendedAudioFormat &format);
		void setOutputFormat(QExtendedAudioFormat &format);

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
		bool mReferenceInputFormat;

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
