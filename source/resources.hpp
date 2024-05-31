#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <grrlib.h>
#include <map>
#include "resourcemap.hpp"
#include "resourceapiclient.hpp"
#include "magic_enum.hpp"
#include "resourcefilemanager.hpp"
#include "mjpegio.hpp"
#include "mjpegplayer.hpp"

struct TTFFontWithResources {
    GRRLIB_ttfFont* ttfFont;
    BinaryChunk resource;
};

class Resources {
public:
    Resources();
    ~Resources();
    static std::string pathOf(Texture texture);
    static std::string pathOf(Font font);
    static std::string pathOf(Audio audio);
    static std::string pathOf(Video video);
    static std::string hash(std::string str);
    GRRLIB_texImg* getTexture(Texture texture);
    GRRLIB_texImg* getTexture(std::string texturePath);
    GRRLIB_ttfFont* getFont(Font font);
    GRRLIB_ttfFont* getFont(std::string fontPath);
    BinaryChunk getAudio(Audio audio);
    BinaryChunk getAudio(std::string audioPath);
    MJpegPlayer* getVideo(Video video);
    MJpegPlayer* getVideo(std::string videoPath);
    MJpegPlayer* getVideo(Video video, Audio audio);
    MJpegPlayer* getVideo(std::string videoPath, std::string audioPath);
    void clearAll();
    void fetchStaticResources();
    void fetchResourcesByPaths(std::set<std::string> resourcePaths);
private:
    std::map<std::string, GRRLIB_texImg*> _textures;
    std::map<std::string, TTFFontWithResources> _fonts;
    std::map<std::string, BinaryChunk> _audio;
    bool _updateFileHash(std::string filePath);
    void _initDefaultFont();
    void _fetchNetworkTextures();
    void _fetchNetworkFonts();
    void _fetchNetworkAudio();
    void _fetchNetworkVideos();
    void _fetchResourceByPath(std::string& path);
    void _fetchAndStoreResource(std::string& path);
    void _fetchAndStoreMjpegResource(std::string& path);
    BinaryChunk _loadResource(std::string& hash);
    void _loadTexture(std::string& hash);
    void _loadFont(std::string& hash);
    void _loadAudio(std::string& hash);
    void _renderDebugStr(std::string text);
    ResourceAPIClient* _resourceAPIClient = nullptr;
    ResourceFileManager* _resourceFileManager = nullptr;
    MjpegIO* _mjpegIO;
    int loadCount = 0;
};

#endif // RESOURCES_HPP
