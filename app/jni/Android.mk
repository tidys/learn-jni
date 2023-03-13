LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := native-lib
LOCAL_SRC_FILES := ../src/main/cpp/native-lib.cpp

LOCAL_LDFLAGS += -Wl,-Bsymbolic
#--unresolved-symbols=ignore-all
LOCAL_CFLAGS := -fPIC

# 静态库
#LOCAL_STATIC_LIBRARIES += cocos_ffmpeg_libavcodec
#LOCAL_STATIC_LIBRARIES += cocos_ffmpeg_libavfilter
#LOCAL_STATIC_LIBRARIES += cocos_ffmpeg_libavformat
#LOCAL_STATIC_LIBRARIES += cocos_ffmpeg_libavutil
#LOCAL_STATIC_LIBRARIES += cocos_ffmpeg_libswresample
#LOCAL_STATIC_LIBRARIES += cocos_ffmpeg_libswscale

# 动态库
LOCAL_SHARED_LIBRARIES += cocos_ffmpeg_libavcodec
LOCAL_SHARED_LIBRARIES += cocos_ffmpeg_libavfilter
LOCAL_SHARED_LIBRARIES += cocos_ffmpeg_libavformat
LOCAL_SHARED_LIBRARIES += cocos_ffmpeg_libavutil
LOCAL_SHARED_LIBRARIES += cocos_ffmpeg_libswresample
LOCAL_SHARED_LIBRARIES += cocos_ffmpeg_libswscale
LOCAL_SHARED_LIBRARIES += cocos_openal
# include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(LOCAL_PATH))
$(call import-module,openal1-19/prebuilt/android)
$(call import-module,ffmpeg3-2/prebuilt/android)
#$(call import-module,ffmpeg4-2/prebuilt/android)
