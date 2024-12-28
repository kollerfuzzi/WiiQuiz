#include "mem.hpp"
#include "bsod.hpp"

void* Mem::alloc(size_t size) {
    void* mem = malloc(size);
    if (mem == nullptr) {
        std::string error = "Memory allocation of ";
        error += std::to_string(size);
        error += "B failed";
        BSOD::raise(error);
    }
    return mem;
}

void Mem::mfree(void* mem){
    free(mem);
}
