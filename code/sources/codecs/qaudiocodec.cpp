#ifndef QAUDIOCODEC_CPP
#define QAUDIOCODEC_CPP

#include <qaudiocodec.h>
#include <typeinfo>

template <typename T>
bool QAudioCodec<T>::mWasInitialized = false;

template <typename T>
QAudioCodec<T>::QAudioCodec()
{
	mShortName = "";
	mLongName = "";
	mCompression = QAudio::UnknownCompression;
}

template <typename T>
T& QAudioCodec<T>::instance()
{
	static T instance;
	if(!instance.mWasInitialized)
	{
		mWasInitialized = true;
		QAudioCodec<T>& dummy = instance;
        dummy.initialize();
	}
	return instance;
}

template <typename T>
QString QAudioCodec<T>::shortName() const
{
	return mShortName;
}

template <typename T>
QString QAudioCodec<T>::longName() const
{
	return mLongName;
}

template <typename T>
QString QAudioCodec<T>::name() const
{
	return mShortName;
}

template <typename T>
QAudio::Compression QAudioCodec<T>::compression() const
{
	return mCompression;
}

template <typename T>
QStringList QAudioCodec<T>::abbreviations() const
{
	return mAbbreviations;
}

template <typename T>
QString QAudioCodec<T>::abbreviation() const
{
	if(mAbbreviations.size() > 0)
	{
		return mAbbreviations[0];
	}
	return "";
}

template <typename T>
QStringList QAudioCodec<T>::extensions(const QString prefix) const
{
	QStringList result;
	for(int i = 0; i < mExtensions.size(); ++i)
	{
		result.append(prefix + mExtensions[i]);
	}
	return result;
}

template <typename T>
QString QAudioCodec<T>::extension(const QString prefix) const
{
	if(mExtensions.size() > 0)
	{
		return prefix + mExtensions[0];
	}
	return "";
}

template <typename T>
void QAudioCodec<T>::setShortName(const QString name)
{
	mShortName = name;
}

template <typename T>
void QAudioCodec<T>::setLongName(const QString name)
{
	mLongName = name;
}

template <typename T>
void QAudioCodec<T>::setCompression(const QAudio::Compression compression)
{
	mCompression = compression;
}

template <typename T>
void QAudioCodec<T>::addAbbreviation(const QString abbreviation)
{
	mAbbreviations.append(abbreviation);
}

template <typename T>
void QAudioCodec<T>::addExtension(const QString extension)
{
	mExtensions.append(extension);
}

template <typename T>
bool QAudioCodec<T>::operator == (const QAudioCodec &other) const
{
	return typeid(this) == typeid (other);
}

template <typename T>
bool QAudioCodec<T>::operator != (const QAudioCodec &other) const
{
	return typeid(this) != typeid (other);
}

#endif
