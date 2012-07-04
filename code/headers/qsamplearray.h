#ifndef QSAMPLEARRAY_H
#define QSAMPLEARRAY_H

#include <qcommon.h>
#include <QByteArray>

class QSampleArray : public QByteArray
{

	public:

		QSampleArray();
		QSampleArray(const QSampleArray &other);
		QSampleArray(const QByteArray &other);
		QSampleArray(const QByteArray &other, int samples);
		QSampleArray(char *data, int size, int samples = 0);
		QSampleArray(qbyte8u *data, int size, int samples = 0);
		QSampleArray(qbyte16u *data, int size, int samples = 0);
		QSampleArray(qbyte32u *data, int size, int samples = 0);
		QSampleArray(qbyte8s *data, int size, int samples = 0);
		QSampleArray(qbyte16s *data, int size, int samples = 0);
		QSampleArray(qbyte32s *data, int size, int samples = 0);
		QSampleArray(qfloat *data, int size, int samples = 0);
		QSampleArray(qreal *data, int size, int samples = 0);

		void setData(char *data, int size, int samples = 0);
		void setData(qbyte8u *data, int size, int samples = 0);
		void setData(qbyte16u *data, int size, int samples = 0);
		void setData(qbyte32u *data, int size, int samples = 0);
		void setData(qbyte8s *data, int size, int samples = 0);
		void setData(qbyte16s *data, int size, int samples = 0);
		void setData(qbyte32s *data, int size, int samples = 0);
		void setData(qfloat *data, int size, int samples = 0);
		void setData(qreal *data, int size, int samples = 0);

		int samples();
		void setSamples(int samples);

	private:

		int mSamples;

};

#endif
