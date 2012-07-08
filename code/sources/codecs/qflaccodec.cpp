#include <qflaccodec.h>

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
