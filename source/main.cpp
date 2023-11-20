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
#include "bsod.hpp"
#include "dwqcp.hpp"
#include "menu.hpp"

// backlog

// rythm
// stop audio after finish
// for every player set points
// info screen
// use new dpad textures

// main menu
// lightpanel = die lichter kapseln

// ideen: Fragen über die wii, team twiizers

enum QuizLoopState { Q_RUN, Q_TERMINATE };

QuizLoopState quizLoop(Quiz* quiz, Clock& frameClock, Resources* resources);

QuizLoopState menuLoop(Menu* menu, Clock& frameClock, Resources* resources) {
    frameClock.tick();
    WiiMote::update();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    if (WiiMote::buttonPressed(Remote::R1, Button::HOME)) {
        return QuizLoopState::Q_TERMINATE;
    }

    menu->update(frameClock);
    menu->render();

    WiiMote::drawPointer(resources, Remote::R1);

    ScreenDebug::render();
    GRRLIB_Render();

    return QuizLoopState::Q_RUN;
}

int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    WiiMote::init();

    Resources* resources = new Resources();
    resources->fetchNetworkResources();
    /*std::string addr = DWQCP::discover();
    while(true) {
        ScreenDebug::printAndRender(addr);
    }*/

    Quiz* quiz = QuizTemplate::getDefaultQuiz(resources);


    Clock frameClock;

    AudioPlayer::init();

    MenuItem* root = MenuItem::builder()
                        .child(MenuItem::builder()
                                   .text("Start Quiz")
                                   .child(MenuItem::builder()
                                          .text("Quiz 1")
                                          .build())
                                   .child(MenuItem::builder()
                                          .text("The second")
                                          .build())
                                   .child(MenuItem::builder()
                                          .text("Third")
                                          .build())
                                   .build())
                        .child(MenuItem::builder()
                                   .text("Something")
                                   .build())
                        .build();

    Menu* testMenu = new Menu(resources, root);
    while(QuizLoopState::Q_RUN == menuLoop(testMenu, frameClock, resources));
    delete testMenu;

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

    WiiMote::drawPointer(resources, Remote::R1);

    ScreenDebug::render();
    GRRLIB_Render();

    return QuizLoopState::Q_RUN;
}

