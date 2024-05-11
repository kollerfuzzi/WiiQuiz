#include "qaquestion.hpp"
#include "bsod.hpp"

#include <cmath>

QAQuestion::QAQuestion(Question question) {
    _question = question;
}

void QAQuestion::init() {
    _timePerState[QAQuestionState::NOT_STARTED] = QAQuestionStateDef(-1, nullptr);
    _timePerState[QAQuestionState::INPUT] = QAQuestionStateDef(_answerTime, &QAQuestion::_startInputState);
    _timePerState[QAQuestionState::SHOW_ANSWERS] = QAQuestionStateDef(7000, &QAQuestion::_startShowAnswersState);
    _timePerState[QAQuestionState::SHOW_SOLUTION] = QAQuestionStateDef(5000, &QAQuestion::_startShowSolutionState);
    _timePerState[QAQuestionState::WAIT_FOR_CONTINUE] = QAQuestionStateDef(-1, &QAQuestion::_startContinueState);
    _initialized = true;
}

void QAQuestion::_manageState() {
    if (_timePassed > 5000 && _timePassed < _answerTime) {
        _textTimeLeft->setAndDisplayText(
            std::to_string(((_answerTime - _timePassed) / 1000) + 1));
    }

    if (_timePassed > _timePerState[_questionState].time && (int) _questionState < _timePerState.size() - 1) {
        _questionState = (QAQuestionState)((int)_questionState + 1);
        _goToState(_questionState, _timePerState[_questionState].transition);
    }
}

void QAQuestion::_goToState(QAQuestionState state, void (QAQuestion::*transition)()) {
    _timePassed = 0;
    _questionState = state;
    ((*this).*(transition))();
}

void QAQuestion::_startInputState() {
    _textQuestion = TextBox::builder()
        .text(_question.getPrompt())
        .font(_resources->get(Font::DEFAULT_FONT))
        .fontSize(25)
        .marginTop(50)
        .animationSpeed(100)
        .build();

    for (std::pair<std::string, bool>& answer : _question.getAnswers()) {
        TextBox* answerBox = TextBox::builder()
            .text(answer.first)
            .color(RGBA(230, 230, 230, 255))
            .font(_resources->get(Font::DEFAULT_FONT))
            .fontSize(25)
            .marginTop(100 + 25 * _textQuestion->lineCount())
            .animationSpeed(100)
            .build();
        if (_textAnswers.size() > 0) {
            TextBox* aboveCurrent = _textAnswers[_textAnswers.size() - 1];
            answerBox->setBelow(aboveCurrent);
        }
        _textAnswers.push_back(answerBox);
    }

    _textTimeLeft = TextBox::builder()
        .color(RGBA(255, 150, 150, 255))
        .font(_resources->get(Font::DEFAULT_FONT))
        .fontSize(35)
        .marginTop(400)
        .build();

    _client->askQuestion(_question);
}

void QAQuestion::_startShowAnswersState() {
    _client->loadAnswers();
    std::vector<Answer> playerAnswers = _state->getAnswers();
    _client->endQuestion();

    for (size_t answerCnt = 0; answerCnt < _question.getAnswers().size(); answerCnt++) {
        std::string answerWithPlayersText = _question.getAnswers()[answerCnt].first;
        std::vector<Player*> playersWithAnswer = _getPlayersWithAnswer(
                _question.getAnswers()[answerCnt].first);
        if (playersWithAnswer.size() > 0) {
            answerWithPlayersText += " (";
            for (size_t i = 0; i < playersWithAnswer.size(); i++) {
                answerWithPlayersText += playersWithAnswer[i]->getName();
                if (i != playersWithAnswer.size() - 1) {
                    answerWithPlayersText += ", ";
                }
            }
            answerWithPlayersText += ")";
        } else {
            answerWithPlayersText += " -";
        }

        _textAnswers[answerCnt]->setAndDisplayText(answerWithPlayersText);
        _textAnswers[answerCnt]->setColor(RGBA(150, 150, 255, 255));
    }
    _textQuestion->setColor(RGBA(100, 100, 100, 255));
}

void QAQuestion::_startShowSolutionState() {
    for (size_t answerCnt = 0; answerCnt < _question.getAnswers().size(); answerCnt++) {
        std::string answer = _question.getAnswers()[answerCnt].first;
        bool correct = _question.getAnswers()[answerCnt].second;
        if (correct) {
            _textAnswers[answerCnt]->setColor(RGBA(155, 255, 150, 255));
            std::string points;
            points += "    +";
            points += std::to_string(_questionPoints);
            if (_question.getType() == QuestionType::MULTIPLE_CHOICE) {
                points += "pts (if all correct).";
            } else {
                points += "pts.";
            }
            _textAnswers[answerCnt]->appendAndDisplayLine(points);
        } else {
            _textAnswers[answerCnt]->setColor(RGBA(255, 150, 150, 255));
        }
    }
    for (Player* player : _getPlayersWithCorrectAnswers()) {
        player->addPoints(_questionPoints);
    }
    _client->setPoints();
}

void QAQuestion::_startContinueState() {
    _continueConfirm = Confirm::builder()
        .resources(_resources)
        .enabled(true)
        .build();
}

QAQuestion::~QAQuestion() {
    if (_textQuestion != nullptr) {
        delete _textQuestion;
    }
    for (TextBox* answer : _textAnswers) {
        delete answer;
    }
    if (_textTimeLeft != nullptr) {
        delete _textTimeLeft;
    }
}

void QAQuestion::update(Clock &clock) {
    if (!_initialized) {
        init();
    }
    _manageState();

    _timePassed += clock.timeElapsedMillisInt();
    _bgAnimation += 0.02;

    _textQuestion->update(clock);
    for (TextBox* answer : _textAnswers) {
        answer->update(clock);
    }
    _textTimeLeft->update(clock);
    if (_continueConfirm != nullptr) {
        _continueConfirm->update(clock);
        _done = _continueConfirm->isConfirmed();
    }
}

void QAQuestion::render() {
    GRRLIB_DrawImg((int)(-100 + sin(_bgAnimation/2) * 100),
                   (int)(-100 + cos(_bgAnimation/3) * 100),
                   _resources->get(Texture::QUIZ_BG), 0, 1, 1.6,
                   RGBA(255, 255, 255, 255));
    _textQuestion->render();
    for (TextBox* answerBox : _textAnswers) {
        answerBox->render();
    }
    if (_questionState == QAQuestionState::INPUT) {
        _textTimeLeft->render();
    }
    if (_continueConfirm != nullptr) {
        _continueConfirm->render();
    }
}

std::vector<Player*> QAQuestion::_getPlayersWithAnswer(std::string answer) {
    std::vector<Player*> playersWithAnswer;
    for (Answer& playerAnswers : _state->getAnswers()) {
        for (std::string& playerAnswer : playerAnswers.getAnswers()) {
            if (playerAnswer == answer) {
                playersWithAnswer.push_back(playerAnswers.getPlayer());
            }
        }
    }
    return playersWithAnswer;
}

std::vector<Player*> QAQuestion::_getPlayersWithCorrectAnswers() {
    std::vector<Player*> players;
    for (Answer& answer : _state->getAnswers()) {
        if (answer.isApproved()) {
            players.push_back(answer.getPlayer());
            continue;
        }
        std::vector<std::string> answers = answer.getAnswers();
        std::vector<std::string> correctAnswers = _question.getCorrectAnswers();
        std::sort(answers.begin(), answers.end());
        std::sort(correctAnswers.begin(), correctAnswers.end());
        if (answers == correctAnswers) {
            players.push_back(answer.getPlayer());
        }
    }
    return players;
}

bool QAQuestion::_hasPlayerAnswer(Player *player, std::string answer) {
    for (Answer& playerAnswers : _state->getAnswers()) {
        if (playerAnswers.getPlayer()->getName() == player->getName()) {
            for (std::string& playerAnswer : playerAnswers.getAnswers()) {
                if (playerAnswer == answer) {
                    return true;
                }
            }
        }
    }
    return false;
}

void QAQuestion::_cleanup() {
    if (_textQuestion != nullptr) {
        delete _textQuestion;
        _textQuestion = nullptr;
    }
    for (TextBox* answer : _textAnswers) {
        delete answer;
    }
    _textAnswers.clear();
    if (_textTimeLeft != nullptr) {
        delete _textTimeLeft;
        _textTimeLeft = nullptr;
    }
    if (_continueConfirm != nullptr) {
        delete _continueConfirm;
    }
    _timePerState.clear();
    _initialized = false;
    _done = false;
}

bool QAQuestion::isDone() {
    return _done;
}

void QAQuestion::reset() {
    _cleanup();
}

Question QAQuestion::getQuestion() {
    return _question;
}

QAQuestion::Builder QAQuestion::builder() {
    return QAQuestion::Builder();
}

QAQuestion* QAQuestion::Builder::build() {
    return new QAQuestion(_question);
}
