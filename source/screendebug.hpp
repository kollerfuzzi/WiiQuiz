#ifndef SCREENDEBUG_HPP
#define SCREENDEBUG_HPP

#include <string>
#include "textbox.hpp"
#include "zr_c64font.hpp"

class ScreenDebug {
public:
    ~ScreenDebug();
    static void init(GRRLIB_ttfFont* font);
    static void destroy();
    static ScreenDebug* instance();
    static void printLn(std::string text);
    static void print(std::vector<std::string>& lines);
    static void print(std::string lines);
    static void render();
    static void clear();
private:
    void _printLn(std::string text);
    void _print(std::string text);
    void _render();
    void _clear();
    ScreenDebug(GRRLIB_ttfFont* font);
    static ScreenDebug* _instance;
    std::string _text;
    GRRLIB_Font* _font = nullptr;
    TextBox* _textbox = nullptr;
};

#endif // SCREENDEBUG_HPP
