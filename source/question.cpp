#include "question.hpp"
#include "tinyuuidv4.hpp"

Question::Question(std::string id, std::string prompt, QuestionType type, std::vector<std::pair<std::string, bool>> answers) {
    _id = id;
    _prompt = prompt;
    _type = type;
    _answers = answers;
}

Question::Question() {
}

std::string Question::getId() {
    return _id;
}

std::string Question::getPrompt() {
    return _prompt;
}

QuestionType Question::getType() {
    return _type;
}

std::vector<std::pair<std::string, bool>> Question::getAnswers() {
    return _answers;
}

std::vector<std::string> Question::getAnswersStr() {
    std::vector<std::string> answers;
    for (std::pair<std::string, bool>& answer : _answers) {
        answers.push_back(answer.first);
    }
    return answers; 
}

Question::Builder Question::builder() {
    return Question::Builder();
}

std::vector<std::string> Question::getCorrectAnswers() {
    std::vector<std::string> correctAnswers;
    for (std::pair<std::string, bool>& answer : _answers) {
        if (answer.second) {
            correctAnswers.push_back(answer.first);
        }
    }
    return correctAnswers;
}

Question::Builder::Builder() {
    _id = TinyUuidV4::generate();
}

Question::Builder& Question::Builder::id(std::string id) {
    _id = id;
    return *this;
}

Question::Builder& Question::Builder::prompt(std::string prompt) {
    _prompt = prompt;
    return *this;
}

Question::Builder& Question::Builder::type(QuestionType type) {
    _type = type;
    return *this;
}

Question::Builder& Question::Builder::answer(std::string answer, bool correct) {
    _answers.emplace_back(answer, correct);
    return *this;
}

Question::Builder& Question::Builder::correctAnswer(std::string answer) {
    _answers.emplace_back(answer, true);
    return *this;
}

Question::Builder& Question::Builder::wrongAnswer(std::string answer) {
    _answers.emplace_back(answer, false);
    return *this;
}

Question Question::Builder::build() {
    return Question(_id, _prompt, _type, _answers);
}
