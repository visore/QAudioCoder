#ifndef QAUDIOCODEC_H
#define QAUDIOCODEC_H

#include <QStringList>
#include <QByteArray>
#include <qaudioinfo.h>
#include <qcommon.h>

class QExtendedAudioFormat;

namespace QAudio
{

	enum Compression
	{
		UnknownCompression = 0,
		LossyCompression = 1,
		LosslessCompression = 2
	};

};

class QAudioCodec
{

	public:

		QString shortName() const;
		QString longName() const;
		QString name() const;
		QAudio::Compression compression() const;
		QStringList abbreviations() const;
		QString abbreviation() const;
		QStringList extensions(const QString prefix = "") const;
		QString extension(const QString prefix = "") const;

		bool operator == (const QAudioCodec &other) const;
		bool operator != (const QAudioCodec &other) const;

	protected:

		QAudioCodec();

		void setShortName(const QString name);
		void setLongName(const QString name);
		void setCompression(const QAudio::Compression compression);
		void addAbbreviation(const QString abbreviation);
		void addExtension(const QString extension);

	private:

		QString mShortName;
		QString mLongName;
		QAudio::Compression mCompression;
		QStringList mAbbreviations;
		QStringList mExtensions;
		
};

template <typename T>
class QAudioCodecHolder : public QAudioCodec
{

	public:

		static T& instance()
		{
			static T instance;
			if(!instance.mWasInitialized)
			{
				mWasInitialized = true;
				QAudioCodecHolder<T>& dummy = instance;
				dummy.initialize();
			}
			return instance;
		}

	protected:

		virtual void initialize() = 0;

	private:

		static bool mWasInitialized;
		
};

template <typename T>
bool QAudioCodecHolder<T>::mWasInitialized = false;

#endif
