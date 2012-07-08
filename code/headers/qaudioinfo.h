#ifndef QAUDIOINFO_H
#define QAUDIOINFO_H

#include <QtGlobal>

class QAudioInfo
{

	public:

		QAudioInfo();

		qint32 headerSize() const;
		qint64 dataSize() const;
		qint32 trailerSize() const;
		qint64 size() const;
		qint64 samples() const;

		void setHeaderSize(qint32 value);
		void setDataSize(qint64 value);
		void setTrailerSize(qint32 value);
		void setSize(qint64 value);
		void setSamples(qint64 value);

	private:

		qint32 mHeaderSize;
		qint32 mTrailerSize;
		qint64 mSize;
		qint64 mDataSize;
		qint64 mSamples;

};

#endif
