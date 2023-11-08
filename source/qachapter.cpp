#include "qachapter.hpp"

QAChapter::QAChapter(std::string title) {
    _title = title;
}

QAChapter::~QAChapter() {
    delete _titleBox;
}

void QAChapter::update(const Clock &clock) {
    _titleBox->update(clock);
    if (_titleBox->getAnimationState() == TextBoxAnimationState::TERMINATED) {
        _continueText->update(clock);
    }
}

void QAChapter::render() {
    _titleBox->render();
}

bool QAChapter::isDone() {
    return WiiMote::buttonPressed(Remote::R1, Button::A);
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
        .font(_resources->get(Font::C64FONT))
        .fontSize(50)
        .marginTop(200)
        .marginLeft(50)
        .marginRight(50)
        .animationSpeed(50)
        .build();


    _continueText = TextBox::builder()
        .text("Press <A> to continue")
        .color(RGBA(255, 255, 255, 255))
        .font(_resources->get(Font::C64FONT))
        .fontSize(50)
        .marginTop(300)
        .marginLeft(100)
        .marginRight(100)
        .animationSpeed(50)
        .build();

    _initialized = true;
}

QAChapter::Builder& QAChapter::Builder::title(std::string title) {
    _title = title;
    return *this;
}

QAChapter* QAChapter::Builder::build() {
    return new QAChapter(_title);
}
