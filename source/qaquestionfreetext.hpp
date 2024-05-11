
#ifndef QAQUESTIONFREETEXT_HPP
#define QAQUESTIONFREETEXT_HPP

#include "qaquestion.hpp"
#include "question.hpp"

class QAQuestionFreeText : public QAQuestion {
public:
    QAQuestionFreeText(Question question);
    ~QAQuestionFreeText();
protected:
    void init() override;
    void _startInputState() override;
    void _startShowAnswersState() override;
    void _startShowSolutionState() override;
    std::map<Player*, TextBox*> _playerAnswerMap;
};

#endif // QAQUESTIONFREETEXT_HPP
