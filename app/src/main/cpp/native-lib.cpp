#include <jni.h>
#include <string>
#include <math.h>

extern "C" {
#include <libavutil/version.h>
#include <libavformat/avformat.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
}
using namespace std;

string checkError(char *file, int line) {
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        char tmp[255];
        sprintf(tmp, "error on line:%d", line);
        return string(tmp) + "\n";
    }
    return string("");
}

#define CHECHERROR() checkError(__FILE__, __LINE__);

extern "C" JNIEXPORT jstring
JNICALL Java_com_example_learnndk_MainActivity_testFFMpeg(JNIEnv *env, jobject) {
    std::string tips = "";
    av_register_all();
    avcodec_register_all();
    AVFormatContext *avFormatContext = avformat_alloc_context();
    if (avFormatContext) {
        tips += "call ffmpeg avformat_alloc_context\n";
    }
    char *file = "gaga.mp4";
    int ret = avformat_open_input(&avFormatContext, file, nullptr, nullptr);
    if (ret != 0) {
        char buf[255];
        av_strerror(ret, buf, 255);
        char tmp[255];
        sprintf(tmp, "avformat_open_input failed %d: %s\n", ret, buf);
        tips += string(file) + "\n";
        tips += string(tmp);
    }
    return env->NewStringUTF(tips.c_str());
}

extern "C" JNIEXPORT jstring

JNICALL Java_com_example_learnndk_MainActivity_testOpenAL(JNIEnv *env, jobject) {
    string tips = "";
    ALCdevice *pDevice = alcOpenDevice(nullptr);
    ALCcontext *pContext = alcCreateContext(pDevice, nullptr);
    alcMakeContextCurrent(pContext);
    ALuint _source;
    alGenSources(1, &_source);
    alSourcei(_source, AL_LOOPING, AL_TRUE);
    if (pDevice) {
        tips += "call openal alcOpenDevice\n";
    }
    tips += CHECHERROR();
    char *data = new char[1000];
    float max = CHAR_MAX / 4;
    float rad = 0;

    for (int i = 0; i < 1000; i++) {
        data[i] = (max * cosf(rad));
        rad += 1.f;
    }

    ALuint buffer;
    alGenBuffers(1, &buffer);
    tips += CHECHERROR();

    alBufferData(buffer, AL_FORMAT_STEREO16, data, 1000, 500);
//    alSourceQueueBuffers(_source, 1, &buffer);
    tips += CHECHERROR();

    alSourcePlay(_source);
}

extern "C" JNIEXPORT jstring

JNICALL Java_com_example_learnndk_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string tips = "Hello from C++！\n";
    int major = LIBAVUTIL_VERSION_MAJOR;
    if (major == 56) {
        tips += "LIBAVUTIL_VERSION_MAJOR: 56";
    }
    return env->NewStringUTF(tips.c_str());
}
