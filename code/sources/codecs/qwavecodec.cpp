#include <qwavecodec.h>
#include <qsamplesizeconverter.h>
#include <QDataStream>

QWaveCodec::QWaveCodec()
	: QAbstractCodec()
{
	mName = "Wave";
	addFileName("");
}

QAbstractCodec::Error QWaveCodec::load()
{
	return QAbstractCodec::NoError;
}

QAbstractCodec::Error QWaveCodec::load(QString filePath)
{
	return QAbstractCodec::NoError;
}

bool QWaveCodec::unload()
{
	return true;
}

bool QWaveCodec::inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content)
{
	QDataStream stream((QByteArray*) &header, QIODevice::ReadOnly);
	char data2[2];
	char data4[4];

	//Check if header contains "RIFF"
	if(stream.readRawData(data4, 4) < 4)
	{
		return false;
	}
	if(QString(data4).toLower() == "riff")
	{
		stream.setByteOrder(QDataStream::LittleEndian);
		format.setByteOrder(QAudioFormat::LittleEndian);
	}
	else if(QString(data4).toLower() == "rifx")
	{
		stream.setByteOrder(QDataStream::BigEndian);
		format.setByteOrder(QAudioFormat::BigEndian);
	}
	else
	{
		return false;
	}

	//Check chunk size
	int chunkSize;
	if(stream.readRawData(data4, 4) < 4 || (chunkSize = toInt(data4)) <= 0)
	{
		return false;
	}

	//Check if header contains "WAVE"
	if(stream.readRawData(data4, 4) < 4 || QString(data4).toLower() != "wave")
	{
		return false;
	}

	//Check if header contains "fmt "
	if(stream.readRawData(data4, 4) < 4 || QString(data4).toLower() != "fmt ")
	{
		return false;
	}

	//Check if data is PCM
	stream.skipRawData(4);
	if(stream.readRawData(data2, 2) < 2 || data2[0] != 1)
	{
		return false;
	}

	//Check channels
	short channels;
	if(stream.readRawData(data2, 2) < 2 || (channels = toShort(data2)) <= 0)
	{
		return false;
	}
	format.setChannelCount(channels);

	//Check sample rate
	int sampleRate;
	if(stream.readRawData(data4, 4) < 4 || (sampleRate = toInt(data4)) <= 0)
	{
		return false;
	}
	format.setSampleRate(sampleRate);

	//Check sample size
	stream.skipRawData(6);
	int sampleSize;
	if(stream.readRawData(data2, 2) < 2 || (sampleSize = toShort(data2)) <= 0)
	{
		return false;
	}
	format.setSampleSize(sampleSize);

	content.setSamples((chunkSize - 36) / (format.sampleSize() / 8));
	content.setFileSize(chunkSize + 8);
	content.setHeaderSize(44);
	content.setTrailerSize(0);
	content.setDataSize(content.fileSize() - 44);

	format.setSampleType(QAudioFormat::SignedInt);	

	return true;
}

void QWaveCodec::createHeader(QByteArray &header, const QCodecFormat &format, QCodecContent &content)
{
	QDataStream stream((QByteArray*) &header, QIODevice::WriteOnly);

	if(format.byteOrder() == QAudioFormat::LittleEndian)
	{
		stream.setByteOrder(QDataStream::LittleEndian);
		stream << qint8('R') << qint8('I') << qint8('F') << qint8('F');
	}
	else if(format.byteOrder() == QAudioFormat::BigEndian)
	{
		stream.setByteOrder(QDataStream::BigEndian);
		stream << qint8('R') << qint8('I') << qint8('F') << qint8('X');
	}
	stream << int(content.fileSize() - 8);
	stream << qint8('W') << qint8('A') << qint8('V') << qint8('E');
	
	stream << qint8('f') << qint8('m') << qint8('t') << qint8(' ');
	stream << int(16);
	stream << short(1);
	stream << short(format.channelCount());
	stream << int(format.sampleRate());
	stream << int(format.sampleRate() * format.channelCount() * format.sampleSize() / 8);
	stream << short(format.channelCount() * format.sampleSize() / 8);
	stream << short(format.sampleSize());

	stream << qint8('d') << qint8('a') << qint8('t') << qint8('a');
	stream << int(content.samples() * format.sampleSize() / 8);
}

bool QWaveCodec::initializeDecode()
{
	mError = QAbstractCodec::NoError;
	return true;
}

bool QWaveCodec::finalizeDecode()
{
	return true;
}

void QWaveCodec::decode(const void *input, int size)
{
	qbyte *output = new qbyte[size];
	memcpy(output, input, size);
	emit decoded(new QAudioChunk(output, size / (mInputFormat.sampleSize() / 8), size));
}

bool QWaveCodec::initializeEncode()
{
	int inSize = mInputFormat.sampleSize();
	int outSize = mOutputFormat.sampleSize();
	QAudioFormat::SampleType inType = mInputFormat.sampleType();
	QAudioFormat::SampleType outType = mOutputFormat.sampleType();

	if(!(inSize == 8 || inSize == 16 || inSize == 32) && !(outSize == 8 || outSize == 16 || outSize == 32))
	{
		mError = QAbstractCodec::SampleSizeError;
		return false;
	}

	if(inType == QAudioFormat::Unknown || outType == QAudioFormat::Unknown)
	{
		mError = QAbstractCodec::SampleTypeError;
		return false;
	}

	if(!mConverter.initialize(mInputFormat, mOutputFormat))
	{
		mError = QAbstractCodec::InitializationError;
		return false;
	}

	mError = QAbstractCodec::NoError;
	return true;
}

bool QWaveCodec::finalizeEncode()
{
	return true;
}

void QWaveCodec::encode(const void *input, int samples)
{
	int bytes;
	qbyte *output = (qbyte*) mConverter.convert(input, samples, bytes);
	emit encoded(new QAudioChunk(output, samples, bytes));
}

QAbstractCodec::Error QWaveCodec::initializeLibrary()
{
	return QAbstractCodec::NoError;
}

short QWaveCodec::toShort(char data[])
{
	short result = 0;
	memcpy(&result, data, 2);
	return result;
}

int QWaveCodec::toInt(char data[])
{
	int result = 0;
	memcpy(&result, data, 4);
	return result;
}
