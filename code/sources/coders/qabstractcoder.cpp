#include <qabstractcoder.h>
#include <QFile>

QAbstractCoder::QAbstractCoder()
{
	mName = "undefined";
	mVersion = "undefined";
	setError(QCoder::NoError);

	addFileExtension("");
	addFileExtension(".a");
	addFileExtension(".lib");
	#ifdef WINDOWS
		addFileExtension(".dll");
	#elif defined MACOSX
		addFileExtension(".so");
		addFileExtension(".dylib");
	#elif defined LINUX
		addFileExtension(".so");
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

QCoder::Error QAbstractCoder::load()
{
	if(!mLibrary.isLoaded())
	{
		QFile file(filePath());
		if(!file.exists())
		{
			setError(QCoder::LibraryFileError);
			return error();
		}
		if(mLibrary.load())
		{
			setError(initializeLibrary());
			if(error() != QCoder::NoError)
			{
				unload();
			}
			return error();
		}
		else
		{
			setError(QCoder::LibraryFileError);
			return error();
		}
	}
	setError(QCoder::NoError);
	return error();
}

QCoder::Error QAbstractCoder::load(QString filePath)
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

QCoder::Error QAbstractCoder::error() const
{
	return mError;
}

void QAbstractCoder::setError(QCoder::Error error)
{
	mError = error;
	if(mError != QCoder::NoError)
	{
		emit failed(mError);
	}
}

bool QAbstractCoder::operator == (const QAbstractCoder &other) const
{
	return mName != "" && mName.trimmed().toLower() == other.mName.trimmed().toLower();
}

bool QAbstractCoder::operator != (const QAbstractCoder &other) const
{
	return mName == "" || mName.trimmed().toLower() != other.mName.trimmed().toLower();
}
