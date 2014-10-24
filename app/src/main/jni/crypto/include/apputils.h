#ifndef __JNI_APPUTILS_H__
#define __JNI_APPUTILS_H__

#include <string>

#include <jni.h>

using std::string;

namespace utils
{

class AppUtils
{
public:
    static void setPackageName(string packageName);
    static string getPackageName();
    static void setPackageNameNative(JNIEnv *env, jobject obj, jstring javaPackageName);

    static void setExternalStoragePath(string storagePath);
    static string getExternalStoragePath();
    static void setExternalStoragePathNative(JNIEnv *env, jobject obj, jstring javaExternalStoragePath);

    static void registerAppUtilsMethods(JNIEnv *env);

    static string gPackageName;
    static string gExternalStoragePath;
};

}

#endif
