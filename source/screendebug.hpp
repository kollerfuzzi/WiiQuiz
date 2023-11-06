#ifndef SCREENDEBUG_HPP
#define SCREENDEBUG_HPP

#include <string>
#include "textbox.hpp"
#include "resources.hpp"

class ScreenDebug {
public:
    ~ScreenDebug();
    static void init(Resources* resources);
    static void destroy();
    static ScreenDebug* instance();
    static void printLn(std::string text);
    static void render();
    static void clear();
private:
    void _printLn(std::string text);
    void _render();
    void _clear();
    ScreenDebug(Resources* resources);
    static ScreenDebug* _instance;
    std::string _text;
    TextBox* _textbox = nullptr;
    Resources* _resources;
};

#endif // SCREENDEBUG_HPP
