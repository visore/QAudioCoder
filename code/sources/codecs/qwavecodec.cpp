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

QAbstractCodec::Header QWaveCodec::inspectHeader(const QByteArray &header, QCodecFormat &format, QCodecContent &content)
{
	QDataStream stream((QByteArray*) &header, QIODevice::ReadOnly);
	char data2[2];
	char data4[4];

	//Check if header contains "RIFF"
	if(stream.readRawData(data4, 4) < 4)
	{
		return QAbstractCodec::InvalidHeader;
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
		return QAbstractCodec::InvalidHeader;
	}

	//Check chunk size
	int chunkSize;
	if(stream.readRawData(data4, 4) < 4 || (chunkSize = toInt(data4)) <= 0)
	{
		return QAbstractCodec::InvalidHeader;
	}

	//Check if header contains "WAVE"
	if(stream.readRawData(data4, 4) < 4 || QString(data4).toLower() != "wave")
	{
		return QAbstractCodec::InvalidHeader;
	}

	//Check if header contains "fmt "
	if(stream.readRawData(data4, 4) < 4 || QString(data4).toLower() != "fmt ")
	{
		return QAbstractCodec::InvalidHeader;
	}

	//Check if data is PCM
	stream.skipRawData(4);
	if(stream.readRawData(data2, 2) < 2 || data2[0] != 1)
	{
		return QAbstractCodec::InvalidHeader;
	}

	//Check channels
	short channels;
	if(stream.readRawData(data2, 2) < 2 || (channels = toShort(data2)) <= 0)
	{
		return QAbstractCodec::InvalidHeader;
	}
	format.setChannelCount(channels);

	//Check sample rate
	int sampleRate;
	if(stream.readRawData(data4, 4) < 4 || (sampleRate = toInt(data4)) <= 0)
	{
		return QAbstractCodec::InvalidHeader;
	}
	format.setSampleRate(sampleRate);

	//Check sample size
	stream.skipRawData(6);
	int sampleSize;
	if(stream.readRawData(data2, 2) < 2 || (sampleSize = toShort(data2)) <= 0)
	{
		return QAbstractCodec::InvalidHeader;
	}
	format.setSampleSize(sampleSize);

	content.setSamples((chunkSize - 36) / (format.sampleSize() / 8));
	content.setFileSize(chunkSize + 8);
	content.setHeaderSize(44);
	content.setTrailerSize(0);
	content.setDataSize(content.fileSize() - 44);

	format.setSampleType(QAudioFormat::SignedInt);	

	return QAbstractCodec::ValidHeader;
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
	qbyte *data = new qbyte[size];
	memcpy(data, input, size);
	emit decoded(new QSampleArray(data, size, size / (mDecoderFormat.sampleSize() / 8)));
}

bool QWaveCodec::initializeEncode()
{
	int inSize = mDecoderFormat.sampleSize();
	int outSize = mEncoderFormat.sampleSize();
	QAudioFormat::SampleType inType = mDecoderFormat.sampleType();
	QAudioFormat::SampleType outType = mEncoderFormat.sampleType();

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

	if(!mConverter.initialize(mDecoderFormat, mEncoderFormat))
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
	char *output = (char*) mConverter.convert(input, samples, bytes);
	emit encoded(new QSampleArray(output, bytes, samples));
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
