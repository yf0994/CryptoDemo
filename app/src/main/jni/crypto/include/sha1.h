#ifndef __JNI_SHA1_H__
#define __JNI_SHA1_H_

#include <string>

using std::string;

namespace sha1
{

class Sha1
{
public:
	static string generateSha1();
	static string createSha1(const unsigned char *msg, unsigned len);
	static string createSha1(string msg);
	static string createFileSha1(const char *filename);
};

}

#endif
