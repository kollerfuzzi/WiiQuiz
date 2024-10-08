#include "qachapter.hpp"

QAChapter::QAChapter(std::string title) {
    _title = title;
}

QAChapter::~QAChapter() {
    _cleanup();
}

void QAChapter::update(Clock &clock) {
    _init();
    _titleBox->update(clock);
    _confirm->update(clock);
    _confirm->setEnabled(_titleBox->getAnimationState()
                         == TextBoxAnimationState::TERMINATED);
}

void QAChapter::render() {
    _titleBox->render();
    _confirm->render();
}

bool QAChapter::isDone() {
    if (_confirm != nullptr) {
        return _confirm->isConfirmed();
    }
    return false;
}

void QAChapter::reset() {
    _cleanup();
}

QAChapter::Builder QAChapter::builder() {
    return QAChapter::Builder();
}

void QAChapter::_init() {
    if (_initialized) {
        return;
    }

    _titleBox = TextBox::builder()
        .text(_title)
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(40)
        .marginTop(150)
        .marginLeft(50)
        .marginRight(50)
        .animationSpeed(50)
        .build();

    _confirm = Confirm::builder()
        .resources(_resources)
        .enabled(false)
        .build();

    _initialized = true;
}

void QAChapter::_cleanup() {
    if (_titleBox != nullptr) {
        delete _titleBox;
        _titleBox = nullptr;
    }
    if (_confirm != nullptr) {
        delete _confirm;
        _confirm = nullptr;
    }
    _initialized = false;
}

QAChapter::Builder& QAChapter::Builder::title(std::string title) {
    _title = title;
    return *this;
}

QAChapter* QAChapter::Builder::build() {
    return new QAChapter(_title);
}
