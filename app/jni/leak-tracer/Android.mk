LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := leaktracer
LOCAL_MODULE_FILENAME := libleaktracer
LOCAL_ARM_MODE := arm
LOCAL_SRC_FILES := \
src/MemoryTrace.cpp \
src/AllocationHandlers.cpp 
#LOCAL_CPPFLAGS += -DUSE_BACKTRACE # android not support bakctrace function
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS += -g
LOCAL_CPPFLAGS += -g
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(BUILD_SHARED_LIBRARY)
