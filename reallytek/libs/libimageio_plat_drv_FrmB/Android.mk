LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = libimageio_plat_drv_FrmB
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES_64 = libdpframework libcamdrv_FrmB libm4u libc++
LOCAL_MULTILIB = 64
LOCAL_SRC_FILES_64 = arm64/libimageio_plat_drv_FrmB.so
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE = libimageio_plat_drv_FrmB
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES = libdpframework libcamdrv_FrmB libm4u libc++
LOCAL_MULTILIB = 32
LOCAL_SRC_FILES_32 = arm/libimageio_plat_drv_FrmB.so
include $(BUILD_PREBUILT)
