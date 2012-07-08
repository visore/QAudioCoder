#include <qaudioinfo.h>

QAudioInfo::QAudioInfo()
{
	mHeaderSize = 0;
	mDataSize = 0;
	mTrailerSize = 0;
	mSize = 0;
	mSamples = 0;
}

qint32 QAudioInfo::headerSize() const
{
	return mHeaderSize;
}

qint64 QAudioInfo::dataSize() const
{
	return mDataSize;
}

qint32 QAudioInfo::trailerSize() const
{
	return mTrailerSize;
}

qint64 QAudioInfo::size() const
{
	return mSize;
}

qint64 QAudioInfo::samples() const
{
	return mSamples;
}

void QAudioInfo::setHeaderSize(qint32 value)
{
	mHeaderSize = value;
}

void QAudioInfo::setDataSize(qint64 value)
{
	mDataSize = value;
}

void QAudioInfo::setTrailerSize(qint32 value)
{
	mTrailerSize = value;
}

void QAudioInfo::setSize(qint64 value)
{
	mSize = value;
}

void QAudioInfo::setSamples(qint64 value)
{
	mSamples = value;
}
