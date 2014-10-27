#include "jni_native.h"

/*
 * Register native methods for all classes we know about.
 */
int registerNativeMethods(JNIEnv *env,
        const char* className,
        const JNINativeMethod *methods,
        int size)
{
    jclass registerClass = env->FindClass(className);
    env->RegisterNatives(registerClass, methods, size);
    return 1;
}