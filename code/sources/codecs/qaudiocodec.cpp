#include <qaudiocodec.h>
#include <qextendedaudioformat.h>

QAudioCodec::QAudioCodec()
{
	mShortName = "";
	mLongName = "";
	mCompression = QAudio::UnknownCompression;
}

QString QAudioCodec::shortName() const
{
	return mShortName;
}

QString QAudioCodec::longName() const
{
	return mLongName;
}

QString QAudioCodec::name() const
{
	return mShortName;
}

QAudio::Compression QAudioCodec::compression() const
{
	return mCompression;
}

QStringList QAudioCodec::abbreviations() const
{
	return mAbbreviations;
}

QString QAudioCodec::abbreviation() const
{
	if(mAbbreviations.size() > 0)
	{
		return mAbbreviations[0];
	}
	return "";
}

QStringList QAudioCodec::extensions(const QString prefix) const
{
	QStringList result;
	for(int i = 0; i < mExtensions.size(); ++i)
	{
		result.append(prefix + mExtensions[i]);
	}
	return result;
}

QString QAudioCodec::extension(const QString prefix) const
{
	if(mExtensions.size() > 0)
	{
		return prefix + mExtensions[0];
	}
	return "";
}

void QAudioCodec::setShortName(const QString name)
{
	mShortName = name;
}

void QAudioCodec::setLongName(const QString name)
{
	mLongName = name;
}

void QAudioCodec::setCompression(const QAudio::Compression compression)
{
	mCompression = compression;
}

void QAudioCodec::addAbbreviation(const QString abbreviation)
{
	mAbbreviations.append(abbreviation);
}

void QAudioCodec::addExtension(const QString extension)
{
	mExtensions.append(extension);
}

bool QAudioCodec::operator == (const QAudioCodec &other) const
{
	return mShortName.trimmed().toLower() == other.mShortName.trimmed().toLower();
}

bool QAudioCodec::operator != (const QAudioCodec &other) const
{
	return mShortName.trimmed().toLower() != other.mShortName.trimmed().toLower();
}
