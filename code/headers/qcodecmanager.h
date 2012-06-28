#ifndef QCODECMANAGER_H
#define QCODECMANAGER_H

#include <qcodecinfo.h>
#include <qlamecodec.h>

class QCodecManager
{

	public:

		QCodecManager();
		~QCodecManager();

		void testLibraries();
		void addSearchPath(QString searchPath);
		void addFileName(QString codecName, QString name);
		void addFileExtension(QString codecName, QString extension);

		QCodecInfo detect(QString filePath);
		QCodecInfo detect(QByteArray data);

		QList<QAbstractCodec*> supportedCodecs(); //Codecs supported by QAudioCoder
		QList<QAbstractCodec*> availableCodecs(); //Codecs supported by QAudioCoder and which can be loaded

	protected:

		void initializeSearchPaths();
		bool testLibrary(QAbstractCodec *codec);
		bool isCodecAvailable(QAbstractCodec *codec);
		QAbstractCodec* codecByName(QString name);

	private:

		QList<QAbstractCodec*> mSupportedCodecs;
		QList<QAbstractCodec*> mAvailableCodecs;
		QCodecInfoList mSupported;
		QStringList mSearchPaths;

};

#endif
