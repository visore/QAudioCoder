#ifndef QAUDIOMANAGER_H
#define QAUDIOMANAGER_H

#include <qabstractcoder.h>
#include <qaudiocodec.h>
/*
class QAudioManager
{

	public:

		QAudioManager();
		~QAudioManager();

		void testLibraries();
		void addSearchPath(QString searchPath);
		void addFileName(QString coderName, QString name);
		void addFileExtension(QString coderName, QString extension);

		QAudioCodec& detectCodec(QString filePath);
		QAbstractCoder& detectCoder(QString filePath);

		QList<QAudioCodec> supportedCodecs(); //Supported codecs that can not necessarily be used
		QList<QAudioCodec> availableCodecs(); //Supported codecs that can be used

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

};*/

#endif
