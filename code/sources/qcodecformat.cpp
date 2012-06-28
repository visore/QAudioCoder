#include <qcodecformat.h>

QCodecFormat::QCodecFormat()
	: QAudioFormat()
{
	mBitrateMode = QCodecFormat::ConstantBitrate;
	mNormalBitrate = 0;
	mMinimumBitrate = 0;
	mMaximumBitrate = 0;
	mQuality = QCodecFormat::Average;
}

QCodecFormat::BitrateMode QCodecFormat::bitrateMode()
{
	return mBitrateMode;
}

void QCodecFormat::setBitrateMode(QCodecFormat::BitrateMode mode)
{
	mBitrateMode = mode;
}

int QCodecFormat::bitrate(QCodecFormat::BitrateType type)
{
	if(mBitrateMode == QCodecFormat::ConstantBitrate || type == QCodecFormat::NormalBitrate)
	{
		return mNormalBitrate;
	}
	else if(type == QCodecFormat::MinimumBitrate)
	{
		return mMinimumBitrate;
	}
	else if(type == QCodecFormat::MaximumBitrate)
	{
		return mMaximumBitrate;
	}
	return -1;
}

void QCodecFormat::setBitrate(int rate, QCodecFormat::BitrateType type)
{
	if(mBitrateMode == QCodecFormat::ConstantBitrate || type == QCodecFormat::NormalBitrate)
	{
		mNormalBitrate = rate;
	}
	else if(type == QCodecFormat::MinimumBitrate)
	{
		mMinimumBitrate = rate;
	}
	else if(type == QCodecFormat::MaximumBitrate)
	{
		mMaximumBitrate = rate;
	}
}

QCodecFormat::Quality QCodecFormat::quality()
{
	return mQuality;
}

void QCodecFormat::setQuality(QCodecFormat::Quality quality)
{
	mQuality = quality;
}
