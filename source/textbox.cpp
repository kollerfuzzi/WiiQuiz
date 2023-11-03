#include "textbox.hpp"

void TextBox::setText(std::string text) {
    this->_textContent.clear();
    this->_textBuffer.clear();

    std::string line;
    for (auto &character : text) {
        line += character;
        GRRLIB_2dMode();
        bool lineOverflow = GRRLIB_WidthTTF(this->_font, line.c_str(), this->_fontSize)
                                + this->_marginLeft
                            > SCREEN_WIDTH - this->_marginRight;
        bool breakLine = character == '\n';

        if (lineOverflow || breakLine) {
            std::string carry;
            carry += character;
            line.pop_back();
            this->_textContent.push_back(line);
            line.clear();
            if (!breakLine) {
                line += carry;
            }
        }
    }

    if (line.empty()) {
        return;
    }

    this->_textContent.push_back(line);
}

void TextBox::update(const Clock &clock) {
    if (this->_animationSpeed == ANIMATION_END) {
        return;
    }

    if (this->_animationSpeed == NO_ANIMATION) {
        this->_textBuffer = this->_textContent;
        return;
    }

    this->_animationTimePassed += static_cast<int>(clock.timeElapsedMillis());
    unsigned int expectedCursorPos = this->_animationTimePassed
                                     / this->_animationSpeed;
    while (this->_animationCursorCharCount <= expectedCursorPos) {
        // advance cursor
        if (this->_animationCursorLinePos
            >= this->_textContent[this->_animationCursorLine].size()) {
            this->_animationCursorLine++;
            this->_animationCursorLinePos = 0;
        }

        if (this->_animationCursorLine >= this->_textContent.size()) {
            this->_animationSpeed = ANIMATION_END;
            break;
        }

        // copy text
        if (this->_textBuffer.size() == this->_animationCursorLine) {
            this->_textBuffer.emplace_back();
        }

        char currentChar = this->_textContent[this->_animationCursorLine]
                                             [this->_animationCursorLinePos];
        this->_textBuffer[this->_animationCursorLine] += currentChar;
        this->_animationCursorCharCount++;
        this->_animationCursorLinePos++;
    }
}

void TextBox::render() {
    for (size_t line = 0; line < this->_textBuffer.size(); line++) {
        GRRLIB_PrintfTTF(this->_marginLeft + 2,
                         this->_marginTop + line * this->_fontSize * 1.25 + 2,
                         this->_font, this->_textBuffer[line].c_str(),
                         this->_fontSize, RGBA(0, 0, 0, 255));
        GRRLIB_PrintfTTF(this->_marginLeft,
                         this->_marginTop + line * this->_fontSize * 1.25,
                         this->_font, this->_textBuffer[line].c_str(),
                         this->_fontSize, this->_color);
    }
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
    this->_font = font;
    this->_fontSize = fontSize;
    this->_color = color;
    this->_marginTop = marginTop;
    this->_marginLeft = marginLeft;
    this->_marginRight = marginRight;
    this->_animationSpeed = animationSpeed;
}

TextBox::Builder& TextBox::Builder::font(GRRLIB_Font *font) {
    this->_font = font;
    return *this;
}

TextBox::Builder& TextBox::Builder::fontSize(int fontSize) {
    this->_fontSize = fontSize;
    return *this;
}

TextBox::Builder& TextBox::Builder::text(std::string text) {
    this->_text = text;
    return *this;
}

TextBox::Builder& TextBox::Builder::color(int color) {
    this->_color = color;
    return *this;
}

TextBox::Builder& TextBox::Builder::marginTop(int marginTop) {
    this->_marginTop = marginTop;
    return *this;
}

TextBox::Builder& TextBox::Builder::marginLeft(int marginLeft) {
    this->_marginLeft = marginLeft;
    return *this;
}

TextBox::Builder& TextBox::Builder::marginRight(int marginRight) {
    this->_marginRight = marginRight;
    return *this;
}

TextBox::Builder& TextBox::Builder::animationSpeed(int animationSpeed) {
    this->_animationSpeed = animationSpeed;
    return *this;
}

TextBox* TextBox::Builder::build() {
    TextBox* box = new TextBox(this->_font, this->_fontSize,
                          this->_color, this->_marginTop,
                          this->_marginLeft, this->_marginRight,
                          this->_animationSpeed);
    box->setText(this->_text);
    return box;
}
