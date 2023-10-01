#include "textbox.hpp"

void TextBox::setText(std::string text) {
    this->_textContent.clear();
    this->_textBuffer.clear();

    std::string line;
    for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
        line += *it;
        GRRLIB_2dMode();
        bool lineOverflow = GRRLIB_WidthTTF(this->_font, line.c_str(),
                                this->_fontSize) + this->_marginLeft
                                > SCREEN_WIDTH - this->_marginRight;
        bool breakLine = *it == '\n';

        if (lineOverflow || breakLine) {
            std::string carry;
            carry += *it;
            line.pop_back();
            this->_textContent.push_back(line);
            line.clear();
            if (!breakLine) {
                line += carry;
            }
        }

        bool stringEnd = (it + 1) == text.end();
        if (stringEnd) {
            this->_textContent.push_back(line);
        }
    }
}

void TextBox::renderText() {
    for (int line = 0 ; line < this->_textContent.size(); line++) {
        GRRLIB_PrintfTTF(this->_marginLeft,
            this->_marginTop + line * this->_fontSize * 1.25, this->_font,
            this->_textContent[line].c_str(), this->_fontSize, this->_color);
    }
}

TextBox::Builder TextBox::builder() {
    return TextBox::Builder();
}

TextBox::TextBox(GRRLIB_Font *font, int fontSize, int color,
                 int marginTop, int marginLeft, int marginRight) {
    this->_font = font;
    this->_fontSize = fontSize;
    this->_color = color;
    this->_marginTop = marginTop;
    this->_marginLeft = marginLeft;
    this->_marginRight = marginRight;
}

TextBox::Builder &TextBox::Builder::font(GRRLIB_Font *font) {
    this->_font = font;
    return *this;
}

TextBox::Builder &TextBox::Builder::fontSize(int fontSize) {
    this->_fontSize = fontSize;
    return *this;
}

TextBox::Builder &TextBox::Builder::text(std::string text) {
    this->_text = text;
    return *this;
}

TextBox::Builder &TextBox::Builder::color(int color) {
    this->_color = color;
    return *this;
}

TextBox::Builder &TextBox::Builder::marginTop(int marginTop) {
    this->_marginTop = marginTop;
    return *this;
}

TextBox::Builder &TextBox::Builder::marginLeft(int marginLeft) {
    this->_marginLeft = marginLeft;
    return *this;
}

TextBox::Builder &TextBox::Builder::marginRight(int marginRight) {
    this->_marginRight = marginRight;
    return *this;
}

TextBox TextBox::Builder::build() {
    TextBox box = TextBox(this->_font, this->_fontSize,
            this->_color, this->_marginTop,
            this->_marginLeft, this->_marginRight);
    box.setText(this->_text);
    return box;
}
