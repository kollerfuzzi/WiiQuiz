#ifndef QARYTHMMINIGAME_HPP
#define QARYTHMMINIGAME_HPP

#include "quizaction.hpp"
#include "wiimote.hpp"


struct RythmNote {
public:
    Button btn;
    int ypos;

    RythmNote(Button btn, int xpos) {
        this->btn = btn;
        this->ypos = xpos;
    }

    Texture getTexture() {
        if (btn == Button::A) {
            return Texture::BTN_A;
        } else if (btn == Button::ONE) {
            return Texture::BTN_ONE;
        } else if (btn == Button::TWO) {
            return Texture::BTN_TWO;
        } else if (btn == Button::UP || btn == Button::DOWN
                   || btn == Button::LEFT || btn == Button::RIGHT) {
            return Texture::BTN_DPAD;
        } else {
            throw -1;
        }
    }
    f32 getRotation() {
        if (btn == Button::DOWN) {
            return 180.0f;
        } else if (btn == Button::LEFT) {
            return 270.0f;
        } else if (btn == Button::RIGHT) {
            return 90.0f;
        }
        return 0;
    }
    f32 getXPos() {
        if (btn == Button::A) {
            return 300;
        } else if (btn == Button::ONE) {
            return 400;
        } else if (btn == Button::TWO) {
            return 452;
        } else if (btn == Button::DOWN) {
            return 260;
        } else if (btn == Button::LEFT) {
            return 104;
        } else if (btn == Button::RIGHT) {
            return 208;
        } else if (btn == Button::UP) {
            return 52;
        }
        throw -1;
    }
    f32 getYPos() {
        if (btn == Button::DOWN) {
            return ypos + 52;
        } else if (btn == Button::LEFT) {
            return ypos + 52;
        }
        return ypos;
    }

};

class QARythmMinigame : public QuizAction {
public:
    QARythmMinigame();
    ~QARythmMinigame();
    void update(const Clock& clock);
    void render();
    bool isDone();

    class Builder {
    public:
        QARythmMinigame* build();
    private:
    };
    static Builder builder();
private:
    void _init();
    bool _initialized =false;
    std::vector<RythmNote> _notes;
};

#endif // QARYTHMMINIGAME_HPP
