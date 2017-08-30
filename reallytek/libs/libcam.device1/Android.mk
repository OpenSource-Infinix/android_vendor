LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = libcam.device1
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES_64 = libcamera_client libcam_mmp libcam_hwutils libcam.utils libcam1_utils libcam.paramsmgr libcam.client libcam.camadapter libmtkcam_fwkutils libcam.halsensor libcamdrv libfeatureio libc++
LOCAL_MULTILIB = 64
LOCAL_SRC_FILES_64 = arm64/libcam.device1.so
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE = libcam.device1
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES = libcamera_client libcam_mmp libcam_hwutils libcam.utils libcam1_utils libcam.paramsmgr libcam.client libcam.camadapter libmtkcam_fwkutils libcam.halsensor libcamdrv libfeatureio libc++
LOCAL_MULTILIB = 32
LOCAL_SRC_FILES_32 = arm/libcam.device1.so
include $(BUILD_PREBUILT)
