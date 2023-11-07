#ifndef QUESTION_HPP
#define QUESTION_HPP

#include "magic_enum.hpp"

#include <string>
#include <vector>

enum QuestionType {
    SINGLE_CHOICE,
    ENTER_STRING
};

class Question {
public:
    Question(std::string prompt, QuestionType type, std::vector<std::string> answers);
    std::string getPrompt();
    QuestionType getType();
    std::vector<std::string> getAnswers();

    class Builder {
    public:
        Builder& prompt(std::string prompt);
        Builder& type(QuestionType type);
        Builder& answers(std::vector<std::string> answers);
        Question build();
    private:
        std::string _prompt;
        QuestionType _type;
        std::vector<std::string> _answers;
    };
    static Builder builder();

private:
    std::string _prompt;
    QuestionType _type;
    std::vector<std::string> _answers;
};

#endif // QUESTION_HPP

/*
    public enum Type {
        SINGLE_CHOICE,
        ENTER_STRING
    }

    private String prompt;
    private Type type;
    private List<String> answers;
*/
