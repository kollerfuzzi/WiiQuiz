#ifndef QAQUESTION_HPP
#define QAQUESTION_HPP

#include <string>
#include <map>
#include <cstdint>
#include <memory>

#include "quizaction.hpp"
#include "textbox.hpp"

class QAQuestion : public QuizAction {
public:

    ~QAQuestion();
    void update(const Clock &clock);
    void render();
    bool isDone();

    class Builder {
    public:
        Builder& question(std::string question);
        Builder& correctAnswer(std::string answer);
        Builder& wrongAnswer(std::string answer);
        QAQuestion* build();
    private:
        std::string _question;
        std::vector<std::string> _answers;
        std::vector<int> _correctAnswers;
    };
    static Builder builder();
private:
    QAQuestion(std::string question, std::vector<std::string> answers,
               std::vector<int> correctAnswers);
    void init();
    std::string _question;
    std::vector<std::string> _answers;
    std::vector<int> _correctAnswers;
    bool _initialized = false;
    bool _done = false;
    int32_t _timePassed;
    TextBox* _textQuestion;
    TextBox* _textAnswers;
};

#endif // QAQUESTION_HPP
