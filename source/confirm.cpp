#include "confirm.hpp"


Confirm::Confirm(Resources* resources, std::string prompt, Remote remote,
                 Button button, bool enabled) {
    _resources = resources;
    _prompt = prompt;
    _remote = remote;
    _button = button;
    _enabled = enabled;
}

Confirm::~Confirm() {
    if (_promptTextbox != nullptr) {
        delete _promptTextbox;
    }
}

void Confirm::update(Clock& clock) {
    _init();
    _confirmTimer += clock.timeElapsedMillis();
    if (!_enabled) {
        return;
    }
    _confirmed = (WiiMote::buttonPressed(_remote, _button) || _confirmed)
                 && _confirmTimer > 1000;
    _promptTextbox->update(clock);
}

void Confirm::render() {
    if (_enabled) {
        _promptTextbox->render();
    }
}

bool Confirm::isConfirmed() {
    return _confirmed;
}

void Confirm::setEnabled(bool enabled) {
    _enabled = enabled;
}

bool Confirm::isDone() {
    return false;
}

Confirm::Builder Confirm::builder() {
    return Confirm::Builder();
}

void Confirm::_init() {
    if (_initialized) {
        return;
    }

    _promptTextbox = TextBox::builder()
        .font(_resources->get(Font::C64FONT))
        .color(RGBA(255, 255, 255, 255))
        .text(_prompt)
        .animationSpeed(NO_ANIMATION)
        .marginTop(450)
        .marginLeft(50)
        .fontSize(20)
        .build();

    _initialized = true;
}

Confirm::Builder& Confirm::Builder::resources(Resources* resources) {
    _resources = resources;
    return *this;
}

Confirm::Builder& Confirm::Builder::prompt(std::string prompt) {
    _prompt = prompt;
    return *this;
}

Confirm::Builder& Confirm::Builder::remote(Remote remote) {
    _remote = remote;
    return *this;
}

Confirm::Builder& Confirm::Builder::button(Button button) {
    _button = button;
    return *this;
}

Confirm::Builder &Confirm::Builder::enabled(bool enabled) {
    _enabled = enabled;
    return *this;
}

Confirm* Confirm::Builder::build() {
    return new Confirm(_resources, _prompt, _remote, _button, _enabled);
}
