#ifndef QARYTHMMINIGAME_HPP
#define QARYTHMMINIGAME_HPP

#include "quizaction.hpp"
#include "wiimote.hpp"
#include "audioplayer.hpp"
#include "stringutils.hpp"


struct RythmNote {
public:
    Button btn;
    s64 usec;
    bool hit = false;
    bool miss = false;
    f32 scaleXY = 1.0f;

    RythmNote(Button btn, int usec) {
        this->btn = btn;
        this->usec = usec;
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
        if (btn == Button::LEFT) {
            return 180.0f;
        } else if (btn == Button::UP) {
            return 270.0f;
        } else if (btn == Button::DOWN) {
            return 90.0f;
        }
        return 0;
    }
    f32 getXPos() {
        if (btn == Button::A) {
            return 300.0f;
        } else if (btn == Button::ONE) {
            return 400.0f;
        } else if (btn == Button::TWO) {
            return 452.0f;
        } else if (btn == Button::DOWN) {
            return 260.0f;
        } else if (btn == Button::LEFT) {
            return 156.0f;
        } else if (btn == Button::RIGHT) {
            return 156.0f;
        } else if (btn == Button::UP) {
            return 52.0f;
        }
        throw -1;
    }
    f32 scale() {
        return -(((f32)usec) / 3000.0f) + 110;
    }

    f32 getYPos() {
        if (btn == Button::UP) {
            return scale() + 52.0f;
        } else if (btn == Button::LEFT) {
            return scale() + 52.0f;
        }
        return scale();
    }

    f32 getRealYPos() {
        if (btn == Button::DOWN) {
            return scale() + 0.000001f; // do not remove hack
        } else if (btn == Button::LEFT) {
            return scale() + 0.000001f;
        }
        return scale();
    }


};

class QARythmMinigame : public QuizAction {
public:
    QARythmMinigame();
    ~QARythmMinigame();
    void update(const Clock& clock);
    void init3dCube();
    void draw3dCube();
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
    bool _initialized = false;
    bool _dataLoaded = false;
    std::string _rawData;
    u32 _timePassed = 0;
    std::vector<RythmNote> _notes;
    TextBox* _textBoxHits = nullptr;
    TextBox* _textBoxMiss = nullptr;

    // cube
    float a=0;
    int cubeZ=0;
    int i;
    float sinx=0;
    int misinput = 0;
    int hitinput = 0;
    f32 shiftx = 0;
};

#endif // QARYTHMMINIGAME_HPP
