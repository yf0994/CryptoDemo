#include "crypto_api.h"

#include "aes_api.h"


namespace crypto
{

bool Api::encryptBlock(Block &block)
{
    Block out;
    AES::Api::encrypt(block.constData(), CRYPTO_BLOCK_SIZE, out.data(), CRYPTO_BLOCK_SIZE);
    memcpy(block.data(), out.constData(), CRYPTO_BLOCK_SIZE);
    return true;
}

bool Api::decryptBlock(Block &block)
{
    Block out;
    AES::Api::decrypt(block.constData(), CRYPTO_BLOCK_SIZE, out.data(), CRYPTO_BLOCK_SIZE);
    memcpy(block.data(), out.constData(), CRYPTO_BLOCK_SIZE);
    return true;
}

bool Api::encryptBlocks(BlockList &blocks)
{
    BlockListIterator iter;
    for (iter = blocks.begin(); iter != blocks.end(); ++iter)
	encryptBlock(*iter);
    return true;
}

bool Api::decryptBlocks(BlockList &blocks)
{
    BlockListIterator iter;
    for (iter = blocks.begin(); iter != blocks.end(); ++iter)
	decryptBlock(*iter);
    return true;
}

bool Api::encryptBlocksTo(BlockList const &blocks, char *buf)
{
    BlockListConstIterator iter;
    for (iter = blocks.cbegin(); iter != blocks.cend(); ++iter)
    {
	AES::Api::encrypt(iter->constData(), CRYPTO_BLOCK_SIZE, buf, CRYPTO_BLOCK_SIZE);
	buf += CRYPTO_BLOCK_SIZE;
    }
    return true;
}

bool Api::decryptBlocksTo(BlockList const &blocks, char *buf)
{
    BlockListConstIterator iter;
    for (iter = blocks.cbegin(); iter != blocks.cend(); ++iter)
    {
	AES::Api::decrypt(iter->constData(), CRYPTO_BLOCK_SIZE, buf, CRYPTO_BLOCK_SIZE);
	buf += CRYPTO_BLOCK_SIZE;
    }
    return true;
}

}
