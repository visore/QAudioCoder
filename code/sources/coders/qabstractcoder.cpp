#include <qabstractcoder.h>
#include <QFile>

QAbstractCoder::QAbstractCoder()
{
	mName = "undefined";
	mVersion = "undefined";
	mError = QAbstractCoder::NoError;

	addFileExtension("");
	addFileExtension(".a");
	addFileExtension(".lib");
	#ifdef WINDOWS
		addFileExtension(".dll");
	#elif defined MACOSX
		addFileExtension(".so");
		addFileExtension(".so.0");
		addFileExtension(".so.0.0");
		addFileExtension(".so.0.0.0");
		addFileExtension(".dylib");
	#elif defined LINUX
		addFileExtension(".so");
		addFileExtension(".so.0");
		addFileExtension(".so.0.0");
		addFileExtension(".so.0.0.0");
	#endif
}

QAbstractCoder::~QAbstractCoder()
{
	mLibrary.unload();
}

const QList<QAudioCodec*> QAbstractCoder::supportedCodecs() const
{
	return mSupportedCodecs;
}

QAbstractCoder::Header QAbstractCoder::inspectHeader(const QByteArray &header, QAudioInfo &content)
{
	return inspectHeader(header, mInputFormat, content);
}

void QAbstractCoder::createHeader(QByteArray &header, QAudioInfo &content)
{
	qreal sizeRatio = (mOutputFormat.sampleSize() + mOutputFormat.channelCount() + mOutputFormat.sampleRate()) / qreal(mInputFormat.sampleSize() + mInputFormat.channelCount() + mInputFormat.sampleRate());
	qreal sampleRatio = (mOutputFormat.channelCount() + mOutputFormat.sampleRate()) / qreal(mInputFormat.channelCount() + mInputFormat.sampleRate());
	content.setDataSize(content.dataSize() * sizeRatio);
	content.setSize(content.dataSize() + content.headerSize() + content.trailerSize());
	content.setSamples(content.samples() * sampleRatio);

	createHeader(header, mOutputFormat, content);
}

QAbstractCoder::Error QAbstractCoder::load()
{
	if(!mLibrary.isLoaded())
	{
		QFile file(filePath());
		if(!file.exists())
		{
			mError = QAbstractCoder::PathError;
			return mError;
		}
		if(mLibrary.load())
		{
			QAbstractCoder::Error error = initializeLibrary();
			if(error != QAbstractCoder::NoError)
			{
				unload();
			}
			mError = error;
			return mError;
		}
		else
		{
			mError = QAbstractCoder::FileError;
			return mError;
		}
	}
	mError = QAbstractCoder::NoError;
	return mError;
}

QAbstractCoder::Error QAbstractCoder::load(QString filePath)
{
	setFilePath(filePath);
	return load();
}

bool QAbstractCoder::unload()
{
	return mLibrary.unload();
}

QString QAbstractCoder::filePath() const
{
	return mLibrary.fileName();
}

void QAbstractCoder::setFilePath(QString filePath)
{
	mLibrary.setFileName(filePath);
}

QExtendedAudioFormat QAbstractCoder::format(QAudio::Mode mode) const
{
	if(mode == QAudio::AudioInput)
	{
		return mInputFormat;
	}
	else if(mode == QAudio::AudioOutput)
	{
		return mOutputFormat;
	}
	return QExtendedAudioFormat();
}

void QAbstractCoder::setFormat(QAudio::Mode mode, QExtendedAudioFormat format)
{
	if(mode == QAudio::AudioInput)
	{
		mInputFormat = format;
	}
	else if(mode == QAudio::AudioOutput)
	{
		mOutputFormat = format;
	}
}

QString QAbstractCoder::name() const
{
	return mName;
}

QString QAbstractCoder::version() const
{
	return mVersion;
}

QStringList QAbstractCoder::fileNames() const
{
	return mFileNames;
}

QStringList QAbstractCoder::fileExtensions() const
{
	return mFileExtensions;
}

void QAbstractCoder::addFileName(QString name)
{
	mFileNames.append(name);
}

void QAbstractCoder::addFileExtension(QString extension)
{
	mFileExtensions.append(extension);
}

QAbstractCoder::Error QAbstractCoder::error() const
{
	return mError;
}

bool QAbstractCoder::operator == (const QAbstractCoder &other) const
{
	return mName != "" && mName.trimmed().toLower() == other.mName.trimmed().toLower();
}

bool QAbstractCoder::operator != (const QAbstractCoder &other) const
{
	return mName == "" || mName.trimmed().toLower() != other.mName.trimmed().toLower();
}
