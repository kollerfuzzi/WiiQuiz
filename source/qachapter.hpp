#ifndef QACHAPTER_HPP
#define QACHAPTER_HPP

#include <string>
#include "quizaction.hpp"
#include "clock.hpp"
#include "wiimote.hpp"
#include "confirm.hpp"

class QAChapter : public QuizAction {
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
    bool _initialized = false;
    std::string _title;
    TextBox* _titleBox = nullptr;
    Confirm* _confirm = nullptr;
};

#endif // QACHAPTER_HPP
