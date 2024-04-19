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
    QAQuestion(Question question);
    ~QAQuestion();
    void update(Clock &clock);
    void render();
    bool isDone();
    void reset();
    Question getQuestion();

    class Builder {
    public:
        Builder& question(Question question);
        QAQuestion* build();
    private:
        Question _question;
    };
    static Builder builder();
private:
    void init();
    void _manageState();
    std::vector<Player*> _getPlayersWithAnswer(std::string answer);
    std::vector<Player*> _getPlayersWithCorrectAnswers();
    bool _hasPlayerAnswer(Player* player, std::string answer);
    void _cleanup();
    Question _question;
    QAQuestionState _questionState = QAQuestionState::INPUT;
    bool _initialized = false;
    bool _done = false;
    u32 _timePassed = 0;
    TextBox* _textQuestion = nullptr;
    std::vector<TextBox*> _textAnswers;
    TextBox* _textTimeLeft = nullptr;
    float _bgAnimation = 0.0f;
    u32 _questionPoints = 100;
    u32 _answerTime = 10000;
};

#endif // QAQUESTION_HPP
