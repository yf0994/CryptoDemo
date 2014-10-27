#include <android/log.h>


#define TAG "CryptoModule"


#ifdef __cplusplus
extern "C"
{
#endif


#define LOG_E(...) \
    __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#define LOG_D(...) \
    __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

#define LOG_I(...) \
        __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)




#ifdef __cplusplus
}
#endif



