#include "textbox.hpp"
#include <codecvt>
#include <locale>
#include "bsod.hpp"

void TextBox::setText(std::string text) {
    _sourceString = text;
    _textContent.clear();
    _textBuffer.clear();
    _animationTimePassed = 0;
    _animationCursorCharCount = 0;
    _animationCursorLine = 0;
    _animationCursorLinePos = 0;
    _animationState = TextBoxAnimationState::RUNNING;

    std::wstring line;
    for (auto &character : _utf8ToUtf32(text)) {
        line += character;
        GRRLIB_2dMode();
        bool lineOverflow = GRRLIB_WidthTTFW(_font, line.c_str(), _fontSize)
                                + _marginLeft
                            > rmode->fbWidth - _marginRight;
        bool breakLine = character == '\n';

        if (lineOverflow || breakLine) {
            std::wstring carry;
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

void TextBox::setAndDisplayText(std::string text) {
    setText(text);
    copyBufferToContent();
}

void TextBox::appendAndDisplay(std::string text) {
    _sourceString += text;
    setText(_sourceString);
    copyBufferToContent();
}

void TextBox::appendAndDisplayLine(std::string text) {
    _textContent.push_back(_utf8ToUtf32(text));
    copyBufferToContent();
}

void TextBox::setColor(int color) {
    _color = color;
}

void TextBox::setAnimationSpeed(unsigned int speed) {
    _animationSpeed = speed;
}

void TextBox::setBelow(TextBox* above) {
    _above = above;
}

u32 TextBox::getTop() {
    return getBottom() - getHeight();
}

u32 TextBox::getBottom() {
    int bottom = _marginTop;
    if (_above != nullptr) {
        bottom += _above->getBottom();
    }
    bottom += getHeight();
    return bottom;
}

u32 TextBox::getHeight() {
    return _fontSize * _textBuffer.size() * 1.25 + 2;
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
    _animationSpeed = NO_ANIMATION;
}

void TextBox::render() {
    for (size_t line = 0; line < _textBuffer.size(); line++) {
        GRRLIB_PrintfTTFW(_marginLeft + 2,
                         getTop() + line * _fontSize * 1.25 + 2,
                         _font, _textBuffer[line].c_str(),
                         _fontSize, RGBA(0, 0, 0, 255));
        GRRLIB_PrintfTTFW(_marginLeft,
                         getTop() + line * _fontSize * 1.25,
                         _font, _textBuffer[line].c_str(),
                         _fontSize, _color);
    }
}

bool TextBox::isDone() {
    return false;
}

void TextBox::reset() {
    setText(_sourceString);
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

TextBox::TextBox(GRRLIB_Font* font,
                 unsigned int fontSize,
                 int color,
                 unsigned int marginTop,
                 unsigned int marginLeft,
                 unsigned int marginRight,
                 int animationSpeed,
                 TextBox* above) {
    _font = font;
    _fontSize = fontSize;
    _color = color;
    _marginTop = marginTop;
    _marginLeft = marginLeft;
    _marginRight = marginRight;
    _animationSpeed = animationSpeed;
    _above = above;
}

std::wstring TextBox::_utf8ToUtf32(std::string str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> utf32conv;
    std::wstring utf32 = utf32conv.from_bytes(str);
    return utf32;
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

TextBox::Builder& TextBox::Builder::below(TextBox* above) {
    _above = above;
    return *this;
}

TextBox* TextBox::Builder::build() {
    if (_font == nullptr) {
        BSOD::raise("TextBox: font is required");
    }
    TextBox* box = new TextBox(_font, _fontSize,
                          _color, _marginTop,
                          _marginLeft, _marginRight,
                          _animationSpeed, _above);

    box->setText(_text);
    return box;
}
