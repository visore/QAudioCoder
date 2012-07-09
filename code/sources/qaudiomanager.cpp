#include <qaudiomanager.h>
#include <qwavecoder.h>
#include <qlamecoder.h>
#include <qflaccoder.h>
#include <QDir>

#define DEFAUL_HEADER_SIZE 8192
#define MAXIMUM_HEADER_TESTS 50

QAudioManager::QAudioManager()
{
	add(QAudioManager::Supported, new QWaveCoder);
	add(QAudioManager::Supported, new QLameCoder);
	add(QAudioManager::Supported, new QFlacCoder);

	initializeSearchPaths();
	testLibraries();
}

QAudioManager& QAudioManager::instance()
{
	static QAudioManager instance;
	return instance;
}

void QAudioManager::addFileName(const QString coderName, const QString name)
{
	QAbstractCoder *theCoder = coder(coderName, QAudioManager::Available);
	if(theCoder != NULL)
	{
		theCoder->addFileName(name);
		testLibrary(theCoder);
	}
}

void QAudioManager::addFileExtension(const QString coderName, const QString extension)
{
	QAbstractCoder *theCoder = coder(coderName, QAudioManager::Available);
	if(theCoder != NULL)
	{
		theCoder->addFileExtension(extension);
		testLibrary(theCoder);
	}
}

void QAudioManager::addSearchPath(const QString searchPath)
{
	mSearchPaths.append(searchPath);
	testLibraries();
}

QAudioCodec* QAudioManager::codec(const QString name, const QAudioManager::Mode mode) const
{
	QString newName = name.trimmed().toLower();
	if(mode == QAudioManager::Available)
	{
		for(int i = 0; i < mAvailableCodecs.size(); ++i)
		{
			if(mAvailableCodecs[i]->longName().toLower() == newName || mAvailableCodecs[i]->shortName().toLower() == newName)
			{
				return mAvailableCodecs[i];
			}
			QStringList abbreviations = mAvailableCodecs[i]->abbreviations();
			for(int k = 0; k < abbreviations.size(); ++k)
			{
				if(abbreviations[k].toLower() == newName)
				{
					return mAvailableCodecs[i];
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < mSupportedCodecs.size(); ++i)
		{
			if(mSupportedCodecs[i]->longName().toLower() == newName || mSupportedCodecs[i]->shortName().toLower() == newName)
			{
				return mSupportedCodecs[i];
			}
			QStringList abbreviations = mSupportedCodecs[i]->abbreviations();
			for(int k = 0; k < abbreviations.size(); ++k)
			{
				if(abbreviations[k].toLower() == newName)
				{
					return mSupportedCodecs[i];
				}
			}
		}
	}
	return NULL;
}

QAbstractCoder* QAudioManager::coder(const QString name, const QAudioManager::Mode mode) const
{
	QString newName = name.trimmed().toLower(); 
	if(mode == QAudioManager::Available)
	{
		for(int i = 0; i < mAvailableCoders.size(); ++i)
		{
			if(mAvailableCoders[i]->name().toLower() == newName)
			{
				return mAvailableCoders[i];
			}
			QList<QAudioCodec*> codecs = mAvailableCoders[i]->supportedCodecs();
			for(int j = 0; j < codecs.size(); ++j)
			{
				if(codecs[j]->longName().toLower() == newName || codecs[j]->shortName().toLower() == newName)
				{
					return mAvailableCoders[i];
				}
				QStringList abbreviations = codecs[j]->abbreviations();
				for(int k = 0; k < abbreviations.size(); ++k)
				{
					if(abbreviations[k].toLower() == newName)
					{
						return mAvailableCoders[i];
					}
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < mSupportedCoders.size(); ++i)
		{
			if(mSupportedCoders[i]->name().toLower() == newName)
			{
				return mSupportedCoders[i];
			}
			QList<QAudioCodec*> codecs = mSupportedCoders[i]->supportedCodecs();
			for(int j = 0; j < codecs.size(); ++j)
			{
				if(codecs[j]->longName().toLower() == newName || codecs[j]->shortName().toLower() == newName)
				{
					return mSupportedCoders[i];
				}
				QStringList abbreviations = codecs[j]->abbreviations();
				for(int k = 0; k < abbreviations.size(); ++k)
				{
					if(abbreviations[k].toLower() == newName)
					{
						return mSupportedCoders[i];
					}
				}
			}
		}
	}
	return NULL;
}

QAbstractCoder* QAudioManager::coder(const QAudioCodec *codec, const QAudioManager::Mode mode) const
{
	if(codec != NULL)
	{
		if(mode == QAudioManager::Available)
		{
			for(int i = 0; i < mAvailableCoders.size(); ++i)
			{
				QList<QAudioCodec*> codecs = mAvailableCoders[i]->supportedCodecs();
				for(int j = 0; j < codecs.size(); ++j)
				{
					if((*codecs[j]) == (*codec))
					{
						return mAvailableCoders[i];
					}
				}
			}
		}
		else
		{
			for(int i = 0; i < mSupportedCoders.size(); ++i)
			{
				QList<QAudioCodec*> codecs = mSupportedCoders[i]->supportedCodecs();
				for(int j = 0; j < codecs.size(); ++j)
				{
					if((*codecs[j]) == (*codec))
					{
						return mSupportedCoders[i];
					}
				}
			}
		}
	}
	return NULL;
}

QAbstractCoder* QAudioManager::coder(const QExtendedAudioFormat &format, const QAudioManager::Mode mode) const
{
	return coder(format.codec(), mode);
}

QAbstractCoder* QAudioManager::detect(const QString filePath, const QAudioManager::Mode mode)
{
	QFile file(filePath);
	if(!file.open(QIODevice::ReadOnly))
	{
		return NULL;
	}

	QCoderList *coders;
	if(mode == QAudioManager::Available)
	{
		coders = &mAvailableCoders;
	}
	else
	{
		coders = &mSupportedCoders;
	} 

	QByteArray data;
	for(int i = 0; i < MAXIMUM_HEADER_TESTS; ++i)
	{
		data.append(file.read(DEFAUL_HEADER_SIZE));
		for(int j = 0; j < coders->size(); ++j)
		{
			if(coders->at(j)->detectCodec(data) != NULL)
			{
				file.close();
				return coders->at(j);
			}
		}
	}

	file.close();
	return NULL;
}

QAbstractCoder* QAudioManager::detect(const QByteArray data, const QAudioManager::Mode mode)
{
	QCoderList coders;
	if(mode == QAudioManager::Available)
	{
		coders = mAvailableCoders;
	}
	else
	{
		coders = mSupportedCoders;
	}
	for(int i = 0; i < coders.size(); ++i)
	{
		if(coders[i]->detectCodec(data) != NULL)
		{
			return coders[i];
		}
	}
	return NULL;
}

bool QAudioManager::isAvailable(const QAbstractCoder *coder) const
{
	if(coder != NULL)
	{
		for(int i = 0; i < mAvailableCoders.size(); ++i)
		{
			if((*mAvailableCoders[i]) == (*coder))
			{
				return true;
			}
		}
	}
	return false;
}

bool QAudioManager::isAvailable(const QAudioCodec *codec) const
{
	if(codec != NULL)
	{
		for(int i = 0; i < mAvailableCodecs.size(); ++i)
		{
			if((*mAvailableCodecs[i]) == (*codec))
			{
				return true;
			}
		}
	}
	return false;
}

bool QAudioManager::isSupported(const QAbstractCoder *coder) const
{
	if(coder != NULL)
	{
		for(int i = 0; i < mSupportedCoders.size(); ++i)
		{
			if((*mSupportedCoders[i]) == (*coder))
			{
				return true;
			}
		}
	}
	return false;
}

bool QAudioManager::isSupported(const QAudioCodec *codec) const
{
	if(codec != NULL)
	{
		for(int i = 0; i < mSupportedCodecs.size(); ++i)
		{
			if((*mSupportedCodecs[i]) == (*codec))
			{
				return true;
			}
		}
	}
	return false;
}

QCoderList QAudioManager::coders(const QAudioManager::Mode mode)
{
	if(mode == QAudioManager::Available)
	{
		return mAvailableCoders;
	}
	else
	{
		return mSupportedCoders;
	}
}

QCodecList QAudioManager::codecs(const QAudioManager::Mode mode)
{
	if(mode == QAudioManager::Available)
	{
		return mAvailableCodecs;
	}
	else
	{
		return mSupportedCodecs;
	}
}

void QAudioManager::initializeSearchPaths()
{
	QStringList paths;

	paths.append(QDir::currentPath() + QDir::separator());
	paths.append(QDir::currentPath() + QDir::separator() + "libraries");
	paths.append(QDir::currentPath() + QDir::separator() + "library");
	paths.append(QDir::currentPath() + QDir::separator() + "Libraries");
	paths.append(QDir::currentPath() + QDir::separator() + "Library");
	paths.append(QDir::currentPath() + QDir::separator() + "lib");
	paths.append(QDir::currentPath() + QDir::separator() + "Lib");
	paths.append(QDir::currentPath() + QDir::separator() + "libs");
	paths.append(QDir::currentPath() + QDir::separator() + "Libs");

	#ifdef WINDOWS

	#elif defined MACOSX

	#elif defined LINUX
		paths.append(QString("") + QDir::separator() + "lib");
		paths.append(QString("") + QDir::separator() + "usr" + QDir::separator() + "lib");
		paths.append(QString("") + QDir::separator() + "usr" + QDir::separator() + "lib");
		paths.append(QString("") + QDir::separator() + "usr" + QDir::separator() + "lib" + QDir::separator() + "i386-linux-gnu");
		paths.append(QString("") + QDir::separator() + "usr" + QDir::separator() + "local" + QDir::separator() + "lib");
	#endif

	for(int i = 0; i < paths.size(); ++i)
	{
		QDir dir(paths[i]);
		if(dir.exists())
		{
			mSearchPaths.append(dir.absolutePath() + QDir::separator());
		}
	}
}

void QAudioManager::testLibraries()
{
	for(int i = 0; i < mSupportedCoders.size(); ++i)
	{
		testLibrary(mSupportedCoders[i]);
	}
}

bool QAudioManager::testLibrary(QAbstractCoder *coder)
{
	QStringList fileNames = coder->fileNames();
	QStringList fileExtensions = coder->fileExtensions();
	for(int j = 0; j < mSearchPaths.size(); ++j)
	{
		QString path = mSearchPaths[j];
		for(int k = 0; k < fileNames.size(); ++k)
		{
			QString fileName = fileNames[k];
			for(int i = 0; i < fileExtensions.size(); ++i)
			{
				if(coder->load(path + fileName + fileExtensions[i]) == QAbstractCoder::NoError || coder->load(path + "lib" + fileName + fileExtensions[i]) == QAbstractCoder::NoError)
				{
					coder->unload();
					add(QAudioManager::Available, coder);
					return true;
				}
				
			}
		}
	}
	return false;
}

void QAudioManager::add(const QAudioManager::Mode mode,  QAbstractCoder *coder)
{
	if(mode == QAudioManager::Available)
	{
		if(!isAvailable(coder))
		{
			mAvailableCoders.append(coder);
			QList<QAudioCodec*> codecs = coder->supportedCodecs();
			for(int i = 0; i < codecs.size(); ++i)
			{
				add(mode, codecs[i]);
			}
		}
	}
	else
	{
		if(!isSupported(coder))
		{
			mSupportedCoders.append(coder);
			QList<QAudioCodec*> codecs = coder->supportedCodecs();
			for(int i = 0; i < codecs.size(); ++i)
			{
				add(mode, codecs[i]);
			}
		}
	}
}

void QAudioManager::add(const QAudioManager::Mode mode, QAudioCodec *codec)
{
	if(mode == QAudioManager::Available)
	{
		if(!isAvailable(codec))
		{
			mAvailableCodecs.append(codec);
		}
	}
	else
	{
		if(!isSupported(codec))
		{
			mSupportedCodecs.append(codec);
		}
	}
}
