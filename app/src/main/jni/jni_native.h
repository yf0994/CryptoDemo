#ifndef _JNI_JNIUTILS_NATIVE_H_
#define _JNI_JNIUTILS_NATIVE_H_

#include <jni.h>

#define CPP_CLASS_TAG "::"

#define NATIVE_METHOD(className, functionName, signature) \
    { #functionName, signature, reinterpret_cast<void*>(className ## _ ## functionName) }

#define CPP_NATIVE_METHOD(functionName, signature, address) \
    { #functionName, signature, reinterpret_cast<void*>(address) }

extern int registerNativeMethods(JNIEnv *env,
        const char* className,
        const JNINativeMethod *methods,
        int size);

#endif



