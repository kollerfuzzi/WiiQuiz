#ifndef QASCOREBOARD_HPP
#define QASCOREBOARD_HPP

#include "quizaction.hpp"
#include "textbox.hpp"
#include "player.hpp"

class QAScoreboard : public QuizAction {
public:
    QAScoreboard();
    ~QAScoreboard();
    void update(const Clock &clock);
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
    TextBox* _title;
    TextBox* _playerText;
    TextBox* _points;
    bool _initialized = false;
    float _bgAnimation = 0.0f;
};

#endif // QASCOREBOARD_HPP
