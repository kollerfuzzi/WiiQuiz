#include "stringutils.hpp"

std::vector<std::string> StringUtils::split(std::string& str, char split) {
    std::vector<std::string> parts;
    std::istringstream iss(str);
    std::string part;
    while (std::getline(iss, part, split)) {
        parts.push_back(part);
    }
    return parts;
}
