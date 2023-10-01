#include "resources.hpp"

Resources::Resources() {

}

Resources::~Resources() {
    this->clearAll();
}

GRRLIB_texImg * Resources::get(Texture texture) {
    if (!this->_textures.contains(texture)) {
        this->_loadTexture(texture);
    }
    return this->_textures[texture];
}

GRRLIB_ttfFont * Resources::get(Font font) {
    if (!this->_fonts.contains(font)) {
        this->_loadFont(font);
    }
    return this->_fonts[font];
}

void Resources::clearAll() {
    for (const auto& [key, value] : this->_textures) {
        GRRLIB_FreeTexture(value);
    }
    for (const auto& [key, value] : this->_fonts) {
        GRRLIB_FreeTTF(value);
    }
}

void Resources::_loadTexture(Texture texture) {
    TextureDef textureDef = TEXTURE_DEFINITIONS[texture];
    this->_textures[texture] = GRRLIB_LoadTexturePNG(
        textureDef.textureRef
    );
}

void Resources::_loadFont(Font font) {
    FontDef fontDef = FONT_DEFINITIONS[font];
    this->_fonts[font] = GRRLIB_LoadTTF(
        fontDef.fontRef, fontDef.fontLen
    );
}
