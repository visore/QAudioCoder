#include <qcodecmanager.h>
#include <qwavecoder.h>
#include <qlamecoder.h>
#include <qflaccoder.h>
#include <QDir>

QCoderManager::QCoderManager()
{
	mSupportedCoders.append(new QWaveCoder);
	mSupportedCoders.append(new QLameCoder);
	mSupportedCoders.append(new QFlacCoder);

	initializeSearchPaths();
	testLibraries();
}

QCoderManager::~QCoderManager()
{
	qDeleteAll(mSupportedCoders);
	mSupportedCoders.clear();
	mAvailableCoders.clear();
}

void QCoderManager::testLibraries()
{
	for(int i = 0; i < mSupportedCoders.size(); ++i)
	{
		if(!isCoderAvailable(mSupportedCoders[i]))
		{
			testLibrary(mSupportedCoders[i]);
		}
	}
}

void QCoderManager::addFileName(QString coderName, QString name)
{
	QAbstractCoder *coder = coderByName(coderName);
	if(coder != NULL)
	{
		coder->addFileName(name);
		if(!isCoderAvailable(coder))
		{
			testLibrary(coder);
		}
	}
}

void QCoderManager::addFileExtension(QString coderName, QString extension)
{
	QAbstractCoder *coder = coderByName(coderName);
	if(coder != NULL)
	{
		coder->addFileExtension(extension);
		if(!isCoderAvailable(coder))
		{
			testLibrary(coder);
		}
	}
}

void QCoderManager::addSearchPath(QString searchPath)
{
	mSearchPaths.append(searchPath);
	testLibraries();
}

QCodecInfo QCoderManager::detect(QString filePath)
{

}

QCodecInfo QCoderManager::detect(QByteArray data)
{

}

QList<QAbstractCoder*> QCoderManager::supportedCoders()
{
	return mSupportedCoders;
}

QList<QAbstractCoder*> QCoderManager::availableCoders()
{
	return mAvailableCoders;
}

void QCoderManager::initializeSearchPaths()
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

bool QCoderManager::testLibrary(QAbstractCoder *coder)
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
					mAvailableCoders.append(coder);
					return true;
				}
				
			}
		}
	}
	return false;
}

bool QCoderManager::isCoderAvailable(QAbstractCoder *coder)
{
	for(int i = 0; i < mAvailableCoders.size(); ++i)
	{
		if((*coder) == (*mAvailableCoders[i]))
		{
			return true;
		}
	}
	return false;
}

QAbstractCoder* QCoderManager::coderByName(QString name)
{
	for(int i = 0; i < mSupportedCoders.size(); ++i)
	{
		if(mSupportedCoders[i]->name().trimmed().toLower() == name.trimmed().toLower())
		{
			return mSupportedCoders[i];
		}
	}
	return NULL;
}
