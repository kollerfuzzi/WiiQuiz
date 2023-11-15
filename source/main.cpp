#include <grrlib.h>

#include <memory>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "clock.hpp"
#include "resources.hpp"
#include "resourcemap.hpp"

#include "quiztemplate.hpp"
#include "quiz.hpp"
#include "player.hpp"
#include "quizapiclient.hpp"
#include "screendebug.hpp"
#include "wiimote.hpp"
#include "audioplayer.hpp"

// backlog

// rythm
// stop audio after finish
// for every player set points
// info screen

// network
// socket error handling
// progress bar

// main menu


// ideen: Fragen über die wii, team twiizers
#define FETCH_NETWORK_RESOURCES true

enum QuizLoopState { Q_RUN, Q_TERMINATE };

QuizLoopState quizLoop(Quiz* quiz, Clock& frameClock, Resources* resources);

int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    WiiMote::init();

    Resources* resources = new Resources();
    resources->fetchNetworkResources();

    Quiz* quiz = QuizTemplate::getDefaultQuiz(resources);

    Clock frameClock;

    AudioPlayer::init();

    while(QuizLoopState::Q_RUN == quizLoop(quiz, frameClock, resources));

    AudioPlayer::stop();
    ScreenDebug::destroy();
    delete quiz;
    delete resources;

    GRRLIB_Exit();

    exit(0);
}

QuizLoopState quizLoop(Quiz* quiz, Clock& frameClock, Resources* resources) {
    frameClock.tick();
    WiiMote::update();

    if (WiiMote::buttonPressed(Remote::R1, Button::HOME) || quiz->isDone()) {
        return QuizLoopState::Q_TERMINATE;
    }

    quiz->update(frameClock);
    quiz->render();
    ScreenDebug::render();
    GRRLIB_Render();

    return QuizLoopState::Q_RUN;
}
