#include <qsamplearray.h>

QSampleArray::QSampleArray()
{
	mSamples = 0;
	mSize = 0;
	mData = NULL;
}

QSampleArray::QSampleArray(const QSampleArray &other)
{
	mSamples = other.mSamples;
	mSize = other.mSize;
	memcpy(mData, other.mData, mSize);
}

QSampleArray::QSampleArray(char *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qbyte8u *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qbyte16u *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qbyte32u *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qbyte8s *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qbyte16s *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qbyte32s *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qfloat *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::QSampleArray(qreal *data, int size, int samples)
{
	mData = NULL;
	setData(data, size, samples);
}

QSampleArray::~QSampleArray()
{
	clearData();
}

void QSampleArray::setData(char *data, int size)
{
	clearData();
	mData = data;
	mSize = size;
}

void QSampleArray::setData(qbyte8u *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte8u);
}

void QSampleArray::setData(qbyte16u *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte16u);
}

void QSampleArray::setData(qbyte32u *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte32u);
}

void QSampleArray::setData(qbyte8s *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte8s);
}

void QSampleArray::setData(qbyte16s *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte16s);
}

void QSampleArray::setData(qbyte32s *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte32s);
}

void QSampleArray::setData(qfloat *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qfloat);
}

void QSampleArray::setData(qreal *data, int size)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qreal);
}

void QSampleArray::setData(char *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size;
	mSamples = samples;
}

void QSampleArray::setData(qbyte8u *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte8u);
	mSamples = samples;
}

void QSampleArray::setData(qbyte16u *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte16u);
	mSamples = samples;
}

void QSampleArray::setData(qbyte32u *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte32u);
	mSamples = samples;
}

void QSampleArray::setData(qbyte8s *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte8s);
	mSamples = samples;
}

void QSampleArray::setData(qbyte16s *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte16s);
	mSamples = samples;
}

void QSampleArray::setData(qbyte32s *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qbyte32s);
	mSamples = samples;
}

void QSampleArray::setData(qfloat *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qfloat);
	mSamples = samples;
}

void QSampleArray::setData(qreal *data, int size, int samples)
{
	clearData();
	mData = data;
	mSize = size * sizeof(qreal);
	mSamples = samples;
}

int QSampleArray::samples()
{
	return mSamples;
}

void QSampleArray::setSamples(int samples)
{
	mSamples = samples;
}

int QSampleArray::size()
{
	return mSize;
}

void* QSampleArray::data()
{
	return mData;
}

char* QSampleArray::charData()
{
	return (char*) mData;
}

void QSampleArray::clear()
{
	mSize = 0;
	mSamples = 0;
	clearData();
}

void QSampleArray::clearData()
{
	if(mData != NULL)
	{
		delete [] (char*) mData;
		mData = NULL;
	}
}
