#include "io_stream.hpp"
#include "mem.hpp"

InputStream::InputStream() {
}

InputStream::~InputStream() {

}

void InputStream::advance(BinaryChunk buffer, size_t maxLen) {
    BinaryChunk chunk(buffer.data, maxLen);
    read(chunk);
}

size_t InputStream::getStreamPos() {
    return _streamPos;
}

size_t InputStream::getMaxSize() {
    return _maxSize;
}

bool InputStream::isEOF() {
    return !_open;
}
