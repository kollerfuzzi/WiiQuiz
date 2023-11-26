#include "qarythmminigame.hpp"
#include "grrlib.h"

QARythmMinigame::QARythmMinigame(Audio audio, Texture img, std::string data, int delayMs, int maxPts) {
    _audio = audio;
    _cubeImg = img;
    _rawData = data;
    _delayMs = delayMs;
    _maxPts = maxPts;
}

QARythmMinigame::~QARythmMinigame() {
    if (_textBoxHits != nullptr) {
        delete _textBoxHits;
    }
    if (_textBoxMiss != nullptr) {
        delete _textBoxMiss;
    }
    if (_textBoxScore != nullptr) {
        delete _textBoxScore;
    }
}

void QARythmMinigame::update(Clock& clock) {
    _init();
    std::vector<RythmNote*> greenNotes;
    size_t hits = 0;
    size_t misses = 0;
    for (RythmNote& note : _notes) {
        note.usec -= clock.timeElapsedMicros();
        if (note.getRealYPos() > 300 && note.getRealYPos() < 400) {
            greenNotes.push_back(&note);
        }
        if (note.getRealYPos() > 400 && !note.hit) {
            note.miss = true;
        }
        if (note.hit) {
            hits++;
        }
        if (note.miss) {
            misses++;
        }
    }
    std::vector<Button> pressedButtons = WiiMote::buttonsPressed(Remote::R1);
    size_t numberOfHits = 0;
    for (RythmNote* greenNote : greenNotes) {
        if(std::find(pressedButtons.begin(), pressedButtons.end(), greenNote->btn) != pressedButtons.end()) {
            greenNote->hit = true;
            ++numberOfHits;
        }
    }
    _misinput -= clock.timeElapsedMillis();
    _hitinput -= clock.timeElapsedMillis();
    if (numberOfHits < pressedButtons.size() && _misinput < 0) {
        _misinput = 100;
        _misinputsTotal++;

    } else if (numberOfHits > 0) {
        _hitinput = 100;
    }

    std::string hitsStr("Hits: ");
    hitsStr += std::to_string(hits);
    _textBoxHits->setText(hitsStr);
    std::string missStr("Miss: ");
    missStr += std::to_string(misses + _misinputsTotal);
    _textBoxMiss->setText(missStr);

    _textBoxHits->copyBufferToContent();
    _textBoxMiss->copyBufferToContent();

    if (hits + misses >= _notes.size()) {
        _ending = true;
    }

    if (_ending && _endingTimePassed == 0) {
        // (((Hit-Miss)/NotesSize+1)/2)*MAXPTS
        s32 score = ((((f32)hits - (misses + _misinputsTotal)) / (f32)_notes.size())) * _maxPts;
        std::string scoreText("You earned ");
        scoreText += std::to_string(score);
        scoreText += "pts.";
        _textBoxScore->setText(scoreText);
    }

    if (_ending) {
        _textBoxScore->update(clock);
        _endingTimePassed += clock.timeElapsedMillis();
    }
}

void QARythmMinigame::init3dCube() {
    GRRLIB_Settings.antialias = true;

    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
    GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
}

void QARythmMinigame::draw3dCube() {
    if (_shiftx < -3) {
        _shiftx = 0.0f;
    }
    _shiftx -= 0.05f;
    GRRLIB_3dMode(0.1,1000,45,1,0);
    for (f32 x = -15; x < 30; x += 3) {
        for (f32 y = -15; y < 30; y += 3) {
            GRRLIB_SetTexture(_resources->get(_cubeImg),0);
            GRRLIB_ObjectView(x, y + _shiftx, _cubeZ - (y + _shiftx)*1.5f, _a,_a*2,_a*3,1,1,1);

            GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
            GX_Position3f32(-1.0f,1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(1.0f,1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(1.0f,-1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(-1.0f,-1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(1.0f,1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(-1.0f,1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(-1.0f,-1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(1.0f,-1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(1.0f,1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(1.0f,1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(1.0f,-1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(1.0f,-1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(-1.0f,1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(-1.0f,1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(-1.0f,-1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(-1.0f,-1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(-1.0f,1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(1.0f,1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(1.0f,1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(-1.0f,1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);

            GX_Position3f32(1.0f,-1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,0.0f);
            GX_Position3f32(-1.0f,-1.0f,-1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,0.0f);
            GX_Position3f32(-1.0f,-1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f,1.0f);
            GX_Position3f32(1.0f,-1.0f,1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f,1.0f);
            GX_End();
        }
    }
    _a+=0.2f;

    // Switch To 2D Mode to display text
    GRRLIB_2dMode();
    const float oldsinx=_sinx;
    _sinx=oldsinx+0.01f;
}

void QARythmMinigame::render() {
    if (!_initialized) {
        return;
    }

    GRRLIB_SetBackgroundColour(10, 10, 10, 255);

    draw3dCube();

    u32 barColor = RGBA(255, 255, 255, 100);
    if (_hitinput > 0) {
        barColor = RGBA(150, 255, 150, 100);
    }
    if (_misinput > 0) {
        barColor = RGBA(255, 150, 150, 100);
    }
    GRRLIB_DrawImg(0, 350 + _endingTimePassed/4, _resources->get(Texture::RYTHM_BAR), 0, 1, 1,
                   barColor);

    for (RythmNote& note : _notes) {
        u32 color = RGBA(255, 255, 255, 255);
        if (note.hit) {
            color = RGBA(100, 255, 100, (u8)(1.0f-255.0f*(note.scaleXY - 1.0f)));
            note.scaleXY+=0.1f;
            if (note.scaleXY >= 2.0f) {
                note.scaleXY = 2.0f;
            }
        }
        if (note.miss) {
            color = RGBA(255, 150, 150, 150);
        }
        GRRLIB_DrawImg(note.getXPos() - note.scaleXY*52/2, note.getYPos() -note.scaleXY*52/2,
                       _resources->get(note.getTexture()), note.getRotation(),
                       note.scaleXY, note.scaleXY,
                       color);
    }
    _textBoxHits->render();
    _textBoxMiss->render();
    if (_ending) {
        _textBoxScore->render();
    }
}

bool QARythmMinigame::isDone() {
    return _endingTimePassed > 5000;
}

QARythmMinigame::Builder QARythmMinigame::builder() {
    return QARythmMinigame::Builder();
}

void QARythmMinigame::_init() {
    if (_dataLoaded) {
        _initialized = true;
        AudioPlayer::play(_audio, _resources);
        return;
    }

    _resources->get(Texture::BTN_A);
    _resources->get(Texture::BTN_DPAD);
    _resources->get(Texture::BTN_ONE);
    _resources->get(Texture::BTN_TWO);
    _resources->get(Texture::RYTHM_BAR);
    _resources->get(_cubeImg);
    _resources->get(_audio);

    std::string content = StringUtils::split(_rawData, '#')[1];
    for (std::string& note : StringUtils::split(content, ';')) {
        std::vector<std::string> noteParts = StringUtils::split(note, '/');
        std::string buttonStr(noteParts[0]);
        Button button = Button::LEFT;
        if ("DOWN" == buttonStr) {
            button = Button::LEFT;
        } else if ("RIGHT" == buttonStr) {
            button = Button::DOWN;
        } else if ("LEFT" == buttonStr) {
            button = Button::UP;
        } else if ("UP" == buttonStr) {
            button = Button::RIGHT;
        } else if ("ONE" == buttonStr) {
            button = Button::ONE;
        } else if ("TWO" == buttonStr) {
            button = Button::TWO;
        } else if ("A" == buttonStr) {
            button = Button::A;
        } else if ("B" == buttonStr) {
            button = Button::B;
        }
        s64 usec = std::stoi(noteParts[1]);
        usec += _delayMs * 1000;
        _notes.emplace_back(button, usec);
    }

    _textBoxHits = TextBox::builder()
        .color(RGBA(150, 255, 150, 255))
        .text("Hits: -")
        .font(_resources->get(Font::C64FONT))
        .fontSize(25)
        .marginLeft(50)
        .marginTop(50)
        .build();

    _textBoxMiss = TextBox::builder()
        .color(RGBA(255, 150, 150, 255))
        .text("Miss: -")
        .font(_resources->get(Font::C64FONT))
        .fontSize(25)
        .marginLeft(400)
        .marginTop(50)
        .build();

    _textBoxScore = TextBox::builder()
        .color(RGBA(255, 255, 255, 255))
        .text("Name + 100 pts")
        .font(_resources->get(Font::C64FONT))
        .fontSize(25)
        .marginLeft(50)
        .marginTop(200)
        .build();


    AudioPlayer::stop();

    init3dCube();

    _dataLoaded = true;
}

QARythmMinigame::Builder& QARythmMinigame::Builder::img(Texture img) {
    _img = img;
    return *this;
}

QARythmMinigame::Builder &QARythmMinigame::Builder::audio(Audio audio) {
    _audio = audio;
    return *this;
}

QARythmMinigame::Builder& QARythmMinigame::Builder::data(std::string data) {
    _data = data;
    return *this;
}

QARythmMinigame::Builder& QARythmMinigame::Builder::delayMs(int ms) {
    _delayMs = ms;
    return *this;
}

QARythmMinigame::Builder& QARythmMinigame::Builder::maxPts(int maxPts) {
    _maxPts = maxPts;
    return *this;
}

QARythmMinigame* QARythmMinigame::Builder::build() {
    return new QARythmMinigame(_audio, _img, _data, _delayMs, _maxPts);
}
