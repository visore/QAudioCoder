#include <qcommon.h>

QString QCoder::errorString(QCoder::Error error)
{
	if(error == QCoder::NoError)
	{
		return "No error.";
	}
	else if(error == QCoder::InputFileError)
	{
		return "The input file could not be accessed.";
	}
	else if(error == QCoder::OutputFileError)
	{
		return "The output file could not be accessed.";
	}

	else if(error == QCoder::DecoderInitializationError)
	{
		return "The decoder could not be initialized.";
	}
	else if(error == QCoder::DecoderFinalizationError)
	{
		return "The decoder could not be finalized and properly closed.";
	}
	else if(error == QCoder::DecodingError)
	{
		return "The data could not be decoded.";
	}
	
	else if(error == QCoder::EncoderInitializationError)
	{
		return "The encoder could not be initialized.";
	}
	else if(error == QCoder::EncoderFinalizationError)
	{
		return "The encoder could not be finalized and properly closed.";
	}
	else if(error == QCoder::EncodingError)
	{
		return "The data could not be encoded.";
	}

	else if(error == QCoder::UnsupportedCodecError)
	{
		return "The codec is not supported.";
	}
	else if(error == QCoder::UnavailableCodecError)
	{
		return "The codec is supported, but not available.";
	}
	else if(error == QCoder::UnsupportedInputCodecError)
	{
		return "The input codec is not supported.";
	}
	else if(error == QCoder::UnavailableInputCodecError)
	{
		return "The input codec is supported, but not available.";
	}
	else if(error == QCoder::UnsupportedOutputCodecError)
	{
		return "The output codec is not supported.";
	}
	else if(error == QCoder::UnavailableOutputCodecError)
	{
		return "The output codec is supported, but not available.";
	}

	else if(error == QCoder::InputSampleSizeError)
	{
		return "The input format (sample size) is invalid.";
	}
	else if(error == QCoder::InputSampleTypeError)
	{
		return "The input format (sample type) is invalid.";
	}
	else if(error == QCoder::InputSampleRateError)
	{
		return "The input format (sample rate) is invalid.";
	}
	else if(error == QCoder::InputBitrateError)
	{
		return "The input format (bitrate) is invalid.";
	}
	else if(error == QCoder::InputChannelError)
	{
		return "The input format (channels) is invalid.";
	}

	else if(error == QCoder::OutputSampleSizeError)
	{
		return "The output format (sample size) is invalid.";
	}
	else if(error == QCoder::OutputSampleTypeError)
	{
		return "The output format (sample type) is invalid.";
	}
	else if(error == QCoder::OutputSampleRateError)
	{
		return "The output format (sample rate) is invalid.";
	}
	else if(error == QCoder::OutputBitrateError)
	{
		return "The output format (bitrate) is invalid.";
	}
	else if(error == QCoder::OutputChannelError)
	{
		return "The output format (channels) is invalid.";
	}

	return "Unknown error.";
}
