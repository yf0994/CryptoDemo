LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libaesstatic
LOCAL_SRC_FILES := \
	aes_api.cpp

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/.. \
	$(LOCAL_PATH)/../include

LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)

LOCAL_EXPORT_LDFLAGS := \
	-L$(LOCAL_PATH)/../libs/$(APP_ABI)

LOCAL_EXPORT_LDLIBS := \
	-lcrypto \
	-llog

include $(BUILD_STATIC_LIBRARY)
