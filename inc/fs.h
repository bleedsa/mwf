#ifndef __MWF_FS_H__
#define __MWF_FS_H__

#include <filesystem>
#include <vector>
#include <string>

#include <u.h>

namespace std {
	namespace fs = std::filesystem;
}

namespace fs {
	std::vector<std::string> png_files(std::string p);
	std::vector<std::string> bmp_files(std::string p);
}

#endif
