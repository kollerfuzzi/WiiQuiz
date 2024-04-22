#include "resources.hpp"
#include <stdlib.h>
#include <grrlib.h>
#include "screendebug.hpp"
#include "zr_notosans.hpp"
#include "bsod.hpp"
#include "mem.hpp"

std::string loadingAnimation = "|/-\\";
extern std::string APIClient::ipAddress; 

Resources::Resources() {
    _initDefaultFont();
    ScreenDebug::init(_fonts[Font::DEFAULT_FONT].ttfFont);
    srand(time(NULL));
    _resourceFileManager = new ResourceFileManager();
    APIClient::ipAddress = _resourceFileManager->loadIpAddressFromConfig();
    _resourceAPIClient = new ResourceAPIClient();
    _resourceAPIClient->registerWii();
    _mjpegIO = new MjpegIO(_resourceFileManager);
}

Resources::~Resources() {
    clearAll();
    if (_resourceAPIClient != nullptr) {
        _resourceAPIClient->unregisterWii();
        delete _resourceAPIClient;
    }
    if (_resourceFileManager != nullptr) {
        delete _resourceFileManager;
    }
    if (_mjpegIO != nullptr) {
        delete _mjpegIO;
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

BinaryChunk Resources::get(Audio audio){
    if (!_audio.contains(audio)) {
        _loadAudio(audio);
    }
    return _audio[audio];
}

MJpegPlayer* Resources::get(Video video) {
    return new MJpegPlayer(video, _resourceFileManager);
}

MJpegPlayer* Resources::get(Video video, Audio audio){
    return new MJpegPlayer(video, audio, _resourceFileManager);
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

    _fetchNetworkVideos();
    _fetchNetworkAudio();
    _fetchNetworkTextures();
    _fetchNetworkFonts();
    _fetchNetworkVersion();

    ScreenDebug::clear();
}

bool Resources::_isUpdateAvailable() {
    std::string version("VERSION");
    BinaryChunk localVersionResource = _resourceFileManager->loadResource(version);
    if (localVersionResource.data == nullptr) {
        return true;
    }
    std::string localVersionStr(reinterpret_cast<char*>(localVersionResource.data));
    s32 localVersion = stoi(localVersionStr);
    s32 remoteVersion = _resourceAPIClient->fetchResourceVersion();

    bool isUpdate = localVersion != remoteVersion;

    _resourceFileManager->freeResource(localVersionResource);
    return isUpdate;
}

void Resources::_initDefaultFont() {
    unsigned char* fontBin = (unsigned char*) Mem::alloc(NotoSansMono_ttf_len);
    std::memcpy(fontBin, NotoSansMono_ttf, NotoSansMono_ttf_len);
    BinaryChunk font = {fontBin, NotoSansMono_ttf_len};
    _fonts[Font::DEFAULT_FONT] = {
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
    s32 remoteVersion = _resourceAPIClient->fetchResourceVersion();
    std::string versionNumberStr = std::to_string(remoteVersion);
    std::string version("VERSION");
    BinaryChunk resource = {
        (unsigned char*) versionNumberStr.c_str(), 
        versionNumberStr.size()
    };
    _resourceFileManager->saveResource(version, resource);
}

void Resources::_fetchNetworkVideos() {
    constexpr auto videos = magic_enum::enum_values<Video>();
    for (Video video : videos) {
        auto enumNameView = magic_enum::enum_name(video);
        std::string enumName(enumNameView);
        _fetchAndStoreMjpegResource(enumName, VIDEO_DEFINITIONS[video].remotePath);
    }
}

void Resources::_fetchAndStoreResource(std::string& name, std::string& path) {
    std::string namePath;
    namePath += name;
    namePath += ": ";
    namePath += path;
    _renderDebugStr(namePath);
    InputStream* stream = _resourceAPIClient->fetchResource(path);
    _resourceFileManager->saveResourceStream(name, stream);
}

void Resources::_fetchAndStoreMjpegResource(std::string &name, std::string& path) {
    std::string namePath;
    namePath += name;
    namePath += ": ";
    namePath += path;
    _renderDebugStr(namePath);
    InputStream* stream = _resourceAPIClient->fetchResource(path);
    _mjpegIO->saveMjpegStream(name, stream);
}

BinaryChunk Resources::_loadResource(std::string& name) {
    return _resourceFileManager->loadResource(name);
}

void Resources::_loadTexture(Texture texture) {
    auto enumNameView = magic_enum::enum_name(texture);
    std::string enumName(enumNameView);
    BinaryChunk resource = _loadResource(enumName);
    _textures[texture] = GRRLIB_LoadTexturePNG(
        resource.data
    );
    _resourceFileManager->freeResource(resource);
}

void Resources::_loadFont(Font font) {
    auto enumNameView = magic_enum::enum_name(font);
    std::string enumName(enumNameView);
    BinaryChunk resource = _loadResource(enumName);
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
