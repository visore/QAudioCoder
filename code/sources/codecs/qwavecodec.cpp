#include <qwavecodec.h>

bool QWaveCodec::initialize()
{
	mError = QAbstractCodec::NoError;
	return true;
}

bool QWaveCodec::finalize()
{
	return true;
}

void QWaveCodec::encode8(const qbyte input[], int samples)
{
	/*QAudioChunk chunk(input, samples, samples);
	addChunk(chunk);*/
}

void QWaveCodec::encode16(const qbyte input[], int samples)
{

}

void QWaveCodec::encode32(const qbyte input[], int samples)
{

}

void QWaveCodec::decode8(const qbyte input[], int size)
{

}

void QWaveCodec::decode16(const qbyte input[], int size)
{

}
void QWaveCodec::decode32(const qbyte input[], int size)
{

}

QAbstractCodec::Error QWaveCodec::initializeLibrary()
{
	return QAbstractCodec::NoError;
}
