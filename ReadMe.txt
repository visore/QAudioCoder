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
codec libraries. If these libraries are availbale the functionality is being made public
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
4. package: create a DEB RPM or STGZ package (if possible - Linux only)

Linux example: "sh build/linux/linux-build-32bit configure build install package"

You can change the build script by adjusting the following variables in the script:
1. code_directory: The directory of the source code.
2. build_directory: The directory used to build QAudioCoder
3. install_directory: The location to install QAudioCoder
4. qt_directory: The directory of the Qt desktop build (contains a bin and lib directory)
5. mingw_directory: The directory of the MinGW bin directory under Windows.


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

Additionaly the following OS-specific paths are searched:

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
2. MP3: The Lame tage, an extension of the Xing header, is used for MP3 headers.
3. FLAC: The default Flac headers are used.

==========================================================================================
                                      The Main Class
==========================================================================================

QAudioCoder is the interface that should be used for all transformations.

1.	QFourierTransformer(int size = -1, QString functionName = "");

	Constructor with optional parameters.

	The first parameter specifies the fixed size of the FFT. The default is -1 which will
	result in a slower variable-sized FFT.
	The second parameter specifies the window function to use. By default a rectangular
	window will be used.
   
2.	Initialization setSize(int size);

	Changes the size to one of sizes given in the list above. This is the same as
	the parameter in the constructor. Can be changed during runtime.
   
	If the size is one of the default fixed sizes, FixedSize will be returned. If the
	size is not in the default list, but still a valid FFT size (power of 2),
	VariableSize will be returned. If the size is an invalid FFT size, InvalidSize is
	returned.

3.	bool setWindowFunction(QString functionName);

	Sets the window function to be used. If this function is never called, nor a name
	passed to the constructor, a rectangular window will be used, which by default will be
	NULL, and not have any changes on the input data.

4.	QStringList windowFunctions();

	Returns a list of strings for all the supported window functions.
		
5.	void forwardTransform(float *input, float *output, QWindower *windower);

	Calculates the FFT of the input samples and stores them in output. The output array
	must be allocated beforehand and has the same size as the input array.

	If a window function is required, you can pass one to the function. The input array
	will automatically be adjusted according to the window function. If NULL is passed
	no windowing will be done.

6.	void inverseTransform(float input[], float output[]);

	Calculates the inverse FFT from the input and stores it as real samples in the output
	array. The output array must be allocated beforehand with the same size as input.
		
7.	void transform(float input[], float output[], QWindower *windower = NULL,
	Direction direction = QFourierTransformer::Forward);

	Calls one of the function in 5 or 6 above, depending on the direction parameter.
	This function is generally not recommended since it uses an extra if-statement.
	Rather use 3 or 4 instead.

8.	void rescale(float input[]);

	After the inverse FFT was calculated, you have to rescale the values of the samples.

9.	void conjugate(float input[]);

	Conjugates the imaginary part of the input. Hence the imaginary part's sign is changed
	Eg: input[length/2 + 1] = -input[length/2 + 1]

10.	QComplexVector toComplex(float input[]);

	Converts the FFT calculated with 6 or 7 above to a QVector of complex numbers
	as explained in the previous section.

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

