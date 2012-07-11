#ifndef QAUDIOMANAGER_H
#define QAUDIOMANAGER_H

#include <qabstractcoder.h>
#include <qaudiocodec.h>

typedef QList<QAbstractCoder*> QCoderList;
typedef QList<QAudioCodec*> QCodecList;

class QAudioManager
{

	public:

		enum Mode
		{
			Supported = 0,
			Available = 1	
		};

		~QAudioManager();
		static QAudioManager& instance();

		void addSearchPath(const QString searchPath);
		void addFileName(const QString coderName, const QString name);
		void addFileExtension(const QString coderName, const QString extension);

		QAudioCodec* codec(const QString name, const QAudioManager::Mode mode = QAudioManager::Available) const;

		QAbstractCoder* coder(const QString name, const QAudioManager::Mode mode = QAudioManager::Available) const;
		QAbstractCoder* coder(const QAudioCodec *codec, const QAudioManager::Mode mode = QAudioManager::Available) const;
		QAbstractCoder* coder(const QExtendedAudioFormat &format, const QAudioManager::Mode mode = QAudioManager::Available) const;

		QAbstractCoder* detect(const QString filePath, const QAudioManager::Mode mode = QAudioManager::Available);
		QAbstractCoder* detect(const QByteArray &data, const QAudioManager::Mode mode = QAudioManager::Available);

		bool isAvailable(const QAbstractCoder *coder) const;
		bool isAvailable(const QAudioCodec *codec) const;
		bool isSupported(const QAbstractCoder *coder) const;
		bool isSupported(const QAudioCodec *codec) const;

		QCoderList coders(const QAudioManager::Mode mode = QAudioManager::Available);
		QCodecList codecs(const QAudioManager::Mode mode = QAudioManager::Available);

	protected:

		QAudioManager();

		void initializeSearchPaths();
		void testLibraries();
		bool testLibrary(QAbstractCoder *coder);

		void add(const QAudioManager::Mode mode, QAbstractCoder *coder);
		void add(const QAudioManager::Mode mode, QAudioCodec *codec);

	private:

		QCoderList mSupportedCoders;
		QCoderList mAvailableCoders;
		QCodecList mSupportedCodecs;
		QCodecList mAvailableCodecs;
		QStringList mSearchPaths;

};

#endif
