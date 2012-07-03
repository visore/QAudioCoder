#include <qcommon.h>

QAudioFormat::SampleType QAudio::toFormatSampleType(QAudio::SampleType type)
{
	if(type == QAudio::SignedInt) return QAudioFormat::SignedInt;
	else if(type == QAudio::UnSignedInt) return QAudioFormat::UnSignedInt;
	else if(type == QAudio::Float) return QAudioFormat::Float;
	return QAudioFormat::Unknown;
}

QAudio::SampleType QAudio::toAudioSampleType(QAudioFormat::SampleType type)
{
	if(type == QAudioFormat::SignedInt) return QAudio::SignedInt;
	else if(type == QAudioFormat::UnSignedInt) return QAudio::UnSignedInt;
	else if(type == QAudioFormat::Float) return QAudio::Float;
	return QAudio::Unknown;
}
