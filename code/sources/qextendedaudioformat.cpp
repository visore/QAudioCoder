#include <qextendedaudioformat.h>

QExtendedAudioFormat::QExtendedAudioFormat()
	: QAudioFormat()
{
	mSampleType = QExtendedAudioFormat::Unknown;
	mBitrateMode = QExtendedAudioFormat::ConstantBitrate;
	mNormalBitrate = 0;
	mMinimumBitrate = 0;
	mMaximumBitrate = 0;
	mQuality = QExtendedAudioFormat::Average;
}

QExtendedAudioFormat::SampleType QExtendedAudioFormat::sampleType()
{
	return mSampleType;
}

void QExtendedAudioFormat::setSampleType(QExtendedAudioFormat::SampleType type)
{
	mSampleType = type;
}

QExtendedAudioFormat::BitrateMode QExtendedAudioFormat::bitrateMode()
{
	return mBitrateMode;
}

void QExtendedAudioFormat::setBitrateMode(QExtendedAudioFormat::BitrateMode mode)
{
	mBitrateMode = mode;
}

int QExtendedAudioFormat::bitrate(QExtendedAudioFormat::BitrateType type)
{
	if(mBitrateMode == QExtendedAudioFormat::ConstantBitrate || type == QExtendedAudioFormat::NormalBitrate)
	{
		return mNormalBitrate;
	}
	else if(type == QExtendedAudioFormat::MinimumBitrate)
	{
		return mMinimumBitrate;
	}
	else if(type == QExtendedAudioFormat::MaximumBitrate)
	{
		return mMaximumBitrate;
	}
	return -1;
}

void QExtendedAudioFormat::setBitrate(int rate, QExtendedAudioFormat::BitrateType type)
{
	if(mBitrateMode == QExtendedAudioFormat::ConstantBitrate || type == QExtendedAudioFormat::NormalBitrate)
	{
		mNormalBitrate = rate;
	}
	else if(type == QExtendedAudioFormat::MinimumBitrate)
	{
		mMinimumBitrate = rate;
	}
	else if(type == QExtendedAudioFormat::MaximumBitrate)
	{
		mMaximumBitrate = rate;
	}
}

QExtendedAudioFormat::Quality QExtendedAudioFormat::quality()
{
	return mQuality;
}

void QExtendedAudioFormat::setQuality(QExtendedAudioFormat::Quality quality)
{
	mQuality = quality;
}
