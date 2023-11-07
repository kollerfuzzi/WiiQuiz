#include "screendebug.hpp"

ScreenDebug* ScreenDebug::_instance = nullptr;

ScreenDebug::ScreenDebug(Resources *resources) {
    _resources = resources;
}

ScreenDebug::~ScreenDebug() {
    delete _textbox;
}

void ScreenDebug::init(Resources *resources) {
    ScreenDebug::_instance = new ScreenDebug(resources);
}

void ScreenDebug::destroy() {
    delete _instance;
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

void ScreenDebug::_printLn(std::string text) {
    _text += text;
    _text += "\n";

    if (_textbox == nullptr) {
        _textbox = TextBox::builder()
                       .text(_text)
                       .font(_resources->get(Font::C64FONT))
                       .fontSize(20)
                       .marginTop(50)
                       .color(RGBA(255, 100, 100, 255))
                       .build();
    } else {
        _textbox->setText(_text);
    }
    _textbox->copyBufferToContent();
}

void ScreenDebug::render() {
    instance()->_render();
}

void ScreenDebug::_render() {
    if (_textbox == nullptr) {
        return;
    }
    _textbox->render();
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
