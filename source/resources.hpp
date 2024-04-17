#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <grrlib.h>
#include <map>
#include "resourcemap.hpp"
#include "resourceapiclient.hpp"
#include "magic_enum.hpp"
#include "resourcefilemanager.hpp"
#include "mjpegio.hpp"

struct TTFFontWithResources {
    GRRLIB_ttfFont* ttfFont;
    BinaryResource resource;
};

class Resources {
public:
    Resources();
    ~Resources();
    GRRLIB_texImg* get(Texture texture);
    GRRLIB_ttfFont* get(Font font);
    BinaryResource get(Audio audio);
    void clearAll();
    void fetchNetworkResources();
private:
    std::map<Texture, GRRLIB_texImg*> _textures;
    std::map<Font, TTFFontWithResources> _fonts;
    std::map<Audio, BinaryResource> _audio;
    std::map<Video, Mjpeg> _videos;
    bool _isUpdateAvailable();
    void _initDefaultFont();
    void _fetchNetworkTextures();
    void _fetchNetworkFonts();
    void _fetchNetworkAudio();
    void _fetchNetworkVersion();
    void _fetchNetworkVideos();
    void _fetchAndStoreResource(std::string& name, std::string& path);
    void _fetchAndStoreMjpegResource(std::string& name, std::string& path);
    BinaryResource _loadResource(std::string& name);
    void _loadTexture(Texture texture);
    void _loadFont(Font font);
    void _loadAudio(Audio font);
    void _loadVideo(Video video);
    void _renderDebugStr(std::string text);
    ResourceAPIClient* _resourceAPIClient = nullptr;
    ResourceFileManager* _resourceFileManager = nullptr;
    MjpegIO* _mjpegIO;
    int loadCount = 0;
};

#endif // RESOURCES_HPP
