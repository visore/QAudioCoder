#include <qextendedaudioformat.h>
#include <qaudiomanager.h>

QExtendedAudioFormat::QExtendedAudioFormat()
{
	mSampleType = QExtendedAudioFormat::Unknown;
	mByteOrder = QExtendedAudioFormat::LittleEndian;
	mQuality = QExtendedAudioFormat::Average;
	mBitrateMode = QExtendedAudioFormat::ConstantBitrate;
	mNormalBitrate = 256;
	mMinimumBitrate = 256;
	mMaximumBitrate = 256;
	mSampleSize = 16;
	mSampleRate = 44100;
	mChannelCount = 2;
	mCodec = NULL;
}

QExtendedAudioFormat::QExtendedAudioFormat(const QExtendedAudioFormat &other)
{
	mSampleType = other.mSampleType;
	mByteOrder = other.mByteOrder;
	mQuality = other.mQuality;
	mBitrateMode = other.mBitrateMode;
	mNormalBitrate = other.mNormalBitrate;
	mMinimumBitrate = other.mMinimumBitrate;
	mMaximumBitrate = other.mMaximumBitrate;
	mSampleSize = other.mSampleSize;
	mSampleRate = other.mSampleRate;
	mChannelCount = other.mChannelCount;
	mCodec = other.mCodec;
}

QExtendedAudioFormat::QExtendedAudioFormat(const QAudioFormat &other)
{
	setSampleSize(other.sampleType());
	setByteOrder(other.byteOrder());
	mQuality = QExtendedAudioFormat::Average;
	mBitrateMode = QExtendedAudioFormat::ConstantBitrate;
	mNormalBitrate = 256;
	mMinimumBitrate = 256;
	mMaximumBitrate = 256;
	mSampleSize = other.sampleSize();
	mSampleRate = other.sampleRate();
	mChannelCount = other.channelCount();
	mCodec = NULL;
}

QExtendedAudioFormat::SampleType QExtendedAudioFormat::sampleType() const
{
	return mSampleType;
}

QExtendedAudioFormat::Endian QExtendedAudioFormat::byteOrder() const
{
	return mByteOrder;
}

QExtendedAudioFormat::Quality QExtendedAudioFormat::quality() const
{
	return mQuality;
}

QExtendedAudioFormat::BitrateMode QExtendedAudioFormat::bitrateMode() const
{
	return mBitrateMode;
}

int QExtendedAudioFormat::bitrate(const QExtendedAudioFormat::BitrateType type) const
{
	if(type == QExtendedAudioFormat::MinimumBitrate)
	{
		return mMinimumBitrate;
	}
	else if(type == QExtendedAudioFormat::MaximumBitrate)
	{
		return mMaximumBitrate;
	}
	else
	{
		return mNormalBitrate;
	}
}

int QExtendedAudioFormat::sampleSize() const
{
	return mSampleSize;
}

int QExtendedAudioFormat::sampleRate() const
{
	return mSampleRate;
}

int QExtendedAudioFormat::channelCount() const
{
	return mChannelCount;
}

int QExtendedAudioFormat::channels() const
{
	return mChannelCount;
}

QAudioCodec* QExtendedAudioFormat::codec() const
{
	return mCodec;
}
		
void QExtendedAudioFormat::setSampleType(const QExtendedAudioFormat::SampleType type)
{
	mSampleType = type;
}

void QExtendedAudioFormat::setSampleType(const QAudioFormat::SampleType type)
{
	if(type == QAudioFormat::SignedInt)
	{
		mSampleType = QExtendedAudioFormat::SignedInt;
	}
	else if(type == QAudioFormat::UnSignedInt)
	{
		mSampleType = QExtendedAudioFormat::UnSignedInt;
	}
	else if(type == QAudioFormat::Float)
	{
		mSampleType = QExtendedAudioFormat::Float;
	}
	else
	{
		mSampleType = QExtendedAudioFormat::Unknown;
	}
}

void QExtendedAudioFormat::setByteOrder(const QExtendedAudioFormat::Endian order)
{
	mByteOrder = order;
}

void QExtendedAudioFormat::setByteOrder(const QAudioFormat::Endian order)
{
	if(order == QAudioFormat::BigEndian)
	{
		mByteOrder = QExtendedAudioFormat::BigEndian;
	}
	else
	{
		mByteOrder = QExtendedAudioFormat::LittleEndian;
	}
}

void QExtendedAudioFormat::setQuality(const QExtendedAudioFormat::Quality quality)
{
	mQuality = quality;
}

void QExtendedAudioFormat::setBitrateMode(const QExtendedAudioFormat::BitrateMode mode)
{
	mBitrateMode = mode;
}

void QExtendedAudioFormat::setBitrate(const int rate, const QExtendedAudioFormat::BitrateType type)
{
	if(type == QExtendedAudioFormat::MinimumBitrate)
	{
		mMinimumBitrate = rate;
	}
	else if(type == QExtendedAudioFormat::MaximumBitrate)
	{
		mMaximumBitrate = rate;
	}
	else
	{
		mNormalBitrate = rate;
	}
}

void QExtendedAudioFormat::setSampleSize(const int size)
{
	mSampleSize = size;
}

void QExtendedAudioFormat::setSampleRate(const int rate)
{
	mSampleRate = rate;
}

void QExtendedAudioFormat::setChannelCount(const int channels)
{
	mChannelCount = channels;
}

void QExtendedAudioFormat::setChannels(const int channels)
{
	mChannelCount = channels;
}

void QExtendedAudioFormat::setCodec(QAudioCodec *codec)
{
	mCodec = codec;
}

bool QExtendedAudioFormat::setCodec(QString codecName)
{
	mCodec = QAudioManager::instance().codec(codecName, QAudioManager::Supported);
	return mCodec != NULL;
}
