#ifndef TINYUUID4_HPP
#define TINYUUID4_HPP

#include <stdlib.h>
#include <time.h>
#include <string>

namespace TinyUuidV4 {
    /// @brief Generates a uuidv4 string according to rfc 4122 
    /// @return std::string representation of the uuid4 
    std::string generate();
}

#endif // TINYUUID4_HPP
