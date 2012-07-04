#include <qsamplearray.h>

QSampleArray::QSampleArray()
	: QByteArray()
{
	mSamples = 0;
}

QSampleArray::QSampleArray(const QSampleArray &other)
	: QByteArray(other)
{
	mSamples = other.mSamples;
}

QSampleArray::QSampleArray(const QByteArray &other)
	: QByteArray(other)
{
	mSamples = 0;
}

QSampleArray::QSampleArray(const QByteArray &other, int samples)
	: QByteArray(other)
{
	mSamples = samples;
}

QSampleArray::QSampleArray(char *data, int size, int samples)
	: QByteArray(data, size)
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qbyte8u *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qbyte8u))
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qbyte16u *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qbyte16u))
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qbyte32u *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qbyte32u))
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qbyte8s *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qbyte8s))
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qbyte16s *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qbyte16s))
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qbyte32s *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qbyte32s))
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qfloat *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qfloat))
{
	mSamples = samples;
}

QSampleArray::QSampleArray(qreal *data, int size, int samples)
	: QByteArray((char*) data, size * sizeof(qreal))
{
	mSamples = samples;
}

void QSampleArray::setData(char *data, int size, int samples)
{
	clear();
	setRawData(data, size);
	mSamples = samples;
}

void QSampleArray::setData(qbyte8u *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qbyte8u));
	mSamples = samples;
}

void QSampleArray::setData(qbyte16u *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qbyte16u));
	mSamples = samples;
}

void QSampleArray::setData(qbyte32u *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qbyte32u));
	mSamples = samples;
}

void QSampleArray::setData(qbyte8s *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qbyte8s));
	mSamples = samples;
}

void QSampleArray::setData(qbyte16s *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qbyte16s));
	mSamples = samples;
}

void QSampleArray::setData(qbyte32s *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qbyte32s));
	mSamples = samples;
}

void QSampleArray::setData(qfloat *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qfloat));
	mSamples = samples;
}

void QSampleArray::setData(qreal *data, int size, int samples)
{
	clear();
	setRawData((char*) data, size * sizeof(qreal));
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
