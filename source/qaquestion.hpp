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
#include "confirm.hpp"

enum QAQuestionState {
    NOT_STARTED = 0,
    INPUT = 1,
    SHOW_ANSWERS = 2,
    SHOW_SOLUTION = 3,
    WAIT_FOR_CONTINUE = 4
};

class QAQuestion;

struct QAQuestionStateDef {
    s32 time;
    void (QAQuestion::*transition)();
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
protected:
    virtual void init();
    void _manageState();
    void _goToState(QAQuestionState state, void (QAQuestion::*transition)());
    virtual void _startInputState();
    void _createQuestionAndTimeLeftText();
    void _createAnswersText();
    virtual void _startShowAnswersState();
    virtual void _startShowSolutionState();
    std::string _getPointsString();
    virtual void _startContinueState();
    std::vector<Player*> _getPlayersWithAnswer(std::string answer);
    std::vector<Player*> _getPlayersWithCorrectAnswers();
    bool _hasPlayerAnswer(Player* player, std::string answer);
    void _cleanup();
    std::map<QAQuestionState, QAQuestionStateDef> _timePerState;
    Question _question;
    QAQuestionState _questionState = QAQuestionState::NOT_STARTED;
    bool _initialized = false;
    bool _done = false;
    s32 _timePassed = 0;
    TextBox* _textQuestion = nullptr;
    std::vector<TextBox*> _textAnswers;
    TextBox* _textTimeLeft = nullptr;
    Confirm* _continueConfirm = nullptr;
    float _bgAnimation = 0.0f;
    u32 _questionPoints = 100;
    s32 _answerTime = 10000;
};

#endif // QAQUESTION_HPP
