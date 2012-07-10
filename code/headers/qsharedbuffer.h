#ifndef QSHAREDBUFFER_H
#define QSHAREDBUFFER_H

#include <QMutex>
#include <QQueue>
#include <qsamplearray.h>

class QSharedBuffer : public QObject
{

	Q_OBJECT

	public slots:

		void enqueue(QSampleArray *array);

	public:

		QSharedBuffer();
		~QSharedBuffer();
		QSampleArray* dequeue();
		QSampleArray* dequeue(int &size);
		bool isEmpty();
		int size();
		void clear();

	private:

		QMutex mMutex;
		QQueue<QSampleArray*> mChunks;

};

#endif
