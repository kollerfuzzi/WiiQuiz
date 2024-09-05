
#ifndef QASLIDE_HPP
#define QASLIDE_HPP

#include "quizaction.hpp"
#include "confirm.hpp"

class QASlide : public QuizAction {
public:
    QASlide(TextBox::Builder title, TextBox::Builder text, std::string bgImgPath, AVResource bgVideo, std::string bgAudioPath);
    ~QASlide();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
    std::set<std::string> getResourcePaths();

    class Builder {
    public:
        Builder& title(TextBox::Builder title);
        Builder& text(TextBox::Builder text);
        Builder& bgImgPath(std::string bgImgPath);
        Builder& bgVideo(AVResource bgVideo);
        Builder& bgAudioPath(std::string bgAudioPath);
        QASlide* build();
    private:
        TextBox::Builder _title;
        TextBox::Builder _text;
        std::string _bgImgPath = "";
        AVResource _bgVideo = AVResource::none();
        std::string _bgAudioPath = "";
    };
    static Builder builder();
protected:
    void init();
    TextBox::Builder _title;
    TextBox::Builder _text;
    std::string _bgImgPath;
    std::string _bgAudioPath;
    AVResource _bgVideo;

    TextBox* _textBoxTitle = nullptr;
    TextBox* _textBoxContent = nullptr;
    MJpegPlayer* _bgVideoPlayer = nullptr;
    Confirm* _confirm = nullptr;

    bool _initialized = false;
};

#endif // QASLIDE_HPP
