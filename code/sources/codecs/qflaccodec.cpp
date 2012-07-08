#include <qflaccodec.h>

QByteArray QFlacCodec::createHeader(const QExtendedAudioFormat &format, const QAudioInfo &info)
{

}

QByteArray QFlacCodec::createTrailer(const QExtendedAudioFormat &format, const QAudioInfo &info)
{
	return QByteArray();
}

Qt::Validity QFlacCodec::interpretHeader(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info)
{

}

Qt::Validity QFlacCodec::interpretTrailer(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info)
{
	return Qt::Invalid;
}

void QFlacCodec::initialize()
{
	//Names
	setShortName("Free Lossless Audio Codec");
	setLongName("Xiph.Org Foundation Free Lossless Audio Codec");

	//Compression
	setCompression(QAudio::LosslessCompression);

	//Abbreviations
	addAbbreviation("FLAC");

	//Extensions
	addExtension("flac");
}
