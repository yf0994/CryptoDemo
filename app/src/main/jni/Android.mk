LOCAL_PATH := $(call my-dir)

LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
MY_NDK_MODULES_LOCAL_PATH := $(LOCAL_PATH)

include $(all-subdir-makefiles)

LOCAL_PATH := $(MY_NDK_MODULES_LOCAL_PATH)

include $(CLEAR_VARS)

LOCAL_MODULE := testcrypto

LOCAL_SRC_FILES := \
    $(LOCAL_PATH)/crypto_module.cpp \
    $(LOCAL_PATH)/jni_native.cpp \
    $(LOCAL_PATH)/crypto_helper.cpp \
    $(LOCAL_PATH)/toolkits.cpp \


LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
	$(LOCAL_PATH)/crypto \
    $(LOCAL_PATH)/crypto/aes \
	$(LOCAL_PATH)/crypto/sm4 \
	$(LOCAL_PATH)/crypto/include \

LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH) \


LOCAL_EXPORT_LDLIBS := \
	-llog \


LOCAL_STATIC_LIBRARIES := \
	libcryptostatic \

include $(BUILD_SHARED_LIBRARY)
