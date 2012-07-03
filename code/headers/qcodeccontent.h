#ifndef QCODECCONTENT_H
#define QCODECCONTENT_H

#include <QtGlobal>

class QCodecContent
{

	public:

		QCodecContent();

		qint32 headerSize() const;
		qint32 trailerSize() const;
		qint64 fileSize() const;
		qint64 dataSize() const;
		qint64 samples() const;

		void setHeaderSize(qint32 value);
		void setTrailerSize(qint32 value);
		void setFileSize(qint64 value);
		void setDataSize(qint64 value);
		void setSamples(qint64 value);

	private:

		qint32 mHeaderSize;
		qint32 mTrailerSize;
		qint64 mFileSize;
		qint64 mDataSize;
		qint64 mSamples;

};

#endif
