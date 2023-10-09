#include "qaquestion.hpp"

QAQuestion::QAQuestion(std::string question, std::map<std::string, bool> answers) {
    _question = question;
    _answers = answers;
}

void QAQuestion::init() {
    _textQuestion = TextBox::builder()
                        .color(RGBA(255, 255, 255, 255))
                        .text(_question)
                        .animationSpeed(50)
                        .build();
}

QAQuestion::~QAQuestion() {
    delete _textQuestion;
    delete _textAnswers;
}

void QAQuestion::update(const Clock &clock) {
    if (!_initialized) {
        init();
    }

    _timePassed += clock.timeElapsedMillisInt();
    if (_timePassed > 10000) {
        _done = true;
    }
    _textQuestion->update(clock);
}

void QAQuestion::render() {
    _textQuestion->render();
}

bool QAQuestion::isDone() {
    return _done;
}

QAQuestion::Builder QAQuestion::builder() {
    return QAQuestion::Builder();
}

QAQuestion::Builder& QAQuestion::Builder::question(std::string question) {
    this->_question = question;
    return *this;
}

QAQuestion::Builder& QAQuestion::Builder::correctAnswer(std::string answer) {
    this->_answers[answer] = true;
    return *this;
}

QAQuestion::Builder& QAQuestion::Builder::wrongAnswer(std::string answer) {
    this->_answers[answer] = false;
    return *this;
}

QAQuestion* QAQuestion::Builder::build() {
    return new QAQuestion(_question, _answers);
}
