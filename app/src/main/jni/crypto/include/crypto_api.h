
#include "block.h"

namespace crypto
{

class Api
{
public:
    static bool encryptFile(const char *inpath, const char *outpath);
    static bool decryptFile(const char *inpath, const char *outpath);
    static bool encryptBlock(Block &block);
    static bool decryptBlock(Block &block);

    static bool encryptBlocks(BlockList &blocks);
    static bool decryptBlocks(BlockList &blocks);

    static bool encryptBlocksTo(BlockList const &blocks, char *buf);
    static bool decryptBlocksTo(BlockList const &blocks, char *buf);
};

}


