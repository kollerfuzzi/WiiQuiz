#include "qarythmminigame.hpp"
#include "grrlib.h"

QARythmMinigame::QARythmMinigame() {

}

QARythmMinigame::~QARythmMinigame() {

}

void QARythmMinigame::update(const Clock& clock) {
    _init();
    for (RythmNote& note : _notes) {
        note.ypos += 6;
    }
}

void QARythmMinigame::render() {
    GRRLIB_SetBackgroundColour(100, 100, 100, 100);

    for (RythmNote& note : _notes) {
        GRRLIB_DrawImg(note.getXPos(), note.getYPos(),
                       _resources->get(note.getTexture()), note.getRotation(),
                       1, 1,
                       RGBA(255, 255, 255, 255));
    }/*
    GRRLIB_DrawImg(0, 100, _resources->get(Texture::BTN_DPAD), 0, 1, 1,
                   RGBA(255, 255, 255, 255));

    GRRLIB_DrawImg(100, 100, _resources->get(Texture::BTN_A), 0, 1, 1,
                   RGBA(255, 255, 255, 255));

    GRRLIB_DrawImg(200, 100, _resources->get(Texture::BTN_ONE), 0, 1, 1,
                   RGBA(255, 255, 255, 255));

    GRRLIB_DrawImg(300, 100, _resources->get(Texture::BTN_TWO), 0, 1, 1,
                   RGBA(255, 255, 255, 255));*/
}

bool QARythmMinigame::isDone() {
    return false;
}

QARythmMinigame::Builder QARythmMinigame::builder() {
    return QARythmMinigame::Builder();
}

void QARythmMinigame::_init()
{
    if (_initialized) {
        return;
    }

    RythmNote note(Button::UP, 50);

    for (int i = 0; i > -100000; i -= 100) {
        _notes.emplace_back(Button::UP, i);
        _notes.emplace_back(Button::LEFT, i);
        _notes.emplace_back(Button::RIGHT, i);
        _notes.emplace_back(Button::DOWN, i);
        _notes.emplace_back(Button::A, i);
        _notes.emplace_back(Button::ONE, i);
        _notes.emplace_back(Button::TWO, i);
    }

    _initialized = true;
}

QARythmMinigame* QARythmMinigame::Builder::build() {
    return new QARythmMinigame;
}
