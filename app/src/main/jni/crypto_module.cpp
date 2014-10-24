#include "crypto_module.h"
#include <stdio.h>

namespace crypto
{
    void CryptoModule::onLoad(JavaVM *vm,JNIEnv *env,void *reserved)
    {
        crypto::CryptoHelper::registerCryptpHelper(env);
    }

}


jint JNI_OnLoad(JavaVM *vm,void *reserved)
{
    JNIEnv *env = NULL;
    jint version = vm -> GetEnv((void **)&env,JNI_VERSION_1_4);
    crypto::CryptoModule *module = new crypto::CryptoModule;
    module -> onLoad(vm,env,reserved);
    delete module;
    return JNI_VERSION_1_4;

}