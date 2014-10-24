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
    void CryptoHelper::initDataHead(DataHead *head)
        {
            head->magic = HEAD_MAGIC_V1;
            head->psize = 0;
            head->esize = 0;
        }

        DataHead CryptoHelper::readDataHead(const char *buf,int len)
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

        bool CryptoHelper::isEncrypted(DataHead *head)
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
        //            LOG_I("is Encrypted");
                    return javaBytes;
                }
                crypto::BlockList blockList = crypto::Utils::toBlocks(buf, len);
                char encryptData[len];
                memset(encryptData, 0, len);
                crypto::Api::encryptBlocksTo(blockList,encryptData);
        //        LOG_I("++++++[%s]+++++",encryptData);
                int encryptLength = (int)strlen(encryptData);
                initDataHead(&head);
                head.psize = len;
                head.esize = encryptLength;
        //        LOG_I("++++++Head info %x,%d,%d",head.magic,head.psize,head.esize);
                int size = sizeof(DataHead);
                char *tmpBuf = (char *)calloc(1, size + encryptLength);
                memcpy(tmpBuf, (void *)&head, size);
                memcpy(tmpBuf + size, encryptData, encryptLength);

        return toolkits::Toolkits::getByteArray(env, tmpBuf, size + encryptLength);
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
                    //LOG_D("not encrypted");
                    return javaBytes;
                }
                //        LOG_D("-----Head info %x,%d,%d:",head.magic,head.psize,head.esize);
                int size = sizeof(DataHead);
                char bufs[head.esize];
                memcpy(bufs,(char *) buf + size ,head.esize);
                //        LOG_D("------[%s]-------",bufs);
                crypto::BlockList blockList = crypto::Utils::toBlocks(bufs, head.psize);

                char * encryptData = (char *)calloc(1, head.psize);
                memset(encryptData, 0, head.psize);
                crypto::Api::decryptBlocksTo(blockList,encryptData);
        return toolkits::Toolkits::getByteArray(env, encryptData, head.psize);
    }
//
    jbyteArray CryptoHelper::sm4_encrypt(JNIEnv *env, jclass cls, jbyteArray javaBytes, jint len)
    {
        const char *buf = toolkits::Toolkits::getCharPointer(env, javaBytes);
        if (buf == NULL)
        {
             return NULL;
        }
        LOGI("[%s]",buf);
        DataHead head = readDataHead(buf,len);
        if(isEncrypted(&head))
        {
        //            LOG_I("is Encrypted");
             return javaBytes;
        }
        crypto::BlockList blockList = crypto::Utils::toBlocks(buf, len);
        char encryptData[len];
        memset(encryptData, 0, len);
        crypto::Apis::encryptBlocksTos(blockList,encryptData);
        int encryptLength = (int)strlen(encryptData);
        int size = sizeof(DataHead);
        initDataHead(&head);
        head.psize = len;
        head.esize = encryptLength;
        int total = size + encryptLength;
        //        LOG_I("++++++Head info %x,%d,%d,%d",head.magic,head.psize,head.esize,total);

        //        char tmpBuf[total + 1];
//        char * tmpBuf = (char *)calloc(1, total);
        char tmpBuf[total];
        memcpy(tmpBuf, (void *)&head, size);
        memcpy(tmpBuf + size, encryptData, encryptLength);
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
        //            LOG_D("not encrypted");
             return javaBytes;
        }
        //        LOG_D("-----Head info %x,%d,%d:",head.magic,head.psize,head.esize);
        int size = sizeof(DataHead);
        char bufs[head.esize];
        memset(bufs,0,head.esize);
        memcpy(bufs,(char *) buf + size ,head.esize);
        //        LOG_D("------[%s]-------",bufs);
        crypto::BlockList blockList = crypto::Utils::toBlocks(bufs, head.psize);
                //        char * decryptData = (char *)calloc(1, head.psize);
//        char * decryptData = (char *)calloc(1, head.psize);
        char decryptData[head.psize];
        memset(decryptData, 0, head.psize);
        crypto::Apis::decryptBlocksTos(blockList,decryptData);
        return toolkits::Toolkits::getByteArray(env, decryptData, head.psize);
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