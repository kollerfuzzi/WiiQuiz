#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <vector>
#include <string>
#include <grrlib.h>

#define SCREEN_WIDTH 640

class TextBox {
public:
    void setText(std::string text);
    void renderText();


    class Builder {
    public:
        Builder& font(GRRLIB_Font* font);
        Builder& fontSize(int fontSize);
        Builder& text(std::string text);
        Builder& color(int color);
        Builder& marginTop(int marginTop);
        Builder& marginLeft(int marginLeft);
        Builder& marginRight(int marginRight);
        TextBox build();
    private:
        GRRLIB_Font* _font;
        std::string _text;
        int _fontSize = 10;
        int _color = RGBA(255, 255, 255, 255);
        int _marginTop = 25;
        int _marginLeft = 25;
        int _marginRight = 25;
    };
    static Builder builder();

private:
    TextBox(GRRLIB_Font* font, int fontSize, int color, int marginTop, int marginLeft, int marginRight);
    std::vector<std::string> _textContent;
    std::vector<std::string> _textBuffer;
    GRRLIB_Font* _font;
    int _fontSize;
    int _color;
    int _marginTop;
    int _marginLeft;
    int _marginRight;
};

#endif // TEXTBOX_HPP
