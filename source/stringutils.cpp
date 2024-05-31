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

std::string StringUtils::join(std::vector<std::string>& strings, std::string join) {
    std::string joined;
    for (size_t i = 0; i < strings.size(); i++) {
        joined += strings[i];
        if (i != strings.size() - 1) {
            joined += join;
        }
    }
    return joined;
}
