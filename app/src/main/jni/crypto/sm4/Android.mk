LOCAL_PATH := $(call my-dir)
$(info $(LOCAL_PATH))
#############################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := modulesm4


LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
	$(LOCAL_PATH)/.. \
	$(LOCAL_PATH)/../include

LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)

LOCAL_SRC_FILES := $(LOCAL_PATH)/../libs/armeabi/libsm4crypto.a \

include $(PREBUILT_STATIC_LIBRARY)


##############################################################################




###########################################################################
include $(CLEAR_VARS)

LOCAL_MODULE := libsm4static


LOCAL_SRC_FILES := \
	sm4_api.cpp

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/.. \
	$(LOCAL_PATH)/../include

LOCAL_EXPORT_C_INCLUDES := \
	$(LOCAL_PATH)


LOCAL_STATIC_LIBRARIES :=  \
    modulesm4 \

include $(BUILD_STATIC_LIBRARY)
#######################################################################