LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = wmt_concurrency
LOCAL_MODULE_CLASS = EXECUTABLES
LOCAL_MODULE_OWNER = mtk
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = eng
LOCAL_SHARED_LIBRARIES = libc++
LOCAL_MULTILIB = 64
LOCAL_SRC_FILES_64 = arm64/wmt_concurrency
include $(BUILD_PREBUILT)
