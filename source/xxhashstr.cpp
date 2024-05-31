#include "xxhashstr.hpp"
#include "xxhash64.h"
#include "zr_hexstrings.hpp"

std::string XXHashStr::hashStr(std::string str) {
    XXHash64 xx(0);
    xx.add(str.c_str(), str.length());
    uint64_t hash = xx.hash();
    std::string hashStr;
    for (char i = 0; i < 8; i++) {
        hashStr += hex_strings[*((unsigned char*)&hash + i)];
    }
    return hashStr;
}