#include "qaquestion.hpp"

#include <cmath>

QAQuestion::QAQuestion(std::string question, std::vector<std::string> answers,
                       std::vector<int> correctAnswers) {
    _question = question;
    _answers = answers;
    _correctAnswers = correctAnswers;
}

std::vector<Answer> QAQuestion::_getCorrectAnswerPlayers() {
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
    std::string answers;
    for (size_t answerNr = 0; answerNr < _answers.size(); ++answerNr) {
        answers += (char)(answerNr + 'A');
        answers += ") ";
        answers += _answers[answerNr];
        answers += "\n";
    }
    _textAnswers = TextBox::builder()
                       .text(answers)
                       .color(RGBA(230, 230, 230, 255))
                       .font(_resources->get(Font::C64FONT))
                       .fontSize(25)
                       .marginTop(100 + 25 * _textQuestion->lineCount())
                       .animationSpeed(100)
                       .build();

    Question question = toQuestion();
    _client->askQuestion(question);

    _initialized = true;
}

void QAQuestion::_manageState() {
    if (_questionState == QAQuestionState::INPUT && _timePassed > 10000) {
        _timePassed = 0;
        _questionState = QAQuestionState::SHOW_ANSWERS;

        _client->loadAnswers();
        std::vector<Answer> answers = _state->getAnswers();
        _client->endQuestion();
        std::string playerAnswersText;

        for (Answer& answer : answers) {
            playerAnswersText += answer.getPlayer()->getName();
            playerAnswersText += ": ";
            playerAnswersText += answer.getAnswer();
            playerAnswersText += "\n";
        }
        _textAnswers->setText(playerAnswersText);
        _textQuestion->setColor(RGBA(100, 100, 100, 255));
        _textAnswers->setColor(RGBA(150, 150, 255, 255));
        _textAnswers->setAnimationSpeed(50);
    } else if (_questionState == QAQuestionState::SHOW_ANSWERS && _timePassed > 7000) {
        _timePassed = 0;
        _questionState = QAQuestionState::SHOW_SOLUTION;

        std::string correctAnswerStr = _answers[_correctAnswers[0]];
        std::string correctAnswerDisplay("The correct answer is:\n");
        correctAnswerDisplay += correctAnswerStr;
        _textQuestion->setText(correctAnswerDisplay);
        _textQuestion->setColor(RGBA(150, 255, 150, 255));
        std::vector<Answer> correctAnswers = _getCorrectAnswerPlayers();
        std::string playerPointAdd;
        for (Answer& correctAnswer : correctAnswers) {
            playerPointAdd += correctAnswer.getPlayer()->getName();
            playerPointAdd += " +";
            playerPointAdd += std::to_string(_questionPoints);
            playerPointAdd += " pts\n";
            correctAnswer.getPlayer()->addPoints(_questionPoints);
        }
        _textAnswers->setText(playerPointAdd);
        _textAnswers->setAnimationSpeed(25);
        _textQuestion->setAnimationSpeed(25);
        _client->setPoints();
    } else if (_questionState == QAQuestionState::SHOW_SOLUTION && _timePassed > 5000) {
        _done = true;
    }
}

QAQuestion::~QAQuestion() {
    delete _textQuestion;
    delete _textAnswers;
}

void QAQuestion::update(const Clock &clock) {
    if (!_initialized) {
        init();
    }
    _manageState();

    _timePassed += clock.timeElapsedMillisInt();
    _bgAnimation += 0.02;

    _textQuestion->update(clock);
    _textAnswers->update(clock);
}

void QAQuestion::render() {
    GRRLIB_DrawImg((int)(-100 + sin(_bgAnimation/2) * 100),
                   (int)(-100 + cos(_bgAnimation/3) * 100),
                   _resources->get(Texture::QUIZ_BG), 0, 1, 1.6,
                   RGBA(255, 255, 255, 255));
    _textQuestion->render();
    _textAnswers->render();
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
