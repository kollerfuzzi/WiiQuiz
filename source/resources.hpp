#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <grrlib.h>
#include <map>
#include "resourcemap.hpp"

class Resources {
public:
    Resources();
    ~Resources();
    GRRLIB_texImg* get(Texture texture);
    GRRLIB_ttfFont* get(Font font);
    void clearAll();
private:
    std::map<Texture, GRRLIB_texImg*> _textures;
    std::map<Font, GRRLIB_ttfFont*> _fonts;

    void _loadTexture(Texture texture);
    void _loadFont(Font font);
};

#endif // RESOURCES_HPP
