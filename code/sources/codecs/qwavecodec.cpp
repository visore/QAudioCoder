#include <qwavecodec.h>

QByteArray QWaveCodec::createHeader(const QExtendedAudioFormat &format, const QAudioInfo &info)
{

}

QByteArray QWaveCodec::createTrailer(const QExtendedAudioFormat &format, const QAudioInfo &info)
{
	return QByteArray();
}

Qt::Validity QWaveCodec::interpretHeader(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info)
{

}

Qt::Validity QWaveCodec::interpretTrailer(const QByteArray &data, QExtendedAudioFormat &format, QAudioInfo &info)
{
	return Qt::Invalid;
}

void QWaveCodec::initialize()
{
	//Names
	setShortName("Waveform");
	setLongName("Resource Interchange File Format Waveform");

	//Compression
	setCompression(QAudio::LosslessCompression);

	//Abbreviations
	addAbbreviation("WAVE");
	addAbbreviation("WAVE");
	addAbbreviation("RIFF");
	addAbbreviation("RIFFWAV");
	addAbbreviation("RIFFWAVE");

	//Extensions
	addExtension("wav");
	addExtension("wave");
	addExtension("riff");
}
