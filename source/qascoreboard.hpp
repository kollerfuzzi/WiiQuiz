#ifndef QASCOREBOARD_HPP
#define QASCOREBOARD_HPP

#include "quizaction.hpp"
#include "textbox.hpp"
#include "player.hpp"
#include "confirm.hpp"

class QAScoreboard : public QuizAction {
public:
    QAScoreboard();
    ~QAScoreboard();
    void update(Clock &clock);
    void render();
    bool isDone();

    class Builder {
    public:
        QAScoreboard* build();
    private:
    };
    static Builder builder();
private:
    void init();
    TextBox* _title = nullptr;
    TextBox* _playerText = nullptr;
    TextBox* _points = nullptr;
    Confirm* _confirm = nullptr;
    bool _initialized = false;
    bool _isDone = false;
    float _bgAnimation = 0.0f;
};

#endif // QASCOREBOARD_HPP
