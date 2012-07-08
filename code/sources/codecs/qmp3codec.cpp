#include <qmp3codec.h>

QByteArray QMp3Codec::createHeader(const QExtendedAudioFormat &format, const QAudioInfo &info)
{

}

QByteArray QMp3Codec::createTrailer(const QExtendedAudioFormat &format, const QAudioInfo &info)
{
	return QByteArray();
}

Qt::Validity QMp3Codec::interpretHeader(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info)
{

}

Qt::Validity QMp3Codec::interpretTrailer(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info)
{
	return Qt::Invalid;
}

void QMp3Codec::initialize()
{
	//Names
	setShortName("MPEG Audio Layer 3");
	setLongName("Moving Picture Experts Group Audio Layer 3");

	//Compression
	setCompression(QAudio::LossyCompression);

	//Abbreviations
	addAbbreviation("MP3");
	addAbbreviation("MPEG3");
	addAbbreviation("MPA3");
	addAbbreviation("MPEGA3");

	//Extensions
	addExtension("mp3");
	addExtension("bitl");
}
