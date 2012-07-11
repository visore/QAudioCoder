#ifndef QEXTENDEDAUDIOFORMAT_H
#define QEXTENDEDAUDIOFORMAT_H

#include <qaudiocodec.h>

class QExtendedAudioFormat
{

	public:

		enum SampleType
		{
			Unknown = 0,
			SignedInt = 1,
			UnSignedInt = 2,
			Float = 3,
			Double = 4,
			Real = Double
		};

		enum Endian
		{
			BigEndian = 0,
			LittleEndian = 1
		};

		enum BitrateMode
		{
			ConstantBitrate = 0,
			VariableBitrate = 1,
			AverageBitrate = 2
		};

		enum BitrateType
		{
			NormalBitrate = 0,
			MinimumBitrate = 1,
			MaximumBitrate = 2
		};

		/*
			Depended on codec:
			 1. File size might be larger on higher quality, because samples were compressed less and therefore less information loss (typically lossy codecs).
			 2. File size might be smaller on higher quality, because samples were compressed more without information loss - longer execution time (typcially lossless codecs).
		*/
		enum Quality
		{
			InsaneHigh = 0,
			ExtremeHigh = 1,
			VeryHigh = 2,
			High = 3,
			AboveAverage = 4,
			Average = 5,
			BelowAverage = 6,
			Low = 7,
			VeryLow = 8,
			ExtremeLow = 9,

			Maximum = InsaneHigh, //Internal use only
			Minimum = ExtremeLow //Internal use only
		};

		QExtendedAudioFormat();
		QExtendedAudioFormat(const QExtendedAudioFormat &other);
		QExtendedAudioFormat(const QAudioFormat &other);

		QExtendedAudioFormat::SampleType sampleType() const;
		QExtendedAudioFormat::Endian byteOrder() const;
		QExtendedAudioFormat::Quality quality() const;
		QExtendedAudioFormat::BitrateMode bitrateMode() const;
		int bitrate(const QExtendedAudioFormat::BitrateType type = QExtendedAudioFormat::NormalBitrate) const;
		int sampleSize() const;
		int sampleRate() const;
		int channelCount() const;
		int channels() const;
		QAudioCodec* codec() const;
		
		void setSampleType(const QExtendedAudioFormat::SampleType type);
		void setSampleType(const QAudioFormat::SampleType type);
		void setByteOrder(const QExtendedAudioFormat::Endian order);
		void setByteOrder(const QAudioFormat::Endian order);
		void setQuality(const QExtendedAudioFormat::Quality quality);
		void setBitrateMode(const QExtendedAudioFormat::BitrateMode mode);
		void setBitrate(const int rate, const QExtendedAudioFormat::BitrateType type = QExtendedAudioFormat::NormalBitrate);
		void setSampleSize(const int size);
		void setSampleRate(const int rate);
		void setChannelCount(const int channels);
		void setChannels(const int channels);
		void setCodec(QAudioCodec *codec);
		bool setCodec(QString codecName);

	private:

		QExtendedAudioFormat::SampleType mSampleType;
		QExtendedAudioFormat::Endian mByteOrder;
		QExtendedAudioFormat::Quality mQuality;
		QExtendedAudioFormat::BitrateMode mBitrateMode;
		int mNormalBitrate;
		int mMinimumBitrate;
		int mMaximumBitrate;
		int mSampleSize;
		int mSampleRate;
		int mChannelCount;	
		QAudioCodec *mCodec;

};

#endif
