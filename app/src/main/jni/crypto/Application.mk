NDK_PROJECT_PATH := $(shell pwd)
APP_BUILD_SCRIPT := $(NDK_PROJECT_PATH)/Android.mk
APP_PLATFORM := android-18
APP_STL := gnustl_static
APP_ABI := armeabi
APP_CPPFLAGS := -std=c++11
