LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE = libaudiocompensationfilter
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES_64 = libcustom_nvram libnvram libnativehelper libaudiocustparam libc++
LOCAL_MULTILIB = 64
LOCAL_SRC_FILES_64 = arm64/libaudiocompensationfilter.so
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE = libaudiocompensationfilter
LOCAL_MODULE_CLASS = SHARED_LIBRARIES
LOCAL_MODULE_OWNER = mtk
LOCAL_MODULE_SUFFIX = .so
LOCAL_PROPRIETARY_MODULE = true
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES = libcustom_nvram libnvram libnativehelper libaudiocustparam libc++
LOCAL_MULTILIB = 32
LOCAL_SRC_FILES_32 = arm/libaudiocompensationfilter.so
include $(BUILD_PREBUILT)
