#include <qwavecodec.h>

void QWaveCodec::initialize()
{
	//Names
	setShortName("Waveform");
	setLongName("Resource Interchange File Format Waveform");

	//Compression
	setCompression(QAudio::LosslessCompression);

	//Abbreviations
	addAbbreviation("WAVE");
	addAbbreviation("WAV");
	addAbbreviation("RIFF");
	addAbbreviation("RIFFWAV");
	addAbbreviation("RIFFWAVE");

	//Extensions
	addExtension("wav");
	addExtension("wave");
	addExtension("riff");
}
