#include <qmp3codec.h>

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
