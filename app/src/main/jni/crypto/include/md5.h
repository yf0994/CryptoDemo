#ifndef __JNI_MD5_H__
#define __JNI_MD5_H__

#include <string>

#define MD5_DIGEST_LEN 16

using std::string;

namespace md5
{

class Md5
{
public:
	static string generateMd5();
	static string createMd5(unsigned char const *msg, unsigned len);
	static string createMd5(string msg);
	static string createFileMd5(unsigned char const *filename);
};

}

#endif
