LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = libcam.iopipe_FrmB
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES_64 = libcam_hwutils libimageio_plat_drv_FrmB libcam_utils libcam.metadata libcam.halsensor libimageio_FrmB libcamdrv_FrmB libdpframework libc++
LOCAL_MULTILIB = 64
LOCAL_SRC_FILES_64 = arm64/libcam.iopipe_FrmB.so
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE = libcam.iopipe_FrmB
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES = libcam_hwutils libimageio_plat_drv_FrmB libcam_utils libcam.metadata libcam.halsensor libimageio_FrmB libcamdrv_FrmB libdpframework libc++
LOCAL_MULTILIB = 32
LOCAL_SRC_FILES_32 = arm/libcam.iopipe_FrmB.so
include $(BUILD_PREBUILT)
