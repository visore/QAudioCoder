#ifndef QAUDIOCODEC_H
#define QAUDIOCODEC_H

#include <QStringList>

namespace QAudio
{

	enum Compression
	{
		UnknownCompression = 0,
		LossyCompression = 1,
		LosslessCompression = 2
	};

};

template <typename T>
class QAudioCodec
{

	public:

		static T& instance();

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
		virtual void initialize() = 0;

		void setShortName(const QString name);
		void setLongName(const QString name);
		void setCompression(const QAudio::Compression compression);
		void addAbbreviation(const QString abbreviation);
		void addExtension(const QString extension);

	private:

		static bool mWasInitialized;

		QString mShortName;
		QString mLongName;
		QAudio::Compression mCompression;
		QStringList mAbbreviations;
		QStringList mExtensions;
		
};

#endif
