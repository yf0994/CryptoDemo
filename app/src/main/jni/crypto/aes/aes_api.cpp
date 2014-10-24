
//#include <mutex>

#include <openssl/aes.h>
#include <android/log.h>

#include "aes_api.h"
#include "apputils.h"

//static std::mutex gMutex;

//static unsigned char key[AES_BLOCK_SIZE];
//static unsigned char iv[AES_BLOCK_SIZE];
//static AES_KEY aesKey;

namespace AES
{

bool Api::initKey(UserKey *key)
{
    if (key == NULL)
	return false;
    for (int i = 0; i < AES_BLOCK_SIZE; ++i)
	key->data[i] = 32 + i;
    return true;
}

bool Api::encrypt(const char *in, int inSize, char *out, int outSize)
{
    UserKey uk;
    AES_KEY ak;
    initKey(&uk);
    AES_set_encrypt_key(uk.data, 128, &ak);
    AES_encrypt((unsigned char *)in, (unsigned char *)out, &ak);
    return true;
}

bool Api::decrypt(const char *in, int inSize, char *out, int outSize)
{
    UserKey uk;
    AES_KEY ak;
    initKey(&uk);
    AES_set_decrypt_key(uk.data, 128, &ak);
    AES_decrypt((unsigned char *)in, (unsigned char *)out, &ak);
    return true;
}

}
