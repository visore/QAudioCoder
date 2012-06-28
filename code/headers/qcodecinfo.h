#ifndef QCODECINFO_H
#define QCODECINFO_H

#include <QStringList>

class QCodecInfo
{

	public:

		enum Compression
		{
			Undefined = 0,
			Lossy = 1,
			Lossless = 2,
			Variable = 3
		};

		QCodecInfo();

		QCodecInfo::Compression compression();
		QString abbreviation();
		QString name();
		QStringList extensions();
		QStringList starExtensions();

		bool operator == (const QCodecInfo &other) const;

	protected:

		QCodecInfo::Compression mCompression;
		QString mAbbreviation;
		QString mName;
		QStringList mExtensions;

};

typedef QList<QCodecInfo> QCodecInfoList;

#endif
