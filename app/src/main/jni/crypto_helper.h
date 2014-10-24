
#include <stdio.h>
#include <string>
#include <jni.h>

using std::string;
namespace crypto
{
typedef struct DataHead
    {
        uint32_t magic;//isEncrypted
        uint32_t psize;//plain text length
        uint32_t esize;//cliper text length
    } DataHead;

    class CryptoHelper
    {
    public:
        static jbyteArray aes_encrypt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len);
        static jbyteArray aes_decrypt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len);

        static jbyteArray sm4_encrypt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len);
        static jbyteArray sm4_decrpyt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len);

//        static jstring sm3_hash(JNIEnv *env,jclass cls,jbyteArray javaBytes);


        static void registerCryptpHelper(JNIEnv *env);

        static void initDataHead(DataHead *head);
        static DataHead readDataHead(const char *buf,int len);
        static bool isEncrypted(DataHead *head);
    };
}

