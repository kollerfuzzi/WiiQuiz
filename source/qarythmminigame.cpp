#include "qarythmminigame.hpp"
#include "grrlib.h"
#include "bsod.hpp"

QARythmMinigame::QARythmMinigame(std::string audioPath, std::string imgPath, std::string data, int delayMs, int maxPts) {
    _audioPath = audioPath;
    _cubeImgPath = imgPath;
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

    _textBoxPlayer->update(clock);

    _confirmStart->update(clock);
    if (_gameState == RythmMinigameState::SHOW_TUTORIAL) {
        _tutorialVisibility = _tutorialVisibility == 0xFF ? 0xFF : _tutorialVisibility + 3;
    } else {
        _tutorialVisibility = _tutorialVisibility == 0 ? 0 : _tutorialVisibility - 3;
    }

    if (_gameState == RythmMinigameState::SHOW_TUTORIAL && _confirmStart->isConfirmed()) {
        _gameState = RythmMinigameState::PLAYING;
        AudioPlayer::play(_audioPath, _resources);
    } else if (_gameState == RythmMinigameState::SHOW_TUTORIAL) {
        return;
    }
    
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
        _gameState = RythmMinigameState::ENDING;
    }

    if (_gameState == RythmMinigameState::ENDING && _endingTimePassed == 0) {
        // (((Hit-Miss)/NotesSize+1)/2)*MAXPTS
        s32 score = ((((f32)hits - (misses + _misinputsTotal)) / (f32)_notes.size())) * _maxPts;
        std::string scoreText("You earned ");
        scoreText += std::to_string(score);
        scoreText += "pts.";
        _textBoxScore->setText(scoreText);
        _player->addPoints(score);
        _client->setPoints();
    }

    if (_gameState == RythmMinigameState::ENDING) {
        _textBoxScore->update(clock);
        _endingTimePassed += clock.timeElapsedMillis();
    }

    if (_gameState == RythmMinigameState::ENDING && _endingTimePassed > 5000) {
        _gameState = RythmMinigameState::DONE;
        AudioPlayer::stop();
    }
}

void QARythmMinigame::init3dCube() {
    GRRLIB_Settings.antialias = true;

    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
    GRRLIB_Camera3dSettings(0.0f, 0.0f, 13.0f, 0, 1, 0, 0, 0, 0);
}

void QARythmMinigame::draw3dCubes() {
    if (_shiftx < -3) {
        _shiftx = 0.0f;
    }
    _shiftx -= 0.05f;
    GRRLIB_3dMode(0.1, 1000, 45, 1, 0);
    for (f32 x = -15; x < 30; x += 3) {
        for (f32 y = -15; y < 30; y += 3) {
            GRRLIB_SetTexture(_resources->getTexture(_cubeImgPath), 0);
            GRRLIB_ObjectView(x, y + _shiftx, _cubeZ - (y + _shiftx) * 1.5f, _a, _a * 2, _a * 3, 1, 1, 1);

            GX_Begin(GX_QUADS, GX_VTXFMT0, 24);
            GX_Position3f32(-1.0f, 1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 0.0f);
            GX_Position3f32(1.0f, 1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 0.0f);
            GX_Position3f32(1.0f, -1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 1.0f);
            GX_Position3f32(-1.0f, -1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 1.0f);

            GX_Position3f32(1.0f, 1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 0.0f);
            GX_Position3f32(-1.0f, 1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 0.0f);
            GX_Position3f32(-1.0f, -1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 1.0f);
            GX_Position3f32(1.0f, -1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 1.0f);

            GX_Position3f32(1.0f, 1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 0.0f);
            GX_Position3f32(1.0f, 1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 0.0f);
            GX_Position3f32(1.0f, -1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 1.0f);
            GX_Position3f32(1.0f, -1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 1.0f);

            GX_Position3f32(-1.0f, 1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 0.0f);
            GX_Position3f32(-1.0f, 1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 0.0f);
            GX_Position3f32(-1.0f, -1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 1.0f);
            GX_Position3f32(-1.0f, -1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 1.0f);

            GX_Position3f32(-1.0f, 1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 0.0f);
            GX_Position3f32(1.0f, 1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 0.0f);
            GX_Position3f32(1.0f, 1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 1.0f);
            GX_Position3f32(-1.0f, 1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 1.0f);

            GX_Position3f32(1.0f, -1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 0.0f);
            GX_Position3f32(-1.0f, -1.0f, -1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 0.0f);
            GX_Position3f32(-1.0f, -1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(1.0f, 1.0f);
            GX_Position3f32(1.0f, -1.0f, 1.0f);
            GX_Color1u32(0xFFFFFFFF);
            GX_TexCoord2f32(0.0f, 1.0f);
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
    if (_gameState == RythmMinigameState::NOT_INITIALIZED) {  
        return;
    }

    GRRLIB_SetBackgroundColour(10, 10, 10, 255);

    draw3dCubes();

    _textBoxPlayer->render();

    if (_tutorialVisibility != 0) {
        GRRLIB_DrawImg(120, 120, _resources->getTexture(Texture::RYTHM_TUTORIAL), 0, 1, 1, 0xFFFFFF00 | _tutorialVisibility);
    }

    if (_gameState == RythmMinigameState::SHOW_TUTORIAL) {
        _confirmStart->render();
        return;
    }

    u32 barColor = RGBA(255, 255, 255, 100);
    if (_hitinput > 0) {
        barColor = RGBA(150, 255, 150, 100);
    }
    if (_misinput > 0) {
        barColor = RGBA(255, 150, 150, 100);
    }
    GRRLIB_DrawImg(0, 350 + _endingTimePassed/4, _resources->getTexture(Texture::RYTHM_BAR), 0, 1, 1,
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
                       _resources->getTexture(note.getTexture()), 0,
                       note.scaleXY, note.scaleXY,
                       color);
    }
    _textBoxHits->render();
    _textBoxMiss->render();
    if (_gameState == RythmMinigameState::ENDING) {
        _textBoxScore->render();
    }
}

bool QARythmMinigame::isDone() {
    return _gameState == RythmMinigameState::DONE;
}

void QARythmMinigame::reset() {
    _cleanup();
}

std::set<std::string> QARythmMinigame::getResourcePaths() {
    return {_audioPath, _cubeImgPath};
}

QARythmMinigame::Builder QARythmMinigame::builder() {
    return QARythmMinigame::Builder();
}

void QARythmMinigame::_init() {
    if (_gameState != RythmMinigameState::NOT_INITIALIZED) {
        return;
    }

    if (_player == nullptr) {
        BSOD::raise("RYTHM_GAME player not set");
    }

    _resources->getTexture(Texture::BTN_A);
    _resources->getTexture(Texture::BTN_DPAD_UP);
    _resources->getTexture(Texture::BTN_DPAD_DOWN);
    _resources->getTexture(Texture::BTN_DPAD_LEFT);
    _resources->getTexture(Texture::BTN_DPAD_RIGHT);
    _resources->getTexture(Texture::BTN_ONE);
    _resources->getTexture(Texture::BTN_TWO);
    _resources->getTexture(Texture::RYTHM_BAR);
    _resources->getTexture(Texture::RYTHM_TUTORIAL);
    _resources->getTexture(_cubeImgPath);
    _resources->getAudio(_audioPath);

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
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(25)
        .marginLeft(50)
        .marginTop(50)
        .build();

    _textBoxMiss = TextBox::builder()
        .color(RGBA(255, 150, 150, 255))
        .text("Miss: -")
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(25)
        .marginLeft(400)
        .marginTop(50)
        .build();

    _textBoxScore = TextBox::builder()
        .color(RGBA(255, 255, 255, 255))
        .text("Name + 100 pts")
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(25)
        .marginLeft(50)
        .marginTop(200)
        .build();

    _confirmStart = Confirm::builder()
        .resources(_resources)
        .build();

    std::string playerStr = "Player: ";
    playerStr += _player->getName();
    _textBoxPlayer = TextBox::builder()
        .color(RGBA(255, 255, 255, 255))
        .text(playerStr)
        .font(_resources->getFont(Font::DEFAULT_FONT))
        .fontSize(25)
        .marginTop(15)
        .marginLeft(50)
        .animationSpeed(100)
        .build();

    AudioPlayer::stop();

    init3dCube();

    _gameState = RythmMinigameState::SHOW_TUTORIAL;
}

void QARythmMinigame::_cleanup() {
    _gameState = RythmMinigameState::NOT_INITIALIZED;
    _player = nullptr;    
    _timePassed = 0;
    _notes.clear();

    if (_textBoxHits != nullptr) {
        delete _textBoxHits;
        _textBoxHits = nullptr;
    }
    if (_textBoxMiss != nullptr) {
        delete _textBoxMiss;
        _textBoxMiss = nullptr;
    }
    if (_textBoxScore != nullptr) {
        delete _textBoxScore;
        _textBoxScore = nullptr;
    }
    if (_confirmStart != nullptr) {
        delete _confirmStart;
        _confirmStart = nullptr;
    }
    if (_textBoxPlayer != nullptr) {
        delete _textBoxPlayer;
        _textBoxPlayer = nullptr;
    }
    // cube
    _a = 0;
    _cubeZ = 0;
    _sinx = 0;
    _misinput = 500;
    _misinputsTotal = 0;
    _hitinput = 0;
    _shiftx = 0;
    
    _delayMs = 0;
    _tutorialVisibility = 0;
    _endingTimePassed = 0;
}

QARythmMinigame::Builder& QARythmMinigame::Builder::img(std::string imgPath) {
    _imgPath = imgPath;
    return *this;
}

QARythmMinigame::Builder& QARythmMinigame::Builder::audio(std::string audioPath) {
    _audioPath = audioPath;
    return *this;
}

QARythmMinigame::Builder &QARythmMinigame::Builder::data(std::string data) {
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
    return new QARythmMinigame(_audioPath, _imgPath, _data, _delayMs, _maxPts);
}
