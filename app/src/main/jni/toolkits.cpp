
#include <toolkits.h>

#include "log.h"

namespace toolkits
{

jbyteArray Toolkits::getByteArray(JNIEnv *env, const char *buf, int len)
{
    jbyteArray byteArray = env->NewByteArray(len);
    const jbyte *bytes = (const jbyte *)buf;
    env->SetByteArrayRegion(byteArray, 0, len, bytes);
    return byteArray;
}

jcharArray Toolkits::getCharArray(JNIEnv *env, const char *buf, int len)
{

    int nlen = len + sizeof(jchar) - 1 / sizeof(jchar);
    /*
    jchar nbuf[nlen + 1];
    memset((void *)nbuf, 0, (nlen + 1) * sizeof(jchar));
    memcpy((void *)nbuf, buf, len);
    */
    const jchar *nbuf = (const jchar *)buf;
    jcharArray chars = env->NewCharArray(nlen);
    env->SetCharArrayRegion(chars, 0, nlen, nbuf);
    return chars;
}

const char *Toolkits::getCharPointer(JNIEnv *env, jcharArray chars)
{
    jchar *buf = env->GetCharArrayElements(chars, JNI_FALSE);

    if (!buf)
	return NULL;

    return (const char *)buf;
    //env->ReleaseCharArrayElements(bytes, buf, JNI_COMMIT);
}

const char *Toolkits::getCharPointer(JNIEnv *env, jbyteArray bytes)
{
    jbyte *buf = env->GetByteArrayElements(bytes, JNI_FALSE);

    if (!buf)
	return NULL;

    return (const char *)buf;
    //env->ReleaseCharArrayElements(bytes, buf, JNI_COMMIT);
}

string Toolkits::getString(JNIEnv *env, jstring javaString)
{
    const char *str = env->GetStringUTFChars(javaString, JNI_FALSE);
    string ret = string(str);
    env->ReleaseStringUTFChars(javaString, str);
    return ret;
}

jstring Toolkits::getJString(JNIEnv *env, string str)
{
    return getJString(env, str.c_str(), str.length());
}

jstring Toolkits::getJString(JNIEnv *env, const char *buf, int len)
{
    /*
    jclass strClass = env->FindClass("Ljava/lang/String;");
    jmethodID ctorID = env->GetMethodID(strClass, "", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(len);
    env->SetByteArrayRegion(bytes, 0, len, (jbyte*)buf);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
    */
    return env->NewStringUTF(buf);
}

/*
jchar *Toolkits::toJChar(JNIEnv *env, const char *buf, int len)
{
    jchar *newbuf = (jchar *)calloc(1, sizeof(jchar) * len);
    for (int i = 0; i < len; ++i)
	memcpy();
}
*/

void Toolkits::printHex(const char *buf, int len)
{
    char tmp[len * 2 + 1];
    memset(tmp, 0, len * 2 + 1);

    for (int i = 0; i < len; ++i)
	sprintf(tmp + i, "%02x ", buf[i]);
}

}
