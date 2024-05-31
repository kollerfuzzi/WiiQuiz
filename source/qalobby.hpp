#ifndef QALOBBY_HPP
#define QALOBBY_HPP

#include "quizaction.hpp"
#include "wiiuse/wpad.h"
#include "grrlib.h"
#include "confirm.hpp"
#include "audioplayer.hpp"
#include "swinginglights.hpp"

class QALobby : public QuizAction {
public:
    QALobby();
    ~QALobby();
    void init();
    void update(Clock &clock);
    void render();
    bool isDone();
    void reset();
    class Builder {
    public:
        QALobby* build();
    private:
    };
    static Builder builder();
private:
    void _cleanup();
    bool _initialized = false;
    bool _started = false;
    int32_t _loadTimer = 0;
    TextBox* _welcomeText = nullptr;
    TextBox* _playerText = nullptr;
    Confirm* _startConfirm = nullptr;
    SwingingLights* _swingingLights = nullptr;
};

#endif // QALOBBY_HPP
