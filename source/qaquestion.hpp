#ifndef QAQUESTION_HPP
#define QAQUESTION_HPP

#include <string>
#include <map>
#include <cstdint>
#include <memory>

#include "quizaction.hpp"
#include "textbox.hpp"
#include "question.hpp"
#include "answer.hpp"

enum QAQuestionState {
    INPUT,
    SHOW_ANSWERS,
    SHOW_SOLUTION
};

class QAQuestion : public QuizAction {
public:
    ~QAQuestion();
    void update(const Clock &clock);
    void render();
    bool isDone();
    Question toQuestion();

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
    std::vector<Answer> _getCorrectAnswerPlayers();
    void init();
    void _manageState();
    std::string _question;
    std::vector<std::string> _answers;
    std::vector<int> _correctAnswers;
    QAQuestionState _questionState = QAQuestionState::INPUT;
    bool _initialized = false;
    bool _done = false;
    u32 _timePassed = 0;
    TextBox* _textQuestion;
    TextBox* _textAnswers;
    TextBox* _textTimeLeft;
    float _bgAnimation = 0.0f;
    u32 _questionPoints = 100;
    u32 _answerTime = 10000;
};

#endif // QAQUESTION_HPP
