#ifndef QUESTION_HPP
#define QUESTION_HPP

#include "magic_enum.hpp"

#include <string>
#include <vector>
#include "mjpegplayer.hpp"

enum QuestionType {
    SINGLE_CHOICE,
    MULTIPLE_CHOICE,
    FREE_TEXT,
};

class Question {
public:
    Question(std::string id, std::string prompt, QuestionType type, 
             std::vector<std::pair<std::string, bool>> answers,
             std::string bgImgPath, AVResource bgVideo, std::string bgAudioPath);
    Question();
    std::string getId();
    std::string getPrompt();
    QuestionType getType();
    std::vector<std::pair<std::string, bool>> getAnswers();
    std::vector<std::string> getAnswersStr();
    std::string getBgImgPath();
    AVResource getBgVideo();
    std::string getBgAudioPath();

    class Builder {
    public:
        Builder();
        Builder& id(std::string id);
        Builder& prompt(std::string prompt);
        Builder& type(QuestionType type);
        Builder& answer(std::string answer, bool correct);
        Builder& correctAnswer(std::string answer);
        Builder& wrongAnswer(std::string answer);
        Builder& bgImgPath(std::string bgImgPath);
        Builder& bgVideo(AVResource bgVideo);
        Builder& bgAudioPath(std::string bgAudioPath);
        Question build();
    private:
        std::string _id;
        std::string _prompt;
        QuestionType _type;
        std::vector<std::pair<std::string, bool>> _answers;
        std::string _bgImgPath = "";
        AVResource _bgVideo = AVResource::none();
        std::string _bgAudioPath = "";
    };
    static Builder builder();
    std::vector<std::string> getCorrectAnswers();
    bool areAnswersCorrect(std::vector<std::string> answers);
private:
    std::string _id;
    std::string _prompt;
    QuestionType _type;
    std::vector<std::pair<std::string, bool>> _answers;
    std::string _bgImgPath;
    AVResource _bgVideo;
    std::string _bgAudioPath;
};

#endif // QUESTION_HPP
