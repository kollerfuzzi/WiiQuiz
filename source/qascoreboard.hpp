#ifndef QASCOREBOARD_HPP
#define QASCOREBOARD_HPP

#include "quizaction.hpp"
#include "textbox.hpp"

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
    bool _initialized = false;
};

#endif // QASCOREBOARD_HPP
