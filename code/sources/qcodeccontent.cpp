#include <qcodeccontent.h>

QCodecContent::QCodecContent()
{
	mHeaderSize = 0;
	mTrailerSize = 0;
	mFileSize = 0;
	mDataSize = 0;
	mSamples = 0;
}

qint32 QCodecContent::headerSize() const
{
	return mHeaderSize;
}

qint32 QCodecContent::trailerSize() const
{
	return mTrailerSize;
}

qint64 QCodecContent::fileSize() const
{
	return mFileSize;
}

qint64 QCodecContent::dataSize() const
{
	return mDataSize;
}

qint64 QCodecContent::samples() const
{
	return mSamples;
}

void QCodecContent::setHeaderSize(qint32 value)
{
	mHeaderSize = value;
}

void QCodecContent::setTrailerSize(qint32 value)
{
	mTrailerSize = value;
}

void QCodecContent::setFileSize(qint64 value)
{
	mFileSize = value;
}

void QCodecContent::setDataSize(qint64 value)
{
	mDataSize = value;
}

void QCodecContent::setSamples(qint64 value)
{
	mSamples = value;
}
