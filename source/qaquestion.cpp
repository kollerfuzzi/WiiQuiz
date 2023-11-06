#include "qaquestion.hpp"

QAQuestion::QAQuestion(std::string question, std::vector<std::string> answers,
                       std::vector<int> correctAnswers) {
    _question = question;
    _answers = answers;
    _correctAnswers = correctAnswers;
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
    _initialized = true;
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
    if (_timePassed > 5000) {
        _done = true;
    }

    _textQuestion->update(clock);
    _textAnswers->update(clock);
}

void QAQuestion::render() {
    GRRLIB_DrawImg(0, 0, _resources->get(Texture::QUIZ_BG), 0, 1, 1.4,
                   RGBA(255, 255, 255, 255));
    _textQuestion->render();
    _textAnswers->render();
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
