#include "resources.hpp"
#include <stdlib.h>
#include <grrlib.h>
#include "screendebug.hpp"
#include "zr_notosans.hpp"
#include "bsod.hpp"
#include "mem.hpp"
#include "xxhashstr.hpp"
#include "loadingbar.hpp"
#include "serverdiscovery.hpp"

extern std::string APIClient::ipAddress; 

Resources::Resources() {
    _initDefaultFont();
    ScreenDebug::init(_fonts[hash(pathOf(Font::DEFAULT_FONT))].ttfFont);
    srand(time(NULL));
    _resourceFileManager = new ResourceFileManager();
    _setServerIp();
    _resourceAPIClient = new ResourceAPIClient();
    _resourceAPIClient->registerWii();
    _mjpegIO = new MjpegIO(_resourceFileManager);
}

Resources::~Resources() {
    _reservedResources.clear();
    clearUnreserved();
    if (_resourceAPIClient != nullptr) {
        _resourceAPIClient->unregisterWii();
        delete _resourceAPIClient;
        _resourceAPIClient = nullptr;
    }
    if (_resourceFileManager != nullptr) {
        delete _resourceFileManager;
        _resourceFileManager = nullptr;
    }
    if (_mjpegIO != nullptr) {
        delete _mjpegIO;
        _mjpegIO = nullptr;
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

GRRLIB_texImg* Resources::getTexture(std::string texturePath) {
    std::string textureHash = hash(texturePath);
    if (!_textures.contains(textureHash)) {
        _loadTexture(textureHash);
    }
    return _textures[textureHash];
}

GRRLIB_ttfFont* Resources::getFont(Font font) {
    return getFont(FONT_PATHS[font]);
}

GRRLIB_ttfFont* Resources::getFont(std::string fontPath) {
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

MJpegPlayer* Resources::getVideo(AVResource video) {
    return new MJpegPlayer(video, _resourceFileManager);
}

void Resources::addReserved(std::string path) {
    _reservedResources.insert(hash(path));
}

void Resources::removeReserved(std::string path) {
    _reservedResources.erase(hash(path));
}

void Resources::clearUnreserved() {
    for (auto it = _textures.cbegin(); it != _textures.cend();) {
        if (!_reservedResources.contains(it->first)) {
            GRRLIB_FreeTexture(it->second);
            _textures.erase(it++);
        } else {
            ++it;
        }
    }
    for (auto it = _fonts.cbegin(); it != _fonts.cend();) {
        if (!_reservedResources.contains(it->first)) {
            _resourceFileManager->freeResource(it->second.resource);
            _fonts.erase(it++);
        } else {
            ++it;
        }
    }
    for (auto it = _audio.cbegin(); it != _audio.cend();) {
        if (!_reservedResources.contains(it->first)) {
            _resourceFileManager->freeResource(it->second);
            _audio.erase(it++);
        } else {
            ++it;
        }
    }
}

void Resources::fetchStaticResources() {
    _fetchNetworkVideos();
    _fetchNetworkAudio();
    _fetchNetworkTextures();
    _fetchNetworkFonts();
    ScreenDebug::clear();
}

void Resources::fetchStaticAndPathResources(std::set<std::string> resourcePaths) {
    std::set<std::string> allResourcePaths;
    std::set<std::string> staticResources = _getStaticHashes();
    for (std::string resourcePath : resourcePaths) {
        allResourcePaths.emplace(resourcePath);
    }
    for (std::string staticPath : staticResources) {
        allResourcePaths.emplace(staticPath);
    }
    LoadingBar::setTicks(allResourcePaths.size()); 

    _resourceAPIClient->cacheResourceHashes(allResourcePaths);
    fetchStaticResources();
    fetchResourcesByPaths(resourcePaths);

    _resourceFileManager->saveCachedJson();
    _resourceAPIClient->clearCache();
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
        _resourceFileManager->saveResourceJsonCached(fileMetaResourceName, fileMeta);
    }

    return hashUpdate;
}

void Resources::_initDefaultFont() {
    unsigned char* fontBin = (unsigned char*) Mem::alloc(NotoSansMono_ttf_len);
    std::memcpy(fontBin, NotoSansMono_ttf, NotoSansMono_ttf_len);
    BinaryChunk font = {fontBin, NotoSansMono_ttf_len};
    addReserved(pathOf(Font::DEFAULT_FONT));
    _fonts[hash(pathOf(Font::DEFAULT_FONT))] = {
        GRRLIB_LoadTTF(font.data, font.size),
        font
    };
}

std::set<std::string> Resources::_getStaticHashes() {
    std::set<std::string> hashes;
    for (auto & [texture, path] : TEXTURE_PATHS) {
        hashes.emplace(path);
    }
    for (auto & [font, path] : FONT_PATHS) {
        hashes.emplace(path);
    }
    for (auto & [audio, path] : AUDIO_PATHS) {
        hashes.emplace(path);
    }
    for (auto & [audio, path] : VIDEO_PATHS) {
        hashes.emplace(path);
    }
    return hashes;
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
    _advanceLoadingBar();
    if (_updateFileHash(path)) {
        InputStream* stream = _resourceAPIClient->fetchResource(path);
        _resourceFileManager->saveResourceStream(pathHash, stream);
    }
}

void Resources::_fetchAndStoreMjpegResource(std::string& path) {
    std::string pathHash = hash(path);
    _advanceLoadingBar();
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

void Resources::_advanceLoadingBar() {
    LoadingBar::tick(getFont(Font::DEFAULT_FONT));
}

void Resources::_setServerIp() {
    APIClient::ipAddress = _resourceFileManager->loadIpAddressFromConfig();
    if (APIClient::testConnection()) {
        return;
    }
    APIClient::ipAddress = ServerDiscovery::waitForServerGetAddr();
    if (!APIClient::testConnection()) {
        BSOD::raise("No server discovered");
    }
}
