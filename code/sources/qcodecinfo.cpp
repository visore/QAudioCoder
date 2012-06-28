#include <qcodecinfo.h>

QCodecInfo::QCodecInfo()
{
	mCompression = QCodecInfo::Undefined;
	mAbbreviation = "";
	mName = "";
}

QCodecInfo::Compression QCodecInfo::compression()
{
	return mCompression;
}

QString QCodecInfo::abbreviation()
{
	return mAbbreviation;
}

QString QCodecInfo::name()
{
	return mName;
}

QStringList QCodecInfo::extensions()
{
	return mExtensions;
}

QStringList QCodecInfo::starExtensions()
{
	QStringList result;
	for(int i = 0; i < mExtensions.size(); ++i)
	{
		result[i] = "*." + mExtensions[i];
	}
	return result;
}

bool QCodecInfo::operator == (const QCodecInfo &other) const
{
	return (mCompression == other.mCompression) && (mAbbreviation == other.mAbbreviation) && (mName == other.mName);
}
