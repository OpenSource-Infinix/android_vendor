LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = lights.mt6737m
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_RELATIVE_PATH = hw
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES_64 = libc++
LOCAL_MULTILIB = 64
LOCAL_SRC_FILES_64 = arm64/lights.mt6737m.so
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE = lights.mt6737m
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_RELATIVE_PATH = hw
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES = libc++
LOCAL_MULTILIB = 32
LOCAL_SRC_FILES_32 = arm/lights.mt6737m.so
include $(BUILD_PREBUILT)
