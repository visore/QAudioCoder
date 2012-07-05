#ifndef QSAMPLEARRAY_H
#define QSAMPLEARRAY_H

#include <qcommon.h>

class QSampleArray
{

	public:

		QSampleArray();
		QSampleArray(const QSampleArray &other);
		QSampleArray(char *data, int size, int samples = 0);
		QSampleArray(qbyte8u *data, int size, int samples = 0);
		QSampleArray(qbyte16u *data, int size, int samples = 0);
		QSampleArray(qbyte32u *data, int size, int samples = 0);
		QSampleArray(qbyte8s *data, int size, int samples = 0);
		QSampleArray(qbyte16s *data, int size, int samples = 0);
		QSampleArray(qbyte32s *data, int size, int samples = 0);
		QSampleArray(qfloat *data, int size, int samples = 0);
		QSampleArray(qreal *data, int size, int samples = 0);
		~QSampleArray();

		void setData(char *data, int size);
		void setData(qbyte8u *data, int size);
		void setData(qbyte16u *data, int size);
		void setData(qbyte32u *data, int size);
		void setData(qbyte8s *data, int size);
		void setData(qbyte16s *data, int size);
		void setData(qbyte32s *data, int size);
		void setData(qfloat *data, int size);
		void setData(qreal *data, int size);

		void setData(char *data, int size, int samples);
		void setData(qbyte8u *data, int size, int samples);
		void setData(qbyte16u *data, int size, int samples);
		void setData(qbyte32u *data, int size, int samples);
		void setData(qbyte8s *data, int size, int samples);
		void setData(qbyte16s *data, int size, int samples);
		void setData(qbyte32s *data, int size, int samples);
		void setData(qfloat *data, int size, int samples);
		void setData(qreal *data, int size, int samples);

		int samples();
		void setSamples(int samples);

		int size();
		void* data();
		char* charData();

		void clear();
		void clearData();

	private:

		int mSamples;
		int mSize;
		void *mData;

};

#endif
