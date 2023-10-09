#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <vector>
#include <string>
#include <grrlib.h>
#include "clock.hpp"

#define SCREEN_WIDTH 640
#define NO_ANIMATION -1
#define ANIMATION_END -1

#include "renderable.hpp"

class TextBox : Renderable {
public:
    void setText(std::string text);
    void update(const Clock& clock);
    void render();


    class Builder {
    public:
        Builder& font(GRRLIB_Font* font);
        Builder& fontSize(int fontSize);
        Builder& text(std::string text);
        Builder& color(int color);
        Builder& marginTop(int marginTop);
        Builder& marginLeft(int marginLeft);
        Builder& marginRight(int marginRight);
        Builder& animationSpeed(int animationSpeed);
        TextBox* build();
    private:
        GRRLIB_Font* _font;
        std::string _text;
        unsigned int _fontSize = 10;
        int _color = RGBA(255, 255, 255, 255);
        unsigned int _marginTop = 25;
        unsigned int _marginLeft = 25;
        unsigned int _marginRight = 25;
        int _animationSpeed = NO_ANIMATION;
    };
    static Builder builder();

private:
    TextBox(GRRLIB_Font* font, unsigned int fontSize, int color,
            unsigned int marginTop, unsigned int marginLeft,
            unsigned int marginRight, int animationSpeed);
    std::vector<std::string> _textContent;
    std::vector<std::string> _textBuffer;
    GRRLIB_Font* _font;
    int _fontSize;
    int _color;
    unsigned int _marginTop;
    unsigned int _marginLeft;
    unsigned int _marginRight;
    int _animationSpeed;
    unsigned int _animationTimePassed = 0;
    unsigned int _animationCursorCharCount = 0;
    unsigned int _animationCursorLine = 0;
    unsigned int _animationCursorLinePos = 0;
};

#endif // TEXTBOX_HPP
