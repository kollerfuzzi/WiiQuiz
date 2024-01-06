#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <vector>
#include <string>
#include <grrlib.h>
#include "clock.hpp"
#include "renderable.hpp"

#define SCREEN_WIDTH 640
#define NO_ANIMATION -1


enum TextBoxAnimationState {
    RUNNING,
    TERMINATED
};

class TextBox : public Renderable {
public:
    void setText(std::string text);
    void appendLineWithoutAnimation(std::string text);
    void setColor(int color);
    void setAnimationSpeed(unsigned int speed);
    void setBelow(TextBox* above);
    u32 getTop();
    u32 getBottom();
    u32 getHeight();
    void update(Clock& clock);
    void copyBufferToContent();
    void render();
    bool isDone();
    TextBoxAnimationState getAnimationState();
    size_t lineCount();


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
        Builder& below(TextBox* above);
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
        TextBox* _above = nullptr;
    };
    static Builder builder();

private:
    TextBox(GRRLIB_Font* font, unsigned int fontSize, int color,
            unsigned int marginTop, unsigned int marginLeft,
            unsigned int marginRight, int animationSpeed, TextBox* above);
    std::vector<std::string> _textContent;
    std::vector<std::string> _textBuffer;
    GRRLIB_Font* _font = nullptr;
    int _fontSize;
    int _color;
    unsigned int _marginTop;
    unsigned int _marginLeft;
    unsigned int _marginRight;
    int _animationSpeed;
    TextBoxAnimationState _animationState = TextBoxAnimationState::RUNNING;
    unsigned int _animationTimePassed = 0;
    unsigned int _animationCursorCharCount = 0;
    unsigned int _animationCursorLine = 0;
    unsigned int _animationCursorLinePos = 0;
    TextBox* _above = nullptr;
};

#endif // TEXTBOX_HPP
