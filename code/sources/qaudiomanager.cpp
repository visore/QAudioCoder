#include <qaudiomanager.h>
#include <qwavecoder.h>
#include <qlamecoder.h>
#include <qflaccoder.h>
#include <QDir>
/*
QAudioManager::QAudioManager()
{
	mSupportedCoders.append(new QWaveCoder);
	mSupportedCoders.append(new QLameCoder);
	mSupportedCoders.append(new QFlacCoder);

	initializeSearchPaths();
	testLibraries();
}

QAudioManager::~QAudioManager()
{
	qDeleteAll(mSupportedCoders);
	mSupportedCoders.clear();
	mAvailableCoders.clear();
}

void QAudioManager::testLibraries()
{
	for(int i = 0; i < mSupportedCoders.size(); ++i)
	{
		if(!isCoderAvailable(mSupportedCoders[i]))
		{
			testLibrary(mSupportedCoders[i]);
		}
	}
}

void QAudioManager::addFileName(QString coderName, QString name)
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

void QAudioManager::addFileExtension(QString coderName, QString extension)
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

void QAudioManager::addSearchPath(QString searchPath)
{
	mSearchPaths.append(searchPath);
	testLibraries();
}

QCodecInfo QAudioManager::detect(QString filePath)
{

}

QCodecInfo QAudioManager::detect(QByteArray data)
{

}

QList<QAbstractCoder*> QAudioManager::supportedCoders()
{
	return mSupportedCoders;
}

QList<QAbstractCoder*> QAudioManager::availableCoders()
{
	return mAvailableCoders;
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
					mAvailableCoders.append(coder);
					return true;
				}
				
			}
		}
	}
	return false;
}

bool QAudioManager::isCoderAvailable(QAbstractCoder *coder)
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

QAbstractCoder* QAudioManager::coderByName(QString name)
{
	for(int i = 0; i < mSupportedCoders.size(); ++i)
	{
		if(mSupportedCoders[i]->name().trimmed().toLower() == name.trimmed().toLower())
		{
			return mSupportedCoders[i];
		}
	}
	return NULL;
}*/
