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

int QWaveCodec::encode(const qint8 input[], int inputSize)
{
	//QCodecChunk chunk(input);
}

int QWaveCodec::encode(const qint16 input[], int inputSize)
{
}

int QWaveCodec::encode(const qint32 input[], int inputSize)
{
}

QAbstractCodec::Error QWaveCodec::initializeLibrary()
{
	return QAbstractCodec::NoError;
}
