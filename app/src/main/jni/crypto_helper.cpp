#include "crypto_helper.h"
#include "crypto_apis.h"
#include "crypto_api.h"
#include "log.h"
#include "toolkits.h"
#include "jni_native.h"
#include <jni.h>
#include <stdio.h>
#include <string.h>


#define HEAD_MAGIC_V1 0x0ea8b311

namespace crypto
{
    void initDataHead(DataHead *head)
        {
            head->magic = HEAD_MAGIC_V1;
            head->psize = 0;
            head->esize = 0;
        }

        DataHead readDataHead(const char *buf,int len)
        {
            DataHead head;
            int s = sizeof(DataHead);
            if(len < s)
            {
                return head;
            }
            memset((void *)&head, 0, s);
            memcpy((void *)&head, buf, s);
            return head;
        }

        bool isEncrypted(DataHead *head)
        {
            return head == NULL ? false : head->magic == HEAD_MAGIC_V1;
        }

    jbyteArray CryptoHelper::aes_encrypt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len)
    {
        const char *buf = toolkits::Toolkits::getCharPointer(env, javaBytes);
        if (buf == NULL)
        {
            return NULL;
        }
        DataHead head = readDataHead(buf,len);
        if(isEncrypted(&head))
        {
            return javaBytes;
        }
        crypto::BlockList blockList = crypto::Utils::toBlocks(buf, len);
        char encryptData[len];
        memset(encryptData, 0, len);
        crypto::Api::encryptBlocksTo(blockList,encryptData);
        int size = sizeof(DataHead);
        int count  = len / CRYPTO_BLOCK_SIZE;
        int rest = len % CRYPTO_BLOCK_SIZE;
        if(rest > 0)
        {
            count ++;
        }
        int length = count * CRYPTO_BLOCK_SIZE;
        int total = size + length;
        char * tmpBuf = (char *)calloc(1,total);
        if(!tmpBuf)
        {
            return NULL;
        }
        memset(tmpBuf,0,total);
        initDataHead(&head);
        head.psize = length;
        head.esize = len;
        memcpy(tmpBuf,(void *)&head,size);
        memcpy(tmpBuf + size,encryptData,length);
        return toolkits::Toolkits::getByteArray(env, tmpBuf, total);
    }
    jbyteArray CryptoHelper::aes_decrypt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len)
    {
        const char *buf = toolkits::Toolkits::getCharPointer(env, javaBytes);
        if (buf == NULL)
        {
             return NULL;
        }
        DataHead head = readDataHead(buf,len);
        if (!isEncrypted(&head))
        {
             return javaBytes;
        }
        int length = head.psize;
        int size = sizeof(DataHead);
        char *bufs = (char *)calloc(1,head.psize);
        if(!bufs)
        {
            return NULL;
        }
        memset(bufs,0,head.psize);
        memcpy(bufs,(char *) buf + size ,length);
        crypto::BlockList blockList = crypto::Utils::toBlocks(bufs,length);
        char * decryptData = (char *)calloc(1,length);
        if(!decryptData)
        {
            return NULL;
        }
        memset(decryptData, 0, length);
        crypto::Api::decryptBlocksTo(blockList,decryptData);
        free(bufs);
        return toolkits::Toolkits::getByteArray(env, decryptData, head.esize);
    }
//
    jbyteArray CryptoHelper::sm4_encrypt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len)
    {
        const char *buf = toolkits::Toolkits::getCharPointer(env, javaBytes);
        if (buf == NULL)
        {
             return NULL;
        }
        DataHead head = readDataHead(buf,len);
        if(isEncrypted(&head))
        {
            return javaBytes;
        }
        crypto::BlockList blockList = crypto::Utils::toBlocks(buf, len);
        char encryptData[len];
        memset(encryptData, 0, len);
        crypto::Apis::encryptBlocksTo(blockList,encryptData);
        int encryptLength = (int)strlen(encryptData);
        int size = sizeof(DataHead);
        initDataHead(&head);


        int count = len /CRYPTO_BLOCK_SIZE;
        int rest = len % CRYPTO_BLOCK_SIZE;
        if(rest > 0)
        {
             count++;
        }
        int length = count * CRYPTO_BLOCK_SIZE;
        int total = size + length;
        char * tmpBuf = (char *)calloc(1,total);
        if(!tmpBuf)
        {
            return NULL;
        }
        head.psize = length;
        head.esize = len;
        memcpy(tmpBuf, (void *)&head, size);
        memcpy(tmpBuf + size, encryptData, length);
        return toolkits::Toolkits::getByteArray(env, tmpBuf, total);
    }
    jbyteArray CryptoHelper::sm4_decrpyt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len)
    {
        const char *buf = toolkits::Toolkits::getCharPointer(env, javaBytes);
        if (buf == NULL)
        {
             return NULL;
        }
        DataHead head = readDataHead(buf,len);
        if (!isEncrypted(&head))
        {
             return javaBytes;
        }
        int size = sizeof(DataHead);
        char bufs[head.psize];
        memset(bufs,0,head.psize);
        memcpy(bufs, buf + size ,head.psize);
        crypto::BlockList blockList = crypto::Utils::toBlocks(bufs, head.psize);
        char * decryptData = (char *)calloc(1,head.psize);
        if(!decryptData)
        {
            return NULL;
        }
        memset(decryptData, 0, head.psize);
        crypto::Apis::decryptBlocksTo(blockList,decryptData);
        return toolkits::Toolkits::getByteArray(env, decryptData, head.esize);
    }



//    jstring CryptoHelper::sm3_hash(JNIEnv *env,jclass cls,jbyteArray javaBytes)
//    {
//        const char *buf = toolkits::Toolkits::getCharPointer(env, javaBytes);
//        if (buf == NULL)
//        {
//            return NULL;
//        }
//        unsigned char output[32];
//        crypto::Apis::sm3hash((unsigned char *)buf,output);
//        return toolkits::Toolkits::getJString(env, (const char *)output, 32);
//
//    }




    static JNINativeMethod mCryptoHelperMethods[] =
    {
        CPP_NATIVE_METHOD(aes_encrypt,"([BI)[B",CryptoHelper::aes_encrypt),
        CPP_NATIVE_METHOD(aes_decrypt,"([BI)[B",CryptoHelper::aes_decrypt),
        CPP_NATIVE_METHOD(sm4_encrypt,"([BI)[B",CryptoHelper::sm4_encrypt),
        CPP_NATIVE_METHOD(sm4_decrypt,"([BI)[B",CryptoHelper::sm4_decrpyt),
//        CPP_NATIVE_METHOD(sm3_hash,"([B)Ljava/lang/String;",CryptoHelper::sm3_hash)
    };

    void CryptoHelper::registerCryptpHelper(JNIEnv *env)
    {
        registerNativeMethods(env,"com/example/yinfeng/cryptotest/crypto/CryptoHelper",mCryptoHelperMethods,sizeof(mCryptoHelperMethods)/sizeof(mCryptoHelperMethods[0]));
    }
}