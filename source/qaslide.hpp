
#ifndef QASLIDE_HPP
#define QASLIDE_HPP

#include "quizaction.hpp"
#include "confirm.hpp"

class QASlide : public QuizAction {
public:
    QASlide(std::string title, int titleFontSize, std::string text, int textFontSize, std::string bgImgPath, AVResource bgVideo, std::string bgAudioPath);
    ~QASlide();
    void update(Clock& clock);
    void render();
    bool isDone();
    void reset();
    std::set<std::string> getResourcePaths();

    class Builder {
    public:
        Builder& title(std::string title);
        Builder& titleFontSize(int titleFontSize);
        Builder& text(std::string text);
        Builder& textFontSize(int textFontSize);
        Builder& bgImgPath(std::string bgImgPath);
        Builder& bgVideo(AVResource bgVideo);
        Builder& bgAudioPath(std::string bgAudioPath);
        QASlide* build();
    private:
        std::string _title = "";
        int _titleFontSize = 30;
        std::string _text = "";
        int _textFontSize = 20;
        std::string _bgImgPath = "";
        AVResource _bgVideo = AVResource::none();
        std::string _bgAudioPath = "";
    };
    static Builder builder();
protected:
    void init();
    std::string _title;
    int _titleFontSize;
    std::string _text;
    int _textFontSize;
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
