#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <string>
#include <vector>
#include <sstream>

namespace StringUtils {
    std::vector<std::string> split(std::string& str, char split);
    std::string join(std::vector<std::string>& strings, std::string join);
}

#endif // STRINGUTILS_HPP
