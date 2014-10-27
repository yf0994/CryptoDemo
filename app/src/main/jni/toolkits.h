
#ifndef __JNI_TOOLKITS_H__
#define __JNI_TOOLKITS_H__

#include <string>

#include <jni.h>

using std::string;

namespace toolkits
{

class Toolkits
{
public:
    static jbyteArray getByteArray(JNIEnv *env, const char *buf, int len);
    static const char *getCharPointer(JNIEnv *env, jcharArray chars);
    static const char *getCharPointer(JNIEnv *env, jbyteArray bytes);
    static jcharArray getCharArray(JNIEnv *env, const char *buf, int len);
    static string getString(JNIEnv *env, jstring javaString);
    static jstring getJString(JNIEnv *env, string str);
    static jstring getJString(JNIEnv *env, const char *buf, int len);
    
    static void printHex(const char *buf, int len);
};


}

#endif
