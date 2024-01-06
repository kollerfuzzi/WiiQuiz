#include "resources.hpp"
#include "screendebug.hpp"
#include "grrlib.h"

std::string loadingAnimation = "|/-\\";

Resources::Resources() {
    _initC64Font();
    ScreenDebug::init(_fonts[Font::C64FONT].ttfFont);
    _resourceAPIClient = new ResourceAPIClient();
    _resourceAPIClient->request(APICommand::REGISTER_WII);
    _resourceFileManager = new ResourceFileManager();
}

Resources::~Resources() {
    _resourceAPIClient->request(APICommand::UNREGISTER_WII);
    clearAll();
    if (_resourceAPIClient != nullptr) {
        delete _resourceAPIClient;
    }
    if (_resourceFileManager != nullptr) {
        delete _resourceFileManager;
    }
}

GRRLIB_texImg* Resources::get(Texture texture) {
    if (!_textures.contains(texture)) {
        _loadTexture(texture);
    }
    return _textures[texture];
}

GRRLIB_ttfFont* Resources::get(Font font) {
    if (!_fonts.contains(font)) {
        _loadFont(font);
    }
    return _fonts[font].ttfFont;
}

BinaryResource Resources::get(Audio audio){
    if (!_audio.contains(audio)) {
        _loadAudio(audio);
    }
    return _audio[audio];
}

void Resources::clearAll() {
    for (const auto& [key, value] : _textures) {
        GRRLIB_FreeTexture(value);
    }

    for (const auto& [key, value] : _fonts) {
        GRRLIB_FreeTTF(value.ttfFont);
        _resourceFileManager->freeResource(value.resource);
    }

    for (const auto& [key, value] : _audio) {
        _resourceFileManager->freeResource(value);
    }
}

void Resources::fetchNetworkResources() {
    if (!_isUpdateAvailable()) {
        return;
    }

    _resourceFileManager->saveTestFile();
    _fetchNetworkAudio();
    _fetchNetworkTextures();
    _fetchNetworkFonts();
    _fetchNetworkVersion();

    ScreenDebug::clear();
}

bool Resources::_isUpdateAvailable() {
    std::string version("VERSION");
    BinaryResource localVersion = _resourceFileManager->loadResource(version);
    if (localVersion.data == nullptr) {
        return true;
    }
    std::string localVersionStr(reinterpret_cast<char*>(localVersion.data));
    std::string remoteVersion = _resourceAPIClient->fetchResourceVersion();

    bool isUpdate = localVersionStr != remoteVersion;

    _resourceFileManager->freeResource(localVersion);
    return isUpdate;
}

void Resources::_initC64Font() {
    unsigned char* fontBin = (unsigned char*) malloc(c64font_ttf_len);
    memcpy(fontBin, c64font_ttf, c64font_ttf_len);
    BinaryResource font = {fontBin, c64font_ttf_len};
    _fonts[Font::C64FONT] = {
        GRRLIB_LoadTTF(font.data, font.size),
        font
    };
}

void Resources::_fetchNetworkTextures() {
    constexpr auto textures = magic_enum::enum_values<Texture>();
    for (Texture tex : textures) {
        auto enumNameView = magic_enum::enum_name(tex);
        std::string enumName(enumNameView);
        _fetchAndStoreResource(enumName, TEXTURE_DEFINITIONS[tex].remotePath);
    }
}

void Resources::_fetchNetworkFonts() {
    constexpr auto fonts = magic_enum::enum_values<Font>();
    for (Font font : fonts) {
        auto enumNameView = magic_enum::enum_name(font);
        std::string enumName(enumNameView);
        _fetchAndStoreResource(enumName, FONT_DEFINITIONS[font].remotePath);
    }
}

void Resources::_fetchNetworkAudio() {
    constexpr auto audios = magic_enum::enum_values<Audio>();
    for (Audio audio : audios) {
        auto enumNameView = magic_enum::enum_name(audio);
        std::string enumName(enumNameView);
        _fetchAndStoreResource(enumName, AUDIO_DEFINITIONS[audio].remotePath);
    }
}

void Resources::_fetchNetworkVersion() {
    std::string remoteVersion = _resourceAPIClient->fetchResourceVersion();
    std::string version("VERSION");
    _resourceFileManager->saveResourcePlain(version, remoteVersion);
}

void Resources::_fetchAndStoreResource(std::string& name, std::string& path) {
    std::string namePath;
    namePath += name;
    namePath += ": ";
    namePath += path;
    _renderDebugStr(namePath);
    std::string resource = _resourceAPIClient->fetchResource(path);
    _resourceFileManager->saveResource(name, resource);
}

BinaryResource Resources::_loadResource(std::string& name) {
    return _resourceFileManager->loadResource(name);
}

void Resources::_loadTexture(Texture texture) {
    auto enumNameView = magic_enum::enum_name(texture);
    std::string enumName(enumNameView);
    BinaryResource resource = _loadResource(enumName);
    _textures[texture] = GRRLIB_LoadTexturePNG(
        resource.data
    );
    _resourceFileManager->freeResource(resource);
}

void Resources::_loadFont(Font font) {
    auto enumNameView = magic_enum::enum_name(font);
    std::string enumName(enumNameView);
    BinaryResource resource = _loadResource(enumName);
    _fonts[font] = {
        GRRLIB_LoadTTF(resource.data, resource.size),
        resource
    };
}

void Resources::_loadAudio(Audio audio) {
    auto enumNameView = magic_enum::enum_name(audio);
    std::string enumName(enumNameView);
    _audio[audio] = _loadResource(enumName);
}

void Resources::_renderDebugStr(std::string text) {
    loadCount++;
    std::string loadingStr("Loading resources ");
    loadingStr += loadingAnimation[loadCount % 4];
    loadingStr += "\n";
    loadingStr += text;
    ScreenDebug::printAndRender(loadingStr);
}
