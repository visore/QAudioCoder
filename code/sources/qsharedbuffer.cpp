#include <qsharedbuffer.h>
#include <qcodingchaincomponent.h>

#define ALMOST_EMPTY 5

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
	emit dataAdded();
}

QSampleArray* QSharedBuffer::dequeue()
{
	mMutex.lock();
	QSampleArray *result = mChunks.dequeue();
	if(mChunks.size() < ALMOST_EMPTY)
	{
		emit almostEmpty(mChunks.size());
	}
	mMutex.unlock();
	return result;
}

void QSharedBuffer::connect(QCodingChainComponent *sender, QCodingChainComponent *receiver)
{
	sender->setOutputBuffer(this);
	receiver->setInputBuffer(this);

	QObject::disconnect(this, SIGNAL(dataAdded()));
	QObject::disconnect(this, SIGNAL(almostEmpty(int)));

	QObject::connect(this, SIGNAL(dataAdded()), receiver, SLOT(dataAvailable()));
	QObject::connect(this, SIGNAL(almostEmpty(int)), sender, SLOT(addData(int)));
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
