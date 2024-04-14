#ifndef QUESTION_HPP
#define QUESTION_HPP

#include "magic_enum.hpp"

#include <string>
#include <vector>

enum QuestionType {
    SINGLE_CHOICE,
    MULTIPLE_CHOICE,
    ENTER_STRING
};

class Question {
public:
    Question(std::string prompt, QuestionType type, std::vector<std::pair<std::string, bool>> answers);
    Question();
    std::string getPrompt();
    QuestionType getType();
    std::vector<std::pair<std::string, bool>> getAnswers();
    std::vector<std::string> getAnswersStr();

    class Builder {
    public:
        Builder& prompt(std::string prompt);
        Builder& type(QuestionType type);
        Builder& answer(std::string answer, bool correct);
        Builder& correctAnswer(std::string answer);
        Builder& wrongAnswer(std::string answer);
        Question build();
    private:
        std::string _prompt;
        QuestionType _type;
        std::vector<std::pair<std::string, bool>> _answers;
    };
    static Builder builder();
    std::vector<std::string> getCorrectAnswers();
private:
    std::string _prompt;
    QuestionType _type;
    std::vector<std::pair<std::string, bool>> _answers;
};

#endif // QUESTION_HPP
