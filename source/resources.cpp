#include "resources.hpp"
#include <stdlib.h>
#include <grrlib.h>
#include "screendebug.hpp"
#include "zr_notosans.hpp"
#include "bsod.hpp"
#include "mem.hpp"
#include "xxhashstr.hpp"

std::string loadingAnimation = "|/-\\";
extern std::string APIClient::ipAddress; 

Resources::Resources() {
    _initDefaultFont();
    ScreenDebug::init(_fonts[hash(pathOf(Font::DEFAULT_FONT))].ttfFont);
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

std::string Resources::pathOf(Texture texture) {
    return TEXTURE_PATHS[texture];
}

std::string Resources::pathOf(Font font) {
    return FONT_PATHS[font];
}

std::string Resources::pathOf(Audio audio) {
    return AUDIO_PATHS[audio];
}

std::string Resources::pathOf(Video video) {
    return VIDEO_PATHS[video];
}

std::string Resources::hash(std::string str) {
    return XXHashStr::hashStr(str);
}

GRRLIB_texImg* Resources::getTexture(Texture texture) {
    return getTexture(TEXTURE_PATHS[texture]);
}

GRRLIB_texImg *Resources::getTexture(std::string texturePath) {
    std::string textureHash = hash(texturePath);
    if (!_textures.contains(textureHash)) {
        _loadTexture(textureHash);
    }
    return _textures[textureHash];
}

GRRLIB_ttfFont* Resources::getFont(Font font) {
    return getFont(FONT_PATHS[font]);
}

GRRLIB_ttfFont *Resources::getFont(std::string fontPath) {
    std::string fontHash = hash(fontPath);
    if (!_fonts.contains(fontHash)) {
        _loadFont(fontHash);
    }
    return _fonts[fontHash].ttfFont;
}

BinaryChunk Resources::getAudio(Audio audio){
    return getAudio(AUDIO_PATHS[audio]);
}

BinaryChunk Resources::getAudio(std::string audioPath) {
    std::string audioHash = hash(audioPath);
    if (!_audio.contains(audioHash)) {
        _loadAudio(audioHash);
    }
    return _audio[audioHash];
}

MJpegPlayer* Resources::getVideo(Video video) {
    return new MJpegPlayer(hash(pathOf(video)), _resourceFileManager);
}

MJpegPlayer *Resources::getVideo(std::string videoPath) {
    return new MJpegPlayer(hash(videoPath), _resourceFileManager);
}

MJpegPlayer* Resources::getVideo(Video video, Audio audio){
    return new MJpegPlayer(hash(pathOf(video)), hash(pathOf(audio)), _resourceFileManager);
}

MJpegPlayer *Resources::getVideo(std::string videoPath, std::string audioPath) {
    return new MJpegPlayer(hash(videoPath), hash(audioPath), _resourceFileManager);
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

void Resources::fetchStaticResources() {
    _fetchNetworkVideos();
    _fetchNetworkAudio();
    _fetchNetworkTextures();
    _fetchNetworkFonts();

    ScreenDebug::clear();
}

void Resources::fetchResourcesByPaths(std::set<std::string> resourcePaths) {
    for (std::string resourcePath : resourcePaths) {
        _fetchResourceByPath(resourcePath);
    }
    ScreenDebug::clear();
}

bool Resources::_updateFileHash(std::string filePath) {
    std::string fileMetaResourceName("FILE_META");
    nlohmann::json fileMeta = _resourceFileManager->loadResourceJson(fileMetaResourceName);
    std::string remoteResourceHash = _resourceAPIClient->fetchResourceHash(filePath);

    bool hashUpdate = false;

    if (fileMeta.contains(filePath)) {
        std::string localResourceHash = fileMeta[filePath];
        hashUpdate = localResourceHash != remoteResourceHash;
    } else {
        hashUpdate = true;
    }

    if (hashUpdate) {
        fileMeta[filePath] = remoteResourceHash;
        _resourceFileManager->saveResourceJson(fileMetaResourceName, fileMeta);
    }

    return hashUpdate;
}

void Resources::_initDefaultFont() {
    unsigned char* fontBin = (unsigned char*) Mem::alloc(NotoSansMono_ttf_len);
    std::memcpy(fontBin, NotoSansMono_ttf, NotoSansMono_ttf_len);
    BinaryChunk font = {fontBin, NotoSansMono_ttf_len};
    _fonts[hash(pathOf(Font::DEFAULT_FONT))] = {
        GRRLIB_LoadTTF(font.data, font.size),
        font
    };
}

void Resources::_fetchNetworkTextures() {
    for (auto & [texture, path] : TEXTURE_PATHS) {
        _fetchResourceByPath(path);
    }
}

void Resources::_fetchNetworkFonts() {
    for (auto & [font, path] : FONT_PATHS) {
        _fetchResourceByPath(path);
    }
}

void Resources::_fetchNetworkAudio() {
    for (auto & [audio, path] : AUDIO_PATHS) {
        _fetchResourceByPath(path);
    }
}

void Resources::_fetchNetworkVideos() {
    for (auto & [video, path] : VIDEO_PATHS) {
        _fetchResourceByPath(path);
    }
}

void Resources::_fetchResourceByPath(std::string& path) {
    if (path.ends_with(".avi")) {
        _fetchAndStoreMjpegResource(path);
    } else {
        _fetchAndStoreResource(path);
    }
}

void Resources::_fetchAndStoreResource(std::string& path) {
    std::string pathHash = hash(path);
    std::string debugStr = path;
    debugStr += ": ";
    debugStr += pathHash;
    _renderDebugStr(debugStr);
    if (_updateFileHash(path)) {
        InputStream* stream = _resourceAPIClient->fetchResource(path);
        _resourceFileManager->saveResourceStream(pathHash, stream);
    }
}

void Resources::_fetchAndStoreMjpegResource(std::string& path) {
    std::string pathHash = hash(path);
    std::string debugStr = path;
    debugStr += ": ";
    debugStr += pathHash;
    _renderDebugStr(debugStr);
    if (_updateFileHash(path)) {
        InputStream* stream = _resourceAPIClient->fetchResource(path);
        _mjpegIO->saveMjpegStream(pathHash, stream);
    }
}

BinaryChunk Resources::_loadResource(std::string& hash) {
    return _resourceFileManager->loadResource(hash);
}

void Resources::_loadTexture(std::string& hash) {
    BinaryChunk resource = _loadResource(hash);
    _textures[hash] = GRRLIB_LoadTexturePNG(
        resource.data
    );
    _resourceFileManager->freeResource(resource);
}

void Resources::_loadFont(std::string& hash) {
    BinaryChunk resource = _loadResource(hash);
    _fonts[hash] = {
        GRRLIB_LoadTTF(resource.data, resource.size),
        resource
    };
}

void Resources::_loadAudio(std::string& hash) {
    _audio[hash] = _loadResource(hash);
}

void Resources::_renderDebugStr(std::string text) {
    loadCount++;
    std::string loadingStr("Loading resources ");
    loadingStr += loadingAnimation[loadCount % 4];
    loadingStr += "\n";
    loadingStr += text;
    ScreenDebug::printAndRender(loadingStr);
}
