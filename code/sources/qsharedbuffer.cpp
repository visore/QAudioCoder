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

void QSharedBuffer::enqueue(QAudioChunk *chunk)
{
	mMutex.lock();
char *f = new char[chunk->bytes()];
memcpy(f, chunk->data(), chunk->bytes());
	mChunks.enqueue(f, chunk->samples(), chunk->bytes());
	mMutex.unlock();
	emit chunkAdded();
}

QAudioChunk* QSharedBuffer::dequeue()
{
mMutex.lock();
	QAudioChunk *result = mChunks.dequeue();
delete result;
	//delete(result->data(), 8192);
	mMutex.unlock();

	/*mMutex.lock();
	QAudioChunk *result = mChunks.dequeue();
	if(mChunks.size() < ALMOST_EMPTY)
	{
		emit almostEmpty(mChunks.size());
	}
	mMutex.unlock();
	return result;*/
}

void QSharedBuffer::connect(QCodingChainComponent *sender, QCodingChainComponent *receiver)
{
	sender->setOutputBuffer(this);
	receiver->setInputBuffer(this);

	QObject::disconnect(this, SIGNAL(chunkAdded()));
	QObject::disconnect(this, SIGNAL(almostEmpty(int)));

	QObject::connect(this, SIGNAL(chunkAdded()), receiver, SLOT(chunkAvailable()));
	QObject::connect(this, SIGNAL(almostEmpty(int)), sender, SLOT(addChunks(int)));
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
