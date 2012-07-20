==========================================================================================
==========================================================================================
******************************************************************************************

                                       QAudioCoder

******************************************************************************************
==========================================================================================
==========================================================================================


A Qt-based C++ library for audio decoding, encoding and audio file conversion.

Last Release: 20 July 2012
Latest version: 0.1.0
Developer: Christoph Stallmann, University of Pretoria


==========================================================================================
                                          About
==========================================================================================

QAudioCoder is a Qt library for decoding and encoding raw audio samples. The library also
provides functionality to directly decode or encode audio files and convert between
different formats. On start-up QAudioCoder searches a number of predefined locations for
codec libraries. If these libraries are available the functionality is being made public
through QAudioCoders interface. QAudioCoder includes libresample developed by Dominic
Mazzoni.

==========================================================================================
                                         License
==========================================================================================

QAudioCoder is distributed under the Lesser GNU General Public License (LGPL) version 3
(LGPLv3). Copyright © 2012 Christoph Stallmann, University of Pretoria.

Please refer to License.txt and Copyright.txt for further information.

==========================================================================================
                                      Requirements
==========================================================================================

QAudioCoder requires CMake (2.8.8 or later) for makefile generation and Qt (5.0 or later).
Any native compilers should do, recommended are g++ for Linux/Mac and MinGW for Windows.

==========================================================================================
                                    Codecs & Formats
==========================================================================================

QAudioCoder currently only supports the following sample sizes:

1. 8bit
2. 16bit
3. 32bit

QAudioCoder currently supports the following audio formats:

1. WAVE (always available)
2. MP3 (available if the Lame library is available)
3. FLAC (available if the Flac library is available)

==========================================================================================
                                        Compiling
==========================================================================================

The simplest way of compiling QAudioCoder is to run the following command:

<sh> build/os/os-build-architecture options

where os is your operating system (Linux, Windows or Mac) and architecture is 32bit or
64bit. You can specify any of the following options in any order:

1. configure: configure cmake
2. build: compile QAudioCoder
3. install: install the library

Linux example: "sh build/linux/linux-build-32bit configure build install package"

Or you can manually build as follows:

With Qt installed in the default location

1. cd code
2. mkdir build
3. cd build
4. cmake ..
5. make

With Qt installed in a custom location

1. cd code
2. mkdir build
3. cd build
4. ccmake ..
5. press 'c', 'c' and then 'g' (change Qt path if needed)
6. make

==========================================================================================
                           Search Paths, File Names & Extensions
==========================================================================================

QAudioCoder will search the following paths:
<current dir> is the calling application's path

1. <current dir>
2. <current dir>/libraries
3. <current dir>/library
4. <current dir>/Libraries
5. <current dir>/Library
6. <current dir>/lib
7. <current dir>/Lib
8. <current dir>/libs
9. <current dir>/Libs

Additionally the following OS-specific paths are searched:

Windows:

1. C:\Program Files
2. C:\Program Files (x86)

Mac:

1. /lib
2. /lib64
3. /usr/lib
4. /usr/lib64
5. /usr/local/lib
6. /usr/local/lib64

Linux:

1. /lib
2. /lib64
3. /usr/lib
4. /usr/lib64
5. /usr/local/lib
6. /usr/local/lib64
7. /usr/lib/i386-linux-gnu
8. /usr/lib/x86_64-linux-gnu

In every of these directories QAudioCoder will search for the library:
<path> is all of the above directories
<name> is the name of the library
<extension> is the library file extension

1. <path>/<name>.<extension>
2. <path>/lib<name>.<extension>
3. <path>/<name>/<name>.<extension>
4. <path>/<name>/lib<name>.<extension>
5. <path>/lib<name>/<name>.<extension>
6. <path>/lib<name>/lib<name>.<extension>

The following names are used:

Lame library:

1. mp3lame
2. lame;

Flac library:

1. FLAC
2. flac
3. Flac

The following extensions are used:

1. <no extension> (All systems)
2. .a (All systems)
3. .lib (All systems)
4. .dll (Windows only)
5. .so (Linux and Mac)
9. .dylib (Mac only)

If the library is located anywhere else, the following functions can be used:

void QAudioCoder::addSearchPath(QString path);
void QAudioCoder::addFileName(QString coder, QString name);
void QAudioCoder::addFileExtension(QString coder, QString extension);

==========================================================================================
                                          Usage
==========================================================================================

There are three examples under the example directory.
You can execute the examples from the directory by using the command:
./<name>

The following examples are available:

1. play: Open an audio file, decode it and play it to the default output
   device.
2. record: Record audio from the default input device, encode it and save it to a
   file.
3. convert: Convert and audio file to another format.

==========================================================================================
                                          Headers
==========================================================================================

1. WAVE: The default 44-byte RIFF-WAVE header is used. Currently only raw PCM as WAVE data
   is allowed. Any other formats are not supported.
2. MP3: The Lame tag, an extension of the Xing header, is used for MP3 headers.
3. FLAC: The default Flac headers are used.

==========================================================================================
                                      The Main Class
==========================================================================================

QAudioCoder is the interface that should be used for all decoding, encoding and
conversions. See the examples directory for advanced illustrations.


	signals:

		
		void progressed(qreal percentage);
		void finished();

	private slots:

		void setError(QCoder::Error error);

	public:

1.	QAudioCoder()

	Constructor for creating a QAudioCoder object.

2.	void failed(QCoder::Error error)

	Signal emitted if the processing failed. The following errors are emitted:

		1.	NoError - No error
		2.	UnknownError - Unknown error
		3.	InputFileError - The input file could not be accessed
		4.	OutputFileError - The output file could not be accessed
		5.	DecoderInitializationError - Decoder could not be initialized
		6.	EncoderInitializationError - Encoder could not be initialized
		7.	DecoderFinalizationError - Decoder could not be finalized and closed
		8.	EncoderFinalizationError - Encoder could not be finalized and closed
		9.	DecodingError - The provided data could not be decoded
		10.	EncodingError - The provided data could not be encoded
		11.	LibraryFileError - The codec library could not be accessed
		12.	LibraryVersionError - The codec library has an incompatible version
		13.	UnsupportedCodecError - The codec is not supported
		14.	UnavailableCodecError - The codec is supported, but there is a problem with
									the supporting library 
		15.	UnsupportedInputCodecError - The same as 13, but focuses on the input data
		16.	UnavailableInputCodecError - The same as 14, but focuses on the input data
		17.	UnsupportedOutputCodecError - The same as 13, but focuses on the output data
		18.	UnavailableOutputCodecError - The same as 14, but focuses on the output data
		19.	InputSampleSizeError - The input sample size is not valid
		20.	InputSampleTypeError - The input sample type is not valid
		21.	InputSampleRateError - The input sample rate is not valid
		22.	InputBitrateError - The input bitrate is not valid
		23.	InputChannelError - The input channel count is not valid
		24.	OutputSampleSizeError - The output sample size is not valid
		25.	OutputSampleTypeError - The output sample type is not valid
		26.	OutputSampleRateError - The output sample rate is not valid
		27.	OutputBitrateError - The output bitrate is not valid
		28.	OutputChannelError - The output channel count is not valid

3.	QCoder::Error error()

	Returns the error code from 2.

4.	QString errorString()

	Returns a human-readable string for the error codes above.

5.	void addSearchPath(QString path)

	Add an additional location to search for the libraries.

	Eg: coder.addSearchPath("/usr/my_custom_libs");

6.	void addFileName(QString coder, QString name)

	Add an additional name for a library. The first parameter is the codec name and
	the second parameter the new library file name. Please note that QAudioCoder will
	automatically add "lib" to the front and support a number of file extensions.

	Eg: The library name is as follows: libMyCustomFlac.so.0.0.8
	coder.void addFileName("FLAC", "MyCustomFlac")

7.	addFileExtension(QString coder, QString extension)

	Add a custom file extension (other than .lib, .a, .so, .dll, .dylib). Note that
	the extension is without the dot (".").

	Eg: coder.addFileExtension("FLAC", "dllx");

8.	void convert(QString inputFilePath, QString outputFilePath,
					QExtendedAudioFormat outputFormat)

	Converts the input file to an output file which has a given format. The input format
	will automatically be detected from the input file.

9.	void convert(QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output,
					QExtendedAudioFormat outputFormat)

	Convert raw bytes with a given input format to raw bytes of a given output format.
	Note that these are the raw bytes, not the actual samples. The same as 8, except
	that the data is read from and array and not a file. The header should be stripped
	from the data before passing it to this function.

10.	void convert(QString inputFilePath, QByteArray &output,
					QExtendedAudioFormat outputFormat)

	Convert an input file to an output array with a given output format. The output 
	array will contain the output codec header.

11.	void convert(QByteArray &input, QExtendedAudioFormat inputFormat,
					QString outputFilePath, QExtendedAudioFormat outputFormat)

	Convert and input array with a given format to an output array. The input array
	should not have a codec header. The output array will contain the output codec
	header.

12.	void decode(QString inputFilePath, QByteArray &output,
					QExtendedAudioFormat &inputFormat)

	Decode an input file to samples. The format parameter will be adjusted with the
	format retrieved from the file. Do not alter this object while the coder is
	running.

13.	void decode(QByteArray &input, QByteArray &output, QExtendedAudioFormat &inputFormat)

	The same as 12, but the data as read from and array instead of a file. The input
	array should still have the codec header.

14.	void encode(QByteArray &input, QExtendedAudioFormat inputFormat,
					QString outputFilePath, QExtendedAudioFormat outputFormat)

	Encode an input array of samples with a give format to an output file.

15.	void encode(QByteArray &input, QExtendedAudioFormat inputFormat, QByteArray &output,
					QExtendedAudioFormat outputFormat)

	The same as 14, but the encoded data will be saved to an array. The output array
	will contain the codec header.

16.	static QCoderList coders(QAudioManager::Mode mode = QAudioManager::Available)

	A list of all libraries supported or available for encoding/decoding. 
	QAudioManager::Supported means that the coder is supported, regardless if the actual
	library can be found and used. QAudioManager::Available means that the coder is
	supported and that the library can be loaded and used.
	Eg: Lame library, Flac library

17. static QCodecList codecs(QAudioManager::Mode mode = QAudioManager::Available)

	A list of all codecs that are supported or available.
	Eg: WAVE, MP3, FLAC

==========================================================================================
                                         History
==========================================================================================

*******************
   17 July 2012
  Version 0.1.0
*******************
Initial release.

==========================================================================================
                                         Contact
==========================================================================================

QAudioCoder is part of the Visore project:

http://www.visore.org

http://github.com/visore/Visore

http://sourceforge.net/projects/visore

*******************

QAudioCoder (LGPL):

Christoph Stallmann
University of Pretoria
Department of Computer Science

qaudiocoder@visore.org

qaudiocoder@gmail.com

http://github.com/visore/QAudioCoder

http://sourceforge.net/p/qaudiocoder

*******************

libresample (LGPL):

Dominic Mazzoni

dominic@minorninth.com

http://dominic-mazzoni.com

*******************

Lame (LGPL):

http://lame.sourceforge.net

*******************

Flac (Xiph.Org's BSD-like license):

http://flac.sourceforge.net

