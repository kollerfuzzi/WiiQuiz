#include "qaquestionfreetext.hpp"
#include "stringutils.hpp"

QAQuestionFreeText::QAQuestionFreeText(Question question) : QAQuestion(question) {

}

QAQuestionFreeText::~QAQuestionFreeText() {
    for (auto const& [key, val]  : _playerAnswerMap) {
        delete val;
    }
}

void QAQuestionFreeText::init() {
    QAQuestion::init();
}

void QAQuestionFreeText::_startInputState() {
    _createQuestionAndTimeLeftText();
    _client->askQuestion(_question);
}

void QAQuestionFreeText::_startShowAnswersState() {
    _client->endQuestionLoadAnswers();
    for (Answer& answer : _state->getAnswers()) {
        std::string playerAnswer;
        playerAnswer += answer.getPlayer()->getName();
        playerAnswer += ": "; 
        std::vector<std::string> playerAnswers = answer.getAnswers();
        playerAnswer += StringUtils::join(playerAnswers, " | ");
        TextBox* playerAnswerTextBox = TextBox::builder()
            .text(playerAnswer)
            .color(RGBA(230, 230, 230, 255))
            .font(_resources->getFont(Font::DEFAULT_FONT))
            .fontSize(25)
            .marginTop(100 + 25 * _textQuestion->lineCount())
            .animationSpeed(50)
            .build();
        if (_textAnswers.size() > 0) {
            TextBox* aboveCurrent = _textAnswers[_textAnswers.size() - 1];
            playerAnswerTextBox->setBelow(aboveCurrent);
        }
        _textAnswers.push_back(playerAnswerTextBox);
        _playerAnswerMap[answer.getPlayer()] = playerAnswerTextBox;
    }
}

void QAQuestionFreeText::_startShowSolutionState() {
    _client->loadAnswers();
    for (Answer& answer : _state->getAnswers()) {
        TextBox* playerAnswerBox = _playerAnswerMap[answer.getPlayer()];
        if (answer.isApproved() || _question.areAnswersCorrect(answer.getAnswers())) {
            playerAnswerBox->setColor(RGBA(155, 255, 150, 255));
            playerAnswerBox->appendAndDisplay(_getPointsString());
            answer.getPlayer()->addPoints(_questionPoints);
        } else {
            playerAnswerBox->setColor(RGBA(255, 150, 150, 255));
        }
    }
    _client->setPoints();
}
