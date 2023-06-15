#include <jni.h>
#include <string>
#include <math.h>
#include "assert.h"
#include "android/asset_manager.h"
#include "android/asset_manager_jni.h"
#include "vector"
#include "leak-tracer/include/MemoryTrace.hpp"
#include <android/log.h>
extern "C" {
#include <libavutil/version.h>
#include <libavformat/avformat.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
}
using namespace std;

char *getErrorString(ALenum err) {
    switch (err) {
        case AL_NO_ERROR:
            return "AL_NO_ERROR";
        case AL_INVALID_NAME:
            return "AL_INVALID_NAME";
        case AL_INVALID_ENUM:
            return "AL_INVALID_ENUM";
        case AL_INVALID_VALUE:
            return "AL_INVALID_VALUE";
        case AL_INVALID_OPERATION:
            return "AL_INVALID_OPERATION";
        case AL_OUT_OF_MEMORY:
            return "AL_OUT_OF_MEMORY";
        default:
            return "un know error";
    }
}

string checkError(const char *file, int line) {
    ALenum err = alGetError();
    if (err != AL_NO_ERROR) {
        char tmp[255];
        sprintf(tmp, "error on line %d: %s", line, getErrorString(err));
        return string(tmp) + "\n";
    }
    return string("");
}

#define CHECHERROR() checkError(__FILE__, __LINE__);

extern "C" JNIEXPORT jstring
JNICALL
Java_com_example_learnndk_MainActivity_testVMPath(JNIEnv *env, jobject activity, jstring vmpath) {
    std::string tips = "";
    av_register_all();
    avcodec_register_all();
    AVFormatContext *avFormatContext = avformat_alloc_context();
    if (avFormatContext) {
        tips += "call ffmpeg avformat_alloc_context\n";
    }
    // file:///android_asset 没有效果
//    char *file = "file:///android_asset/gaga.mp4";
    const char *file = env->GetStringUTFChars(vmpath, 0);
    tips += string(file) + "\n";
    int ret = avformat_open_input(&avFormatContext, file, nullptr, nullptr);
    if (ret != 0) {
        char buf[255];
        av_strerror(ret, buf, 255);
        char tmp[255];
        sprintf(tmp, "avformat_open_input failed %d: %s\n", ret, buf);
        tips += string(tmp);
    } else {
        tips += "avformat_open_input success!\n";
    }
    return env->NewStringUTF(tips.c_str());
}

extern "C" JNIEXPORT jstring
JNICALL Java_com_example_learnndk_MainActivity_testFFMpegJNI(JNIEnv *env, jobject, jobject obj) {
    string tips = "";
    AAssetManager *mgr = AAssetManager_fromJava(env, obj);
    if (mgr != nullptr) {
        AAsset *asset = AAssetManager_open(mgr, "gaga.mp4", AASSET_MODE_UNKNOWN);
        if (asset) {
            tips = "open gaga.mp4 asset";
        } else {
            tips = "no gaga.mp4 asset";
        }
    }
    return env->NewStringUTF(tips.c_str());
}
extern "C" JNIEXPORT jstring
JNICALL Java_com_example_learnndk_MainActivity_testFFMpeg(JNIEnv *env, jobject, jstring mp4File) {
    std::string tips = "";
    av_register_all();
    avcodec_register_all();
    AVFormatContext *avFormatContext = avformat_alloc_context();
    if (avFormatContext) {
        tips += "call ffmpeg avformat_alloc_context\n";
    }
    // file:///android_asset 没有效果
//    char *file = "file:///android_asset/gaga.mp4";
    const char *file = env->GetStringUTFChars(mp4File, 0);
    tips += string(file) + "\n";
    int ret = avformat_open_input(&avFormatContext, file, nullptr, nullptr);
    if (ret != 0) {
        char buf[255];
        av_strerror(ret, buf, 255);
        char tmp[255];
        sprintf(tmp, "avformat_open_input failed %d: %s\n", ret, buf);
        tips += string(tmp);
    } else {
        tips += "avformat_open_input success!\n";
    }
    return env->NewStringUTF(tips.c_str());
}
extern "C" JNIEXPORT jstring
JNICALL Java_com_example_learnndk_MainActivity_testFileApi(JNIEnv *env, jobject) {
    string file = "assets/1.txt";
    string tips = file + "\n";
    FILE *fp = fopen(file.c_str(), "rb");
    if (fp) {
        auto descriptor = fileno(fp);
        tips += "has size";
    } else {
        tips += "open failed";
    }
    return env->NewStringUTF(tips.c_str());
}


bool isInitOpenAL = false;
ALuint source;
ALuint buffer;

extern "C" JNIEXPORT jstring

JNICALL Java_com_example_learnndk_MainActivity_testOpenAL(JNIEnv *env, jobject) {
    string tips = "";

    if (!isInitOpenAL) {
        isInitOpenAL = true;
        ALCdevice *pDevice = alcOpenDevice(nullptr);
        if (pDevice) {
            tips += "call openal alcOpenDevice success\n";
        } else {
            tips += "call openal alOpenDevices failed\n";
        }
        ALCcontext *pContext = alcCreateContext(pDevice, nullptr);
        alcMakeContextCurrent(pContext);
        alGenSources(1, &source);
        alSourcei(source, AL_LOOPING, AL_FALSE);
        tips += CHECHERROR();

        char *data = new char[1000];
        float max = CHAR_MAX / 4;
        float rad = 0;

        for (int i = 0; i < 1000; i++) {
            data[i] = (max * cosf(rad));
            rad += 1.f;
        }

        alGenBuffers(1, &buffer);
        tips += CHECHERROR();
        alBufferData(buffer, AL_FORMAT_STEREO16, data, 1000, 2000);
        tips += CHECHERROR();
        delete[] data;
    }
    // clean processed buffer
    ALint process = 0;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &process);

    while ((process--) > 0) {
        ALuint bufferID;
        alSourceUnqueueBuffers(source, 1, &bufferID);
        // don't delete buffer, we can use again
//        alDeleteBuffers(1, &bufferID);
    }
    // push buffer
    alSourceQueueBuffers(source, 1, &buffer);
    tips += CHECHERROR();
    alSourcePlay(source);
    tips += "play ...\n";
    return env->NewStringUTF(tips.c_str());
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

int i = 0;
std::vector<void *> arr;


extern "C" JNIEXPORT jstring
JNICALL Java_com_example_learnndk_MainActivity_leakFree(JNIEnv *env, jobject /* this */) {
    i = 0;
    char tmp[255];
    for (auto m: arr) {
        free(m);
    }
    arr.clear();
    sprintf(tmp, "%s %d\n", "leak test ", arr.size());
    return env->NewStringUTF(tmp);
}

extern "C" JNIEXPORT jstring
JNICALL Java_com_example_learnndk_MainActivity_leakTest(JNIEnv *env, jobject /* this */) {
    i++;
    char tmp[255];
    void *p = malloc(1024 * 1024 * 10);
    arr.push_back(p);
    sprintf(tmp, "%s %d\n", "leak test ", arr.size());
    return env->NewStringUTF(tmp);
}

extern "C" JNIEXPORT void
JNICALL Java_com_example_learnndk_MainActivity_leakStartMonitor(JNIEnv *env, jobject /* this */) {
    leaktracer::MemoryTrace::GetInstance().startMonitoringAllThreads();
}
extern "C" JNIEXPORT void
JNICALL Java_com_example_learnndk_MainActivity_leakStopMonitor(JNIEnv *env, jobject /* this */) {
    leaktracer::MemoryTrace::GetInstance().stopAllMonitoring();
}
extern "C" JNIEXPORT void
JNICALL Java_com_example_learnndk_MainActivity_leakReport(JNIEnv *env, jobject /* this */,
                                                          jstring filePath) {
    const char *path = env->GetStringUTFChars(filePath, JNI_FALSE);;
    leaktracer::MemoryTrace::GetInstance().writeLeaksToFile(path);
    env->ReleaseStringUTFChars(filePath, path);
}
extern "C" JNIEXPORT void
JNICALL Java_com_example_learnndk_MainActivity_testPrint(JNIEnv *env, jobject /* this */) {
    __android_log_print(ANDROID_LOG_INFO, "TAG", "Hello, world!");
}

