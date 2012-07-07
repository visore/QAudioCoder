#include <qwavecoder.h>
#include <qsamplesizeconverter.h>
#include <QDataStream>

QWaveCoder::QWaveCoder()
	: QAbstractCoder()
{
	mName = "Wave";
	addFileName("");
}

QAbstractCoder::Error QWaveCoder::load()
{
	return QAbstractCoder::NoError;
}

QAbstractCoder::Error QWaveCoder::load(QString filePath)
{
	return QAbstractCoder::NoError;
}

bool QWaveCoder::unload()
{
	return true;
}

QAbstractCoder::Header QWaveCoder::inspectHeader(const QByteArray &header, QExtendedAudioFormat &format, QCodecContent &content)
{
	QDataStream stream((QByteArray*) &header, QIODevice::ReadOnly);
	char data2[2];
	char data4[4];

	//Check if header contains "RIFF"
	if(stream.readRawData(data4, 4) < 4)
	{
		return QAbstractCoder::InvalidHeader;
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
		return QAbstractCoder::InvalidHeader;
	}

	//Check chunk size
	int chunkSize;
	if(stream.readRawData(data4, 4) < 4 || (chunkSize = toInt(data4)) <= 0)
	{
		return QAbstractCoder::InvalidHeader;
	}

	//Check if header contains "WAVE"
	if(stream.readRawData(data4, 4) < 4 || QString(data4).toLower() != "wave")
	{
		return QAbstractCoder::InvalidHeader;
	}

	//Check if header contains "fmt "
	if(stream.readRawData(data4, 4) < 4 || QString(data4).toLower() != "fmt ")
	{
		return QAbstractCoder::InvalidHeader;
	}

	//Check if data is PCM
	stream.skipRawData(4);
	if(stream.readRawData(data2, 2) < 2 || data2[0] != 1)
	{
		return QAbstractCoder::InvalidHeader;
	}

	//Check channels
	short channels;
	if(stream.readRawData(data2, 2) < 2 || (channels = toShort(data2)) <= 0)
	{
		return QAbstractCoder::InvalidHeader;
	}
	format.setChannelCount(channels);

	//Check sample rate
	int sampleRate;
	if(stream.readRawData(data4, 4) < 4 || (sampleRate = toInt(data4)) <= 0)
	{
		return QAbstractCoder::InvalidHeader;
	}
	format.setSampleRate(sampleRate);

	//Check sample size
	stream.skipRawData(6);
	int sampleSize;
	if(stream.readRawData(data2, 2) < 2 || (sampleSize = toShort(data2)) <= 0)
	{
		return QAbstractCoder::InvalidHeader;
	}
	format.setSampleSize(sampleSize);

	content.setSamples((chunkSize - 36) / (format.sampleSize() / 8));
	content.setFileSize(chunkSize + 8);
	content.setHeaderSize(44);
	content.setTrailerSize(0);
	content.setDataSize(content.fileSize() - 44);

	format.setSampleType(QAudioFormat::SignedInt);	

	return QAbstractCoder::ValidHeader;
}

void QWaveCoder::createHeader(QByteArray &header, const QExtendedAudioFormat &format, QCodecContent &content)
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

bool QWaveCoder::initializeDecode()
{
	mError = QAbstractCoder::NoError;
	return true;
}

bool QWaveCoder::finalizeDecode()
{
	return true;
}

void QWaveCoder::decode(const void *input, int size)
{
	qbyte *data = new qbyte[size];
	memcpy(data, input, size);
	emit decoded(new QSampleArray(data, size, size / (mInputFormat.sampleSize() / 8)));
}

bool QWaveCoder::initializeEncode()
{
	int inSize = mInputFormat.sampleSize();
	int outSize = mOutputFormat.sampleSize();
	QAudioFormat::SampleType inType = mInputFormat.sampleType();
	QAudioFormat::SampleType outType = mOutputFormat.sampleType();

	if(!(inSize == 8 || inSize == 16 || inSize == 32) && !(outSize == 8 || outSize == 16 || outSize == 32))
	{
		mError = QAbstractCoder::SampleSizeError;
		return false;
	}

	if(inType == QAudioFormat::Unknown || outType == QAudioFormat::Unknown)
	{
		mError = QAbstractCoder::SampleTypeError;
		return false;
	}

	if(!mConverter.initialize(mInputFormat, mOutputFormat))
	{
		mError = QAbstractCoder::InitializationError;
		return false;
	}

	mError = QAbstractCoder::NoError;
	return true;
}

bool QWaveCoder::finalizeEncode()
{
	return true;
}

void QWaveCoder::encode(const void *input, int samples)
{
	int bytes;
	char *output = (char*) mConverter.convert(input, samples, bytes);
	emit encoded(new QSampleArray(output, bytes, samples));
}

QAbstractCoder::Error QWaveCoder::initializeLibrary()
{
	return QAbstractCoder::NoError;
}

short QWaveCoder::toShort(char data[])
{
	short result = 0;
	memcpy(&result, data, 2);
	return result;
}

int QWaveCoder::toInt(char data[])
{
	int result = 0;
	memcpy(&result, data, 4);
	return result;
}
