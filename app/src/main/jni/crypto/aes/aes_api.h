#ifndef __JNI_CRYPTO_AES_API_H__
#define __JNI_CRYPTO_AES_API_H__


#include "block.h"

using crypto::Block;

namespace AES
{

typedef struct UserKey
{
    unsigned char data[CRYPTO_BLOCK_SIZE];
} UserKey;

class Api
{
public:
    static bool initKey(UserKey *uk);
    static bool encrypt(const char *in, int inSize, char *out, int outSize);
    static bool decrypt(const char *in, int inSize, char *out, int outSize);
};

}


#endif
