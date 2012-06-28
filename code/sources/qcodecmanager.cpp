#include <qcodecmanager.h>
#include <QDir>

QCodecManager::QCodecManager()
{
	mSupportedCodecs.append(new QLameCodec);

	initializeSearchPaths();
	testLibraries();
}

QCodecManager::~QCodecManager()
{
	qDeleteAll(mSupportedCodecs);
	mSupportedCodecs.clear();
	mAvailableCodecs.clear();
}

void QCodecManager::testLibraries()
{
	for(int i = 0; i < mSupportedCodecs.size(); ++i)
	{
		if(!isCodecAvailable(mSupportedCodecs[i]))
		{
			testLibrary(mSupportedCodecs[i]);
		}
	}
}

void QCodecManager::addFileName(QString codecName, QString name)
{
	QAbstractCodec *codec = codecByName(codecName);
	if(codec != NULL)
	{
		codec->addFileName(name);
		if(!isCodecAvailable(codec))
		{
			testLibrary(codec);
		}
	}
}

void QCodecManager::addFileExtension(QString codecName, QString extension)
{
	QAbstractCodec *codec = codecByName(codecName);
	if(codec != NULL)
	{
		codec->addFileExtension(extension);
		if(!isCodecAvailable(codec))
		{
			testLibrary(codec);
		}
	}
}

void QCodecManager::addSearchPath(QString searchPath)
{
	mSearchPaths.append(searchPath);
	testLibraries();
}

QCodecInfo QCodecManager::detect(QString filePath)
{

}

QCodecInfo QCodecManager::detect(QByteArray data)
{

}

QList<QAbstractCodec*> QCodecManager::supportedCodecs()
{
	return mSupportedCodecs;
}

QList<QAbstractCodec*> QCodecManager::availableCodecs()
{
	return mAvailableCodecs;
}

void QCodecManager::initializeSearchPaths()
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

bool QCodecManager::testLibrary(QAbstractCodec *codec)
{
	QStringList fileNames = codec->fileNames();
	QStringList fileExtensions = codec->fileExtensions();
	for(int j = 0; j < mSearchPaths.size(); ++j)
	{
		QString path = mSearchPaths[j];
		for(int k = 0; k < fileNames.size(); ++k)
		{
			QString fileName = fileNames[k];
			for(int i = 0; i < fileExtensions.size(); ++i)
			{
				if(codec->load(path + fileName + fileExtensions[i]) == QAbstractCodec::NoError || codec->load(path + "lib" + fileName + fileExtensions[i]) == QAbstractCodec::NoError)
				{
					codec->unload();
					mAvailableCodecs.append(codec);
					return true;
				}
				
			}
		}
	}
	return false;
}

bool QCodecManager::isCodecAvailable(QAbstractCodec *codec)
{
	for(int i = 0; i < mAvailableCodecs.size(); ++i)
	{
		if((*codec) == (*mAvailableCodecs[i]))
		{
			return true;
		}
	}
	return false;
}

QAbstractCodec* QCodecManager::codecByName(QString name)
{
	for(int i = 0; i < mSupportedCodecs.size(); ++i)
	{
		if(mSupportedCodecs[i]->name().trimmed().toLower() == name.trimmed().toLower())
		{
			return mSupportedCodecs[i];
		}
	}
	return NULL;
}
