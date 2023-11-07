#include "question.hpp"

Question::Question(std::string prompt, QuestionType type, std::vector<std::string> answers) {
    _prompt = prompt;
    _type = type;
    _answers = answers;
}

std::string Question::getPrompt() {
    return _prompt;
}

QuestionType Question::getType() {
    return _type;
}

std::vector<std::string> Question::getAnswers() {
    return _answers;
}

Question::Builder Question::builder() {
    return Question::Builder();
}

Question::Builder& Question::Builder::prompt(std::string prompt) {
    _prompt = prompt;
    return *this;
}

Question::Builder& Question::Builder::type(QuestionType type) {
    _type = type;
    return *this;
}

Question::Builder& Question::Builder::answers(std::vector<std::string> answers) {
    _answers = answers;
    return *this;
}

Question Question::Builder::build() {
    return Question(_prompt, _type, _answers);
}
