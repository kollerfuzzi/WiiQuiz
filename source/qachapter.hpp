#ifndef QACHAPTER_HPP
#define QACHAPTER_HPP

#include <string>
#include "quizaction.hpp"
#include "clock.hpp"
#include "wiimote.hpp"

class QAChapter : QuizAction {
public:
    QAChapter(std::string title);
    ~QAChapter();
    void update(const Clock &clock);
    void render();
    bool isDone();
    class Builder {
    public:
        Builder& title(std::string title);
        QAChapter* build();
    private:
        std::string _title;
    };
    static Builder builder();
private:
    void _init();
    bool _initialized;
    std::string _title;
    TextBox* _titleBox;
    TextBox* _continueText;
};

#endif // QACHAPTER_HPP
