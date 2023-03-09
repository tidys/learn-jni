LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_MODULE := cocos_ffmpeg_libavcodec
#LOCAL_MODULE_FILENAME := libavcodec
#LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavcodec.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
#include $(PREBUILT_STATIC_LIBRARY)
#
#LOCAL_MODULE := cocos_ffmpeg_libavfilter
#LOCAL_MODULE_FILENAME := libavfilter
#LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavfilter.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
#include $(PREBUILT_STATIC_LIBRARY)
#
#LOCAL_MODULE := cocos_ffmpeg_libavformat
#LOCAL_MODULE_FILENAME := libavformat
#LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavformat.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
#include $(PREBUILT_STATIC_LIBRARY)
#
#LOCAL_MODULE := cocos_ffmpeg_libavutil
#LOCAL_MODULE_FILENAME := libavutil
#LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavutil.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
#include $(PREBUILT_STATIC_LIBRARY)
#
#LOCAL_MODULE := cocos_ffmpeg_libswresample
#LOCAL_MODULE_FILENAME := libswresample
#LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libswresample.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
#include $(PREBUILT_STATIC_LIBRARY)
#
#LOCAL_MODULE := cocos_ffmpeg_libswscale
#LOCAL_MODULE_FILENAME := libswscale
#LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libswscale.a
#LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
#include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ffmpeg_libavcodec
LOCAL_MODULE_FILENAME := libavcodec
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavcodec.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ffmpeg_libavfilter
LOCAL_MODULE_FILENAME := libavfilter
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavfilter.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ffmpeg_libavformat
LOCAL_MODULE_FILENAME := libavformat
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavformat.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ffmpeg_libavutil
LOCAL_MODULE_FILENAME := libavutil
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libavutil.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ffmpeg_libswresample
LOCAL_MODULE_FILENAME := libswresample
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libswresample.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ffmpeg_libswscale
LOCAL_MODULE_FILENAME := libswscale
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libswscale.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../../include
include $(PREBUILT_SHARED_LIBRARY)