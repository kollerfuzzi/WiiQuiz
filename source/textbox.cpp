#include "textbox.h"

void TextBox::setText(std::string text) {
    //this->_textContent.push_back(text);
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
