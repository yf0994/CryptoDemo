#include <jni.h>
#include "crypto_helper.h"
#include "log.h"
namespace crypto
{
    class CryptoModule
    {
    public:
        CryptoModule(){}
        ~CryptoModule(){}
        void onLoad(JavaVM *vm,JNIEnv *env,void *reserved);
    };
}