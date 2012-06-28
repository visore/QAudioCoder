#ifndef QCODECFORMAT_H
#define QCODECFORMAT_H

#include <QAudioFormat>

class QCodecFormat : public QAudioFormat
{

	public:

		enum BitrateMode
		{
			ConstantBitrate = 0,
			VariableBitrate = 1,
			AverageBitrate = 2
		};

		enum BitrateType
		{
			NormalBitrate = 0,
			MinimumBitrate = 1,
			MaximumBitrate = 2
		};

		enum Quality
		{
			InsaneHigh = 0,
			ExtremeHigh = 1,
			VeryHigh = 2,
			High = 3,
			AboveAverage = 4,
			Average = 5,
			BelowAverage = 6,
			Low = 7,
			VeryLow = 8,
			ExtremeLow = 9
		};

		QCodecFormat();

		QCodecFormat::BitrateMode bitrateMode();
		void setBitrateMode(QCodecFormat::BitrateMode mode);

		int bitrate(QCodecFormat::BitrateType type = QCodecFormat::NormalBitrate);
		void setBitrate(int rate, QCodecFormat::BitrateType type = QCodecFormat::NormalBitrate);

		QCodecFormat::Quality quality();
		void setQuality(QCodecFormat::Quality quality);

	private:

		QCodecFormat::BitrateMode mBitrateMode;
		int mNormalBitrate;
		int mMinimumBitrate;
		int mMaximumBitrate;
		QCodecFormat::Quality mQuality;

};

#endif
