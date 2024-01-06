#include "qaquestion.hpp"

#include <cmath>

QAQuestion::QAQuestion(std::string question, std::vector<std::string> answers,
                       std::vector<int> correctAnswers) {
    _question = question;
    _answers = answers;
    _correctAnswers = correctAnswers;
}

std::vector<Answer> QAQuestion::_getCorrectPlayerAnswers() {
    std::string correctAnswer(_answers[_correctAnswers[0]]);
    std::vector<Answer> correctAnswers;
    for (Answer answer : _state->getAnswers()) {
        if (answer.getAnswer() == correctAnswer) {
            correctAnswers.push_back(answer);
        }
    }
    return correctAnswers;
}

void QAQuestion::init() {
    _textQuestion = TextBox::builder()
        .text(_question)
        .font(_resources->get(Font::C64FONT))
        .fontSize(25)
        .marginTop(50)
        .animationSpeed(100)
        .build();

    for (std::string& answerStr : _answers) {
        TextBox* answerBox = TextBox::builder()
            .text(answerStr)
            .color(RGBA(230, 230, 230, 255))
            .font(_resources->get(Font::C64FONT))
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
        .font(_resources->get(Font::C64FONT))
        .fontSize(35)
        .marginTop(400)
        .build();

    Question question = toQuestion();
    _client->askQuestion(question);

    _initialized = true;
}

void QAQuestion::_manageState() {
    if (_timePassed > 5000 && _timePassed < _answerTime) {
        _textTimeLeft->setText(
            std::to_string(((_answerTime - _timePassed) / 1000) + 1));
        _textTimeLeft->copyBufferToContent();
    }

    if (_questionState == QAQuestionState::INPUT && _timePassed > _answerTime) {
        _timePassed = 0;
        _questionState = QAQuestionState::SHOW_ANSWERS;

        _client->loadAnswers();
        std::vector<Answer> playerAnswers = _state->getAnswers();
        _client->endQuestion();

        for (size_t answerCnt = 0; answerCnt < _answers.size(); answerCnt++) {
            std::string answerWithPlayersText = _answers[answerCnt];

            std::vector<std::string> answerPlayerNames;
            for (Answer& answer : playerAnswers) {
                if (answer.getAnswer() == _answers[answerCnt]) {
                    answerPlayerNames.push_back(answer.getPlayer()->getName());
                }
            }
            if (answerPlayerNames.size() > 0) {
                answerWithPlayersText += " (";
                for (size_t i = 0; i < answerPlayerNames.size(); i++) {
                    answerWithPlayersText += answerPlayerNames[i];
                    if (i != answerPlayerNames.size() - 1) {
                        answerWithPlayersText += ", ";
                    }
                }
                answerWithPlayersText += ")";
            } else {
                answerWithPlayersText += " -";
            }

            _textAnswers[answerCnt]->setText(answerWithPlayersText);
            _textAnswers[answerCnt]->copyBufferToContent();
            _textAnswers[answerCnt]->setColor(RGBA(150, 150, 255, 255));
        }
        _textQuestion->setColor(RGBA(100, 100, 100, 255));
    } else if (_questionState == QAQuestionState::SHOW_ANSWERS && _timePassed > 7000) {
        _timePassed = 0;
        _questionState = QAQuestionState::SHOW_SOLUTION;
        for (size_t answerCnt = 0; answerCnt < _answers.size(); answerCnt++) {
            std::string answer = _answers[answerCnt];
            bool correct = _answers[_correctAnswers[0]] == answer;
            if (correct) {
                _textAnswers[answerCnt]->setColor(RGBA(155, 255, 150, 255));
                std::string points;
                points += "    +";
                points += std::to_string(_questionPoints);
                points += "pts.";
                _textAnswers[answerCnt]->appendLineWithoutAnimation(points);
            } else {
                _textAnswers[answerCnt]->setColor(RGBA(255, 150, 150, 255));
            }
        }
        for (Answer& correctAnswer : _getCorrectPlayerAnswers()) {
            correctAnswer.getPlayer()->addPoints(_questionPoints);
        }
        _client->setPoints();
    } else if (_questionState == QAQuestionState::SHOW_SOLUTION
               && _timePassed > 5000) {
        _done = true;
    }

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
}

bool QAQuestion::isDone() {
    return _done;
}

Question QAQuestion::toQuestion() {
    return Question::builder()
        .prompt(_question)
        .answers(_answers)
        .type(QuestionType::SINGLE_CHOICE)
        .build();
}

QAQuestion::Builder QAQuestion::builder() {
    return QAQuestion::Builder();
}

QAQuestion::Builder& QAQuestion::Builder::question(std::string question) {
    this->_question = question;
    return *this;
}

QAQuestion::Builder& QAQuestion::Builder::correctAnswer(std::string answer) {
    this->_answers.push_back(answer);
    this->_correctAnswers.push_back(_answers.size() - 1);
    return *this;
}

QAQuestion::Builder& QAQuestion::Builder::wrongAnswer(std::string answer) {
    this->_answers.push_back(answer);
    return *this;
}

QAQuestion* QAQuestion::Builder::build() {
    return new QAQuestion(_question, _answers, _correctAnswers);
}
