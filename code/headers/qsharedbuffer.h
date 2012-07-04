#ifndef QSHAREDBUFFER_H
#define QSHAREDBUFFER_H

#include <QMutex>
#include <QQueue>
#include <qaudiochunk.h>

class QCodingChainComponent;

class QSharedBuffer : public QObject
{

	Q_OBJECT

	signals:

		void chunkAdded();
		void almostEmpty(int size);

	public slots:

		void enqueue(QAudioChunk *chunk);

	public:

		QSharedBuffer();
		~QSharedBuffer();
		void connect(QCodingChainComponent *sender, QCodingChainComponent *receiver);
		QAudioChunk* dequeue();
		bool isEmpty();
		int size();
		void clear();

	private:

		QMutex mMutex;
		QQueue<QAudioChunk*> mChunks;

};

#endif
