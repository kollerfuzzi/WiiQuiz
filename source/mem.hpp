#ifndef MEM_HPP
#define MEM_HPP

#include <string>

namespace Mem {
    void* alloc(size_t size);
    void mfree(void* mem);
}

#endif // MEM_HPP