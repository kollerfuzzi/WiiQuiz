#include "qaslide.hpp"
#include "audioplayer.hpp"
#include "bsod.hpp"

QASlide::QASlide(TextBox::Builder title, TextBox::Builder text, std::string bgImgPath, AVResource bgVideo, std::string bgAudioPath) {
    _title = title;
    _text = text;
    _bgImgPath = bgImgPath;
    _bgVideo = bgVideo;
    _bgAudioPath = bgAudioPath;
}

QASlide::~QASlide()
{
    reset();
}

QASlide::Builder QASlide::builder() {
    return Builder();
}

void QASlide::init() {
    _textBoxTitle = _title
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .build();
    _textBoxContent = _text
        .below(_textBoxTitle)
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .build();

    _confirm = Confirm::builder()
        .resources(_resources)
        .build();
    
    if (_bgVideo != AVResource::none()) {
        _bgVideoPlayer = _resources->getVideo(_bgVideo);
    }
    if (_bgAudioPath != "") {
        AudioPlayer::play(_bgAudioPath, _resources);
    }
}

void QASlide::update(Clock &clock) {
    if (!_initialized) {
        init();
        _initialized = true;
    }
    if (_bgVideoPlayer != nullptr) {
        _bgVideoPlayer->update(clock);
    }
    _textBoxTitle->update(clock);
    _textBoxContent->update(clock);
    _confirm->update(clock);
}

void QASlide::render() {
    if (_bgImgPath != "") {
        GRRLIB_texImg* bgImg = _resources->getTexture(_bgImgPath);
        GRRLIB_DrawImg(0, 0, _resources->getTexture(_bgImgPath), 0, 
            (f32) rmode->fbWidth / (f32) bgImg->w,
            (f32) rmode->xfbHeight / (f32) bgImg->h, 
            0xffffffff);
    }
    if (_bgVideoPlayer != nullptr) {
        _bgVideoPlayer->render();
    }
    _textBoxTitle->render();
    _textBoxContent->render();
}

bool QASlide::isDone() {
    return _initialized && _confirm->isConfirmed();
}

void QASlide::reset() {
    if (_textBoxTitle != nullptr) {
        delete _textBoxTitle;
        _textBoxTitle = nullptr;
    }
    if (_textBoxContent != nullptr) {
        delete _textBoxContent;
        _textBoxContent = nullptr;
    }
    if (_bgVideoPlayer != nullptr) {
        delete _bgVideoPlayer;
        _bgVideoPlayer = nullptr;
    }
    if (_confirm != nullptr) {
        delete _confirm;
        _confirm = nullptr;
    }
    _initialized = false;
}

std::set<std::string> QASlide::getResourcePaths() {
    std::set<std::string> paths;
    if (_bgImgPath != "") {
        paths.insert(_bgImgPath);
    }
    if (_bgAudioPath != "") {
        paths.insert(_bgAudioPath);
    }
    if (_bgVideo.videoPath != "") {
        paths.insert(_bgVideo.videoPath);
    }
    if (_bgVideo.audioPath != "") {
        paths.insert(_bgVideo.audioPath);
    }
    return paths;
}

QASlide::Builder &QASlide::Builder::title(TextBox::Builder title) {
    _title = title;
    return *this;
}

QASlide::Builder &QASlide::Builder::text(TextBox::Builder text) {
    _text = text;
    return *this;
}

QASlide::Builder& QASlide::Builder::bgImgPath(std::string bgImgPath) {
    _bgImgPath = bgImgPath;
    return *this;
}

QASlide::Builder& QASlide::Builder::bgVideo(AVResource bgVideo) {
    _bgVideo = bgVideo;
    return *this;
}

QASlide::Builder& QASlide::Builder::bgAudioPath(std::string bgAudioPath) {
    _bgAudioPath = bgAudioPath;
    return *this;
}

QASlide* QASlide::Builder::build() {
    return new QASlide(_title, _text, _bgImgPath, _bgVideo, _bgAudioPath);
}