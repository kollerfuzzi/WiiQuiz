#ifndef QASTART_HPP
#define QASTART_HPP

#include <cmath>
#include "quizaction.hpp"
#include "wiiuse/wpad.h"
#include "grrlib.h"
#include "confirm.hpp"

class QAStart : public QuizAction {
public:
    QAStart();
    ~QAStart();
    void init();
    void update(const Clock &clock);
    void render();
    bool isDone();

    class Builder {
    public:
        QAStart* build();
    private:
    };
    static Builder builder();
private:
    bool _initialized = false;
    bool _started = false;
    f32 _lightx=0.0f;
    int32_t _loadTimer = 0;
    TextBox* _welcomeText = nullptr;
    TextBox* _playerText = nullptr;
    Confirm* _startConfirm = nullptr;
};

#endif // QASTART_HPP
