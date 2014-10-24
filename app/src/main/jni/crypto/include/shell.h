#ifndef __JNI_NDKLIBS_SYSTEM_H__
#define __JNI_NDKLIBS_SYSTEM_H__

#include <jni.h>

namespace shell
{

class Shell
{
public:
    static bool execCmd(const char *cmd);
    static jboolean execCmd(JNIEnv *env, jobject, jstring javaCmd);
    static void registerMethods(JNIEnv *env);
};

}

#endif
