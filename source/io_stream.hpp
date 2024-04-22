#ifndef IO_STREAM_HPP
#define IO_STREAM_HPP

#include <string>
#include <cstring>

struct BinaryChunk {
    unsigned char* data;
    size_t size;
    BinaryChunk() {

    }

    BinaryChunk(unsigned char* _data, size_t _size) {
        data = _data;
        size = _size;
    }
};


class InputStream {
public:
    InputStream();
    virtual ~InputStream() = 0;
    virtual size_t read(BinaryChunk buffer) = 0;
    void advance(BinaryChunk buffer, size_t maxLen);
    size_t getStreamPos();
    size_t getMaxSize();
    virtual void close() = 0;
    bool isEOF();
protected:
    size_t _streamPos = 0;
    size_t _maxSize = 0;
    bool _open = true;
};

#endif // IO_STREAM