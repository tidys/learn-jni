LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := native-lib
LOCAL_SRC_FILES := ../src/main/cpp/native-lib.cpp

include $(BUILD_SHARED_LIBRARY)
# include $(BUILD_STATIC_LIBRARY)