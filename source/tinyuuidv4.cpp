
#include "tinyuuidv4.hpp"
#include "zr_hexstrings.hpp"
#include <stdlib.h>
#include <time.h>

static char variant[] = {'8', '9', 'a', 'b'};
static bool randInitialized = false;

std::string TinyUuidV4::generate() {
    if (!randInitialized) {
        randInitialized = true;
        srand(time(0));
    }
    std::string uuid;
    unsigned int randomNumber;
    for (char i = 0; i < 4; ++i) {
        randomNumber = rand();
        for (char randPos = 0; randPos < 4; randPos++) {
            uuid += hex_strings[*((unsigned char*)&randomNumber + randPos)];
            char pos = i * 4 + randPos + 1;
            if (pos >= 3 && pos <= 10 && pos % 2 == 0) {
                uuid += '-';
            }
        }
    }
    uuid[14] = '4';
    uuid[19] = variant[randomNumber % 4];
    return uuid;
}
