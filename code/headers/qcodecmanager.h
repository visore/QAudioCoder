#ifndef QCODECMANAGER_H
#define QCODECMANAGER_H

#include <qcodecinfo.h>
#include <qabstractcoder.h>

class QCodecManager
{

	public:

		QCodecManager();
		~QCodecManager();

		void testLibraries();
		void addSearchPath(QString searchPath);
		void addFileName(QString coderName, QString name);
		void addFileExtension(QString coderName, QString extension);

		QCodecInfo detect(QString filePath);
		QCodecInfo detect(QByteArray data);

		QList<QAbstractCoder*> supportedCoders(); //Coders supported by QAudioCoder
		QList<QAbstractCoder*> availableCoders(); //Coders supported by QAudioCoder and which can be loaded

	protected:

		void initializeSearchPaths();
		bool testLibrary(QAbstractCoder *coder);
		bool isCoderAvailable(QAbstractCoder *coder);
		QAbstractCoder* coderByName(QString name);

	private:

		QList<QAbstractCoder*> mSupportedCoders;
		QList<QAbstractCoder*> mAvailableCoders;
		QCodecInfoList mSupported;
		QStringList mSearchPaths;

};

#endif
