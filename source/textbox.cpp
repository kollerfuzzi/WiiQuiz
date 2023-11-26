#include "textbox.hpp"

void TextBox::setText(std::string text) {
    _textContent.clear();
    _textBuffer.clear();
    _animationTimePassed = 0;
    _animationCursorCharCount = 0;
    _animationCursorLine = 0;
    _animationCursorLinePos = 0;
    _animationState = TextBoxAnimationState::RUNNING;

    std::string line;
    for (auto &character : text) {
        line += character;
        GRRLIB_2dMode();
        bool lineOverflow = GRRLIB_WidthTTF(_font, line.c_str(), _fontSize)
                                + _marginLeft
                            > SCREEN_WIDTH - _marginRight;
        bool breakLine = character == '\n';

        if (lineOverflow || breakLine) {
            std::string carry;
            carry += character;
            line.pop_back();
            _textContent.push_back(line);
            line.clear();
            if (!breakLine) {
                line += carry;
            }
        }
    }

    if (line.empty()) {
        return;
    }

    _textContent.push_back(line);
}

void TextBox::setColor(int color) {
    _color = color;
}

void TextBox::setAnimationSpeed(unsigned int speed) {
    _animationSpeed = speed;
}

void TextBox::update(Clock &clock) {
    if (_animationState == TextBoxAnimationState::TERMINATED) {
        return;
    }

    if (_animationSpeed == NO_ANIMATION || _textContent.empty()) {
        copyBufferToContent();
        return;
    }

    _animationTimePassed += static_cast<int>(clock.timeElapsedMillis());
    unsigned int expectedCursorPos = _animationTimePassed
                                     / _animationSpeed;
    while (_animationCursorCharCount <= expectedCursorPos) {
        // advance cursor
        if (_animationCursorLinePos
            >= _textContent[_animationCursorLine].size()) {
            _animationCursorLine++;
            _animationCursorLinePos = 0;
        }

        if (_animationCursorLine >= _textContent.size()) {
            _animationState = TextBoxAnimationState::TERMINATED;
            break;
        }

        // copy text
        if (_textBuffer.size() == _animationCursorLine) {
            _textBuffer.emplace_back();
        }

        char currentChar = _textContent[_animationCursorLine]
                                             [_animationCursorLinePos];
        _textBuffer[_animationCursorLine] += currentChar;
        _animationCursorCharCount++;
        _animationCursorLinePos++;
    }
}

void TextBox::copyBufferToContent() {
    _textBuffer = _textContent;
}

void TextBox::render() {
    for (size_t line = 0; line < _textBuffer.size(); line++) {
        GRRLIB_PrintfTTF(_marginLeft + 2,
                         _marginTop + line * _fontSize * 1.25 + 2,
                         _font, _textBuffer[line].c_str(),
                         _fontSize, RGBA(0, 0, 0, 255));
        GRRLIB_PrintfTTF(_marginLeft,
                         _marginTop + line * _fontSize * 1.25,
                         _font, _textBuffer[line].c_str(),
                         _fontSize, _color);
    }
}

bool TextBox::isDone() {
    return false;
}

TextBoxAnimationState TextBox::getAnimationState() {
    return _animationState;
}

size_t TextBox::lineCount() {
    return _textContent.size();
}

TextBox::Builder TextBox::builder() {
    return TextBox::Builder();
}

TextBox::TextBox(GRRLIB_Font *font, unsigned int fontSize, int color,
                 unsigned int marginTop, unsigned int marginLeft,
                 unsigned int marginRight, int animationSpeed) {
    _font = font;
    _fontSize = fontSize;
    _color = color;
    _marginTop = marginTop;
    _marginLeft = marginLeft;
    _marginRight = marginRight;
    _animationSpeed = animationSpeed;
}

TextBox::Builder& TextBox::Builder::font(GRRLIB_Font *font) {
    _font = font;
    return *this;
}

TextBox::Builder& TextBox::Builder::fontSize(int fontSize) {
    _fontSize = fontSize;
    return *this;
}

TextBox::Builder& TextBox::Builder::text(std::string text) {
    _text = text;
    return *this;
}

TextBox::Builder& TextBox::Builder::color(int color) {
    _color = color;
    return *this;
}

TextBox::Builder& TextBox::Builder::marginTop(int marginTop) {
    _marginTop = marginTop;
    return *this;
}

TextBox::Builder& TextBox::Builder::marginLeft(int marginLeft) {
    _marginLeft = marginLeft;
    return *this;
}

TextBox::Builder& TextBox::Builder::marginRight(int marginRight) {
    _marginRight = marginRight;
    return *this;
}

TextBox::Builder& TextBox::Builder::animationSpeed(int animationSpeed) {
    _animationSpeed = animationSpeed;
    return *this;
}

TextBox* TextBox::Builder::build() {
    TextBox* box = new TextBox(_font, _fontSize,
                          _color, _marginTop,
                          _marginLeft, _marginRight,
                          _animationSpeed);

    box->setText(_text);
    return box;
}
