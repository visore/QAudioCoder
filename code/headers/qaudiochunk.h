#ifndef QAUDIOHUNK_H
#define QAUDIOHUNK_H

#include <qsampleconverter.h>

class QAudioChunk
{

	public:

		QAudioChunk();
		QAudioChunk(qbyte *data, int samples, int bytes);
		~QAudioChunk();

		static QAudioChunk create(int samples, int bytes);

		qbyte* data();
		int samples();
		int bytes();

		void setData(qbyte *data, int samples, int bytes);
		void setData(qbyte *data);
		void setSamples(int samples);
		void setBytes(int bytes);

	private:

		qbyte *mData;
		int mSamples;
		int mBytes;

};

#endif
