#include <jni.h>
#include <string>
extern "C"{
#include <libavutil/version.h>
#include <libavformat/avformat.h>
}
extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_learnndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    std::string hello = "Hello from C++！";
//    int major=LIBAVUTIL_VERSION_MAJOR;
//    if(major==56){
//        hello="56";
//    }
    if(avformat_alloc_context()){
        hello="call ffmpeg avformat_alloc_context";
    }
    return env->NewStringUTF(hello.c_str());
}
