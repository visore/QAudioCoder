#ifndef QEXTENDEDAUDIOFORMAT_H
#define QEXTENDEDAUDIOFORMAT_H

#include <QAudioFormat>

class QExtendedAudioFormat : public QAudioFormat
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

		QExtendedAudioFormat();

		QExtendedAudioFormat::BitrateMode bitrateMode();
		void setBitrateMode(QExtendedAudioFormat::BitrateMode mode);

		int bitrate(QExtendedAudioFormat::BitrateType type = QExtendedAudioFormat::NormalBitrate);
		void setBitrate(int rate, QExtendedAudioFormat::BitrateType type = QExtendedAudioFormat::NormalBitrate);

		QExtendedAudioFormat::Quality quality();
		void setQuality(QExtendedAudioFormat::Quality quality);

	private:

		QExtendedAudioFormat::BitrateMode mBitrateMode;
		int mNormalBitrate;
		int mMinimumBitrate;
		int mMaximumBitrate;
		QExtendedAudioFormat::Quality mQuality;

};

#endif
