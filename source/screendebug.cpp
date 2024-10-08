#include "screendebug.hpp"
#include "textbox.hpp"

ScreenDebug* ScreenDebug::_instance = nullptr;

ScreenDebug::ScreenDebug(GRRLIB_ttfFont* font) {
    _font = font;
}

ScreenDebug::~ScreenDebug() {
    if (_textbox != nullptr) {
        delete _textbox;
    }
}

void ScreenDebug::init(GRRLIB_ttfFont* font) {
    ScreenDebug::_instance = new ScreenDebug(font);
}

void ScreenDebug::destroy() {
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

ScreenDebug* ScreenDebug::instance() {
    return ScreenDebug::_instance;
}

void ScreenDebug::printLn(std::string text) {
    instance()->_printLn(text);
}

void ScreenDebug::print(std::vector<std::string>& lines) {
    for (std::string& line : lines) {
        ScreenDebug::printLn(line);
    }
}

void ScreenDebug::print(std::string lines) {
    _instance->_print(lines);
}

void ScreenDebug::printAndRender(std::string lines) {
    _instance->_printAndRender(lines);
}

void ScreenDebug::setColor(u32 color) {
    _instance->_setColor(color);
}

void ScreenDebug::_printLn(std::string text) {
    if (!_enabled) {
        return;
    }
    text += '\n';

    _print(text);
}

void ScreenDebug::_print(std::string text) {
    if (!_enabled) {
        return;
    }
    _text += text;

    if (_textbox == nullptr) {
        _textbox = TextBox::builder()
                       .text(_text)
                       .font(_font)
                       .fontSize(20)
                       .marginTop(50)
                       .color(_color)
                       .build();
    } else {
        _textbox->setText(_text);
    }
    _textbox->copyBufferToContent();
}

void ScreenDebug::_printAndRender(std::string text) {
    clear();
    print(text);
    render();
    GRRLIB_Render();
    clear();
}

void ScreenDebug::_setColor(u32 color) {
    _color = color;
    if (_textbox != nullptr) {
        _textbox->setColor(_color);
    }
}

void ScreenDebug::render() {
    instance()->_render();
}

void ScreenDebug::disable() {
    instance()->_disable();
}

void ScreenDebug::enable() {
    instance()->_enable();
}

bool ScreenDebug::isEnabled() {
    return instance()->_isEnabled();
}

void ScreenDebug::_render() {
    if (_textbox == nullptr) {
        return;
    }
    _textbox->render();
}

void ScreenDebug::_disable() {
    _enabled = false;
}

void ScreenDebug::_enable() {
    _enabled = true;
}

bool ScreenDebug::_isEnabled() {
    return _enabled;
}

void ScreenDebug::clear() {
    instance()->_clear();
}

void ScreenDebug::_clear() {
    _text = std::string();
    if (_textbox != nullptr) {
        _textbox->setText(_text);
        _textbox->copyBufferToContent();
    }
}
