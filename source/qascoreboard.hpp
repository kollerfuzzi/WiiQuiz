#ifndef QASCOREBOARD_HPP
#define QASCOREBOARD_HPP

#include <algorithm>

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

    TextBox* _playerText;
    TextBox* _points;
    bool _initialized = false;
};

#endif // QASCOREBOARD_HPP
