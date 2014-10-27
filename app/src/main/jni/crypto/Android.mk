LOCAL_PATH := $(call my-dir)
$(info $(LOCAL_PATH))
include $(CLEAR_VARS)
MY_ROOT_LOCAL_PATH := $(LOCAL_PATH)


include $(MY_ROOT_LOCAL_PATH)/sm4/Android.mk
include $(CLEAR_VARS)

include $(MY_ROOT_LOCAL_PATH)/aes/Android.mk
include $(CLEAR_VARS)

LOCAL_PATH := $(MY_ROOT_LOCAL_PATH)

LOCAL_MODULE := libcryptostatic

LOCAL_SRC_FILES := \
	crypto_api.cpp \
	crypto_apis.cpp \

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/.. \
    $(LOCAL_PATH)/aes \
	$(LOCAL_PATH)/sm4 \
	$(LOCAL_PATH)/include \
    $(LOCAL_PATH)/include/openssl \

LOCAL_CFLAGS := \
	-D_USE_AES_=1

LOCAL_EXPORT_LDLIBS := \
	-llog \

LOCAL_STATIC_LIBRARIES := \
	libaesstatic \
	libsm4static

include $(BUILD_STATIC_LIBRARY)
