#include "qarythmminigame.hpp"
#include "grrlib.h"

QARythmMinigame::QARythmMinigame() {

}

QARythmMinigame::~QARythmMinigame() {
    if (_textBoxHits != nullptr) {
        delete _textBoxHits;
    }
    if (_textBoxMiss != nullptr) {
        delete _textBoxMiss;
    }
}

void QARythmMinigame::update(const Clock& clock) {
    _init();
    std::vector<RythmNote*> greenNotes;
    int hits = 0;
    int misses = 0;
    for (RythmNote& note : _notes) {
        note.usec -= clock.timeElapsedMicros();
        if (note.getRealYPos() > 248 && note.getRealYPos() < 350) {
            greenNotes.push_back(&note);
        }
        if (note.getRealYPos() > 350 && !note.hit) {
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
    misinput -= clock.timeElapsedMillis();
    hitinput -= clock.timeElapsedMillis();
    if (numberOfHits < pressedButtons.size()) {
        misinput = 100;
    } else if (numberOfHits > 0) {
        hitinput = 100;
    }

    std::string hitsStr("Hits: ");
    hitsStr += std::to_string(hits);
    _textBoxHits->setText(hitsStr);
    std::string missStr("Miss: ");
    missStr += std::to_string(misses);
    _textBoxMiss->setText(missStr);

    _textBoxHits->copyBufferToContent();
    _textBoxMiss->copyBufferToContent();
}

void QARythmMinigame::init3dCube() {
    GRRLIB_Settings.antialias = true;

    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
    GRRLIB_Camera3dSettings(0.0f,0.0f,13.0f, 0,1,0, 0,0,0);
}

void QARythmMinigame::draw3dCube() {
    if (shiftx < -3) {
        shiftx = 0.0f;
    }
    shiftx -= 0.05f;
    GRRLIB_3dMode(0.1,1000,45,1,0);
    for (f32 x = -15; x < 30; x += 3) {
        for (f32 y = -15; y < 30; y += 3) {
            GRRLIB_SetTexture(_resources->get(Texture::QUALLE),0);
            GRRLIB_ObjectView(x, y + shiftx, cubeZ - (y + shiftx)*1.5f, a,a*2,a*3,1,1,1);

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
    a+=0.2f;

    // Switch To 2D Mode to display text
    GRRLIB_2dMode();
    const float oldsinx=sinx;
    sinx=oldsinx+0.01f;
}

void QARythmMinigame::render() {
    if (!_initialized) {
        return;
    }

    GRRLIB_SetBackgroundColour(10, 10, 10, 255);

    draw3dCube();

    u32 barColor = RGBA(255, 255, 255, 100);
    if (hitinput > 0) {
        barColor = RGBA(150, 255, 150, 100);
    }
    if (misinput > 0) {
        barColor = RGBA(255, 150, 150, 100);
    }
    GRRLIB_DrawImg(0, 300, _resources->get(Texture::RYTHM_BAR), 0, 1, 1,
                   barColor);

    for (RythmNote& note : _notes) {
        u32 color = RGBA(255, 255, 255, 255);
        if (note.getYPos() > 248 && note.getYPos() < 350) {
            //color = RGBA(100, 255, 100, 255);
        }
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
}

bool QARythmMinigame::isDone() {
    return false;
}

QARythmMinigame::Builder QARythmMinigame::builder() {
    return QARythmMinigame::Builder();
}

void QARythmMinigame::_init() {
    if (_dataLoaded) {
        _initialized = true;
        AudioPlayer::play(Audio::DISCOQUALLEN, _resources);
        return;
    }

    _resources->get(Texture::BTN_A);
    _resources->get(Texture::BTN_DPAD);
    _resources->get(Texture::BTN_ONE);
    _resources->get(Texture::BTN_TWO);
    _resources->get(Texture::RYTHM_BAR);
    _resources->get(Audio::DISCOQUALLEN);

    _rawData = std::string("ONE/2001000;TWO/2473000;ONE/2945000;TWO/3417000;ONE/3889000;TWO/4361000;ONE/4833000;TWO/5305000;A/5305000;ONE/5777000;TWO/6249000;A/6249000;ONE/6721000;TWO/7193000;A/7193000;ONE/7665000;TWO/8137000;A/8137000;ONE/8609000;TWO/9081000;A/9081000;ONE/9553000;A/10025000;TWO/10025000;ONE/10497000;TWO/10969000;A/10969000;ONE/11441000;A/11913000;TWO/11913000;ONE/12385000;TWO/12857000;A/12857000;ONE/13329000;A/13801000;TWO/13801000;ONE/14273000;TWO/14745000;A/14745000;ONE/15217000;TWO/15807000;ONE/16043000;A/16161000;LEFT/16633000;LEFT/17105000;LEFT/17577000;RIGHT/18049000;LEFT/18521000;LEFT/18993000;LEFT/19465000;RIGHT/19937000;LEFT/20409000;LEFT/20881000;LEFT/21353000;RIGHT/21825000;LEFT/22061000;UP/22297000;UP/22769000;UP/23241000;LEFT/23713000");
    for (std::string& note : StringUtils::split(_rawData, ';')) {
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
        _notes.emplace_back(button, std::stoi(noteParts[1]));
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

    AudioPlayer::stop();

    init3dCube();

    _dataLoaded = true;
}

QARythmMinigame* QARythmMinigame::Builder::build() {
    return new QARythmMinigame;
}
