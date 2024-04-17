#ifndef BINARYRESOURCE_HPP
#define BINARYRESOURCE_HPP

#include <string>

struct BinaryResource {
    unsigned char* data;
    size_t size;
    BinaryResource() {

    }

    BinaryResource(unsigned char* _data, size_t _size) {
        data = _data;
        size = _size;
    }
};

#endif // BINARYRESOURCE_HPP