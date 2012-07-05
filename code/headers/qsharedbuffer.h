#ifndef QSHAREDBUFFER_H
#define QSHAREDBUFFER_H

#include <QMutex>
#include <QQueue>
#include <qsamplearray.h>

#include <iostream>
using namespace std;

class QCodingChainComponent;

class QSharedBuffer : public QObject
{

	Q_OBJECT

	signals:

		void dataAdded();
		void almostEmpty(int size);

	public slots:

		void enqueue(QSampleArray *array);

	public:

		QSharedBuffer();
		~QSharedBuffer();
		void connect(QCodingChainComponent *sender, QCodingChainComponent *receiver);
		QSampleArray* dequeue();
		bool isEmpty();
		int size();
		void clear();

	private:

		QMutex mMutex;
		QQueue<QSampleArray*> mChunks;

};

#endif
