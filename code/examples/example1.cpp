#include <qaudiocoder.h>


#include <iostream>
using namespace std;

#include <QString>
#include <QFile>

int main()
{

QCodecFormat format;
format.setChannelCount(2);
format.setSampleRate(44100);
format.setSampleSize(16);
format.setBitrate(128);

QAudioCoder coder;
coder.convert("/home/visore/a.wav", "/home/visore/meee.flac", format);

signed int g = 40000;
unsigned int a = g;



	/*int read, write;

    FILE *pcm = fopen("/home/visore/a.wav", "rb");
    FILE *mp3 = fopen("file.mp3", "wb");

    const int PCM_SIZE = 8192;
    const int MP3_SIZE = 8192;

    short int pcm_buffer[PCM_SIZE*2];
    unsigned char mp3_buffer[MP3_SIZE];

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, 44100);
    lame_set_VBR(lame, vbr_default);
    lame_init_params(lame);

    do {
        read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
cout<<read<<" "<<2*sizeof(short int)<<endl;
        if (read == 0)
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        else
            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
        fwrite(mp3_buffer, write, 1, mp3);
    } while (read != 0);

    lame_close(lame);
    fclose(mp3);
    fclose(pcm);

    return 0;*/

}
