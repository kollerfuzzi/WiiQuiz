#include <grrlib.h>

#include <memory>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "clock.hpp"
#include "resources.hpp"
#include "resourcemap.hpp"

#include "asndlib.h"
#include "mp3player.h"

#include "quiztemplate.hpp"
#include "quiz.hpp"
#include "player.hpp"
#include "quizapiclient.hpp"
#include "screendebug.hpp"
#include "wiimote.hpp"

enum QuizLoopState { Q_RUN, Q_TERMINATE };

QuizLoopState quizLoop(Quiz* quiz, Clock& frameClock, Resources* resources);

int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    WiiMote::init();

    std::unique_ptr<Resources> resources = std::make_unique<Resources>();
    ScreenDebug::init(resources.get());

    Quiz* quiz = QuizTemplate::getDefaultQuiz(resources.get());

    Clock frameClock;

    //MP3 TEST
    ASND_Init();
    MP3Player_Init();

    while(QuizLoopState::Q_RUN == quizLoop(quiz, frameClock, resources.get()));


    GRRLIB_Exit();

    ScreenDebug::destroy();
    //delete quiz; // TODO crashes

    exit(0);
}

QuizLoopState quizLoop(Quiz* quiz, Clock& frameClock, Resources* resources) {
    frameClock.tick();
    WiiMote::update();

    if (WiiMote::buttonPressed(Remote::R1, Button::HOME)) {
        return QuizLoopState::Q_TERMINATE;
    }

    quiz->update(frameClock);

    if (!MP3Player_IsPlaying()) {
        MP3Player_PlayBuffer(resources->get(Audio::DISCOQUALLEN).audioRef,
                             resources->get(Audio::DISCOQUALLEN).audioLen,
                             NULL);
    }


    quiz->render();
    ScreenDebug::render();

    GRRLIB_Render();

    return QuizLoopState::Q_RUN;
}
