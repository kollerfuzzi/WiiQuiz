#include "qaquestioncreator.hpp"
#include "bsod.hpp"
#include "magic_enum.hpp"

QAQuestion* QAQuestionCreator::of(Question question) {
    switch (question.getType()) {
        case QuestionType::SINGLE_CHOICE:
        case QuestionType::MULTIPLE_CHOICE:
            return new QAQuestion(question);
        break;

        case QuestionType::FREE_TEXT:
            BSOD::raise("FREE_TEXT not supported yet");
        break;

        default:
            std::string error("Invalid question type: ");
            error += magic_enum::enum_name(question.getType());
            BSOD::raise(error);
        break;
    }
    return nullptr;
}
