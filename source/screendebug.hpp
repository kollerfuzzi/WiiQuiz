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
    static void disable();
    static void enable();
    static bool isEnabled();
    static void clear();
private:
    void _printLn(std::string text);
    void _print(std::string text);
    void _render();
    void _disable();
    void _enable();
    bool _isEnabled();
    void _clear();
    ScreenDebug(GRRLIB_ttfFont* font);
    static ScreenDebug* _instance;
    std::string _text;
    GRRLIB_Font* _font = nullptr;
    TextBox* _textbox = nullptr;
    bool _enabled = true;
};

#endif // SCREENDEBUG_HPP
