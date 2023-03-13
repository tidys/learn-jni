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

JNICALL Java_com_example_learnndk_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++！\n";
    int major = LIBAVUTIL_VERSION_MAJOR;
    if (major == 56) {
        hello += "LIBAVUTIL_VERSION_MAJOR: 56";
    }
    if (avformat_alloc_context()) {
        hello += "call ffmpeg avformat_alloc_context\n";
    }
    ALCdevice *pDevice = alcOpenDevice(nullptr);
    ALCcontext *pContext = alcCreateContext(pDevice, nullptr);
    alcMakeContextCurrent(pContext);
    ALuint _source;
    alGenSources(1, &_source);
    alSourcei(_source, AL_LOOPING, AL_TRUE);
    if (pDevice) {
        hello += "call openal alcOpenDevice\n";
    }
    hello += CHECHERROR();
    char *data = new char[1000];
    float max = CHAR_MAX / 4;
    float rad = 0;

    for (int i = 0; i < 1000; i++) {
        data[i] = (max * cosf(rad));
        rad += 1.f;
    }

    ALuint buffer;
    alGenBuffers(1, &buffer);
    hello += CHECHERROR();

    alBufferData(buffer, AL_FORMAT_STEREO16, data, 1000, 500);
//    alSourceQueueBuffers(_source, 1, &buffer);
    hello += CHECHERROR();

    alSourcePlay(_source);
    return env->NewStringUTF(hello.c_str());
}
