LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = libcamdrv_isp
LOCAL_MODULE_CLASS = STATIC_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .a
LOCAL_PROPRIETARY_MODULE = true
LOCAL_UNINSTALLABLE_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_MULTILIB = 64
LOCAL_SRC_FILES_64 = arm64/libcamdrv_isp.a
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE = libcamdrv_isp
LOCAL_MODULE_CLASS = STATIC_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .a
LOCAL_PROPRIETARY_MODULE = true
LOCAL_UNINSTALLABLE_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_MULTILIB = 32
LOCAL_SRC_FILES_32 = arm/libcamdrv_isp.a
include $(BUILD_PREBUILT)
