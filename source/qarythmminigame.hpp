#ifndef QARYTHMMINIGAME_HPP
#define QARYTHMMINIGAME_HPP

#include "wiimote.hpp"
#include "audioplayer.hpp"
#include "stringutils.hpp"
#include "textbox.hpp"
#include "qasingleplayer.hpp"
#include "confirm.hpp"

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
        } else if (btn == Button::UP) {
            return Texture::BTN_DPAD_UP;
        } else if (btn == Button::DOWN) {
            return Texture::BTN_DPAD_DOWN;
        } else if (btn == Button::LEFT) {
            return Texture::BTN_DPAD_LEFT;
        } else if (btn == Button::RIGHT) {
            return Texture::BTN_DPAD_RIGHT;
        } else {
            throw -1;
        }
    }
    f32 getXPos() {
        if (btn == Button::A) {
            return 300.0f;
        } else if (btn == Button::ONE) {
            return 400.0f;
        } else if (btn == Button::TWO) {
            return 452.0f;
        } else if (btn == Button::DOWN) {
            return 176.0f;
        } else if (btn == Button::LEFT) {
            return 52.0f;
        } else if (btn == Button::RIGHT) {
            return 238.0f;
        } else if (btn == Button::UP) {
            return 114.0f;
        }
        throw -1;
    }
    f32 scale() {
        return -(((f32)usec) / 3000.0f) + 110;
    }

    f32 getYPos() {
        return scale() + 52.0f;
    }

    f32 getRealYPos() {
        return scale();
    }

};

enum RythmMinigameState {
    NOT_INITIALIZED,
    SHOW_TUTORIAL,
    PLAYING,
    ENDING,
    DONE
};

class QARythmMinigame : public QASinglePlayer {
public:
    QARythmMinigame(std::string audioPath, std::string imgPath, std::string data, int delayMs, int maxPts);
    ~QARythmMinigame();
    void update(Clock& clock);
    void init3dCube();
    void draw3dCubes();
    void render();
    bool isDone();
    void reset();
    std::set<std::string> getResourcePaths() override;
    class Builder {
    public:
        Builder& img(std::string imgPath);
        Builder& audio(std::string audioPath);
        Builder& data(std::string data);
        Builder& delayMs(int ms);
        Builder& maxPts(int maxPts);
        QARythmMinigame* build();
    private:
        std::string _imgPath;
        std::string _audioPath;
        std::string _data;
        int _delayMs;
        int _maxPts = 200;
    };
    static Builder builder();
private:
    void _init();
    void _cleanup();
    RythmMinigameState _gameState = RythmMinigameState::NOT_INITIALIZED;
    std::string _rawData;
    std::string _cubeImgPath;
    std::string _audioPath;
    u32 _timePassed = 0;
    std::vector<RythmNote> _notes;
    TextBox* _textBoxHits = nullptr;
    TextBox* _textBoxMiss = nullptr;
    TextBox* _textBoxScore = nullptr;
    TextBox* _textBoxPlayer = nullptr;
    Confirm* _confirmStart = nullptr; 

    // cube
    float _a = 0;
    int _cubeZ = 0;
    float _sinx=0;

    int _misinput = 500;
    int _misinputsTotal = 0;
    int _hitinput = 0;
    f32 _shiftx = 0;
    int _delayMs = 0;
    int _maxPts = 200;
    u8 _tutorialVisibility = 0;
    int _endingTimePassed = 0;

    void renderCube(const f32 &x, const f32 &y);
    void updateNote(const Clock &clock, RythmNote &note, size_t &hits, size_t &misses) const;
};

#endif // QARYTHMMINIGAME_HPP
