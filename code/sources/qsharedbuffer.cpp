#include <qsharedbuffer.h>
#include <qcodingchaincomponent.h>

QSharedBuffer::QSharedBuffer()
	: QObject()
{
}

QSharedBuffer::~QSharedBuffer()
{
	clear();
}

void QSharedBuffer::enqueue(QSampleArray *array)
{
	mMutex.lock();
	mChunks.enqueue(array);
	mMutex.unlock();
}

QSampleArray* QSharedBuffer::dequeue()
{
	mMutex.lock();
	QSampleArray *result = mChunks.dequeue();
	mMutex.unlock();
	return result;
}

QSampleArray* QSharedBuffer::dequeue(int &size)
{
	mMutex.lock();
	QSampleArray *result = mChunks.dequeue();
	size = mChunks.size();
	mMutex.unlock();
	return result;
}

bool QSharedBuffer::isEmpty()
{
	mMutex.lock();
	bool result = mChunks.isEmpty();
	mMutex.unlock();
	return result;
}

int QSharedBuffer::size()
{
	mMutex.lock();
	int result = mChunks.size();
	mMutex.unlock();
	return result;
}

void QSharedBuffer::clear()
{
	mMutex.lock();
	qDeleteAll(mChunks);
	mChunks.clear();
	mMutex.unlock();
}
