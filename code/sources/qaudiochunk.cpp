#include <qaudiochunk.h>

QAudioChunk::QAudioChunk()
{
	mData = 0;
	mSamples = 0;
	mBytes = 0;
}

QAudioChunk::QAudioChunk(qbyte *data, int samples, int bytes)
{
	mData = data;
	mSamples = samples;
	mBytes = bytes;
}

QAudioChunk::~QAudioChunk()
{
	if(mData != 0)
	{
		delete mData;
		mData = 0;
	}
}

QAudioChunk QAudioChunk::create(int samples, int bytes)
{
	return QAudioChunk(new qbyte[bytes], samples, bytes);
}

qbyte* QAudioChunk::data()
{
	return mData;
}

int QAudioChunk::samples()
{
	return mSamples;
}

int QAudioChunk::bytes()
{
	return mBytes;
}

void QAudioChunk::setData(qbyte *data, int samples, int bytes)
{
	mData = data;
	mSamples = samples;
	mBytes = bytes;
}

void QAudioChunk::setData(qbyte *data)
{
	mData = data;
}

void QAudioChunk::setSamples(int samples)
{
	mSamples = samples;
}

void QAudioChunk::setBytes(int bytes)
{
	mBytes = bytes;
}
