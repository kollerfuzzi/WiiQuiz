#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <string>

namespace BSOD {
    void raise(std::string error);
    void raise(std::string error, int code);
}

#endif // ERRORHANDLER_HPP
