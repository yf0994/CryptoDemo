#ifndef __JNI_DIR_UTILS_H__
#define __JNI_DIR_UTILS_H__

#include <unistd.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace utils
{

class DirUtils
{
public:
    static string mapToDirPath(string packageName);
    static bool createDirFromPackage(string packageName);
    static bool createDirFromPath(string path);
    static vector<string> scanDir(string path);
	static bool mkdirs(string s, mode_t mode);
};

}


#endif
