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

int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    WiiMote::init();

    Resources* resources = new Resources();
    resources->fetchNetworkResources();

    Quiz* quiz = QuizTemplate::getDefaultQuiz(resources);


    Clock frameClock;

    AudioPlayer::init();

    MenuItem* root = MenuItem::builder()
        .child(MenuItem::builder()
                   .text("Start Quiz")
                   .child(MenuItem::builder()
                          .text("Quiz 1")
                          .renderable(quiz)
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
    testMenu->runUntilDone(frameClock, resources);
    AudioPlayer::stop();
    ScreenDebug::destroy();


    delete testMenu;
    delete quiz;
    delete resources;

    GRRLIB_Exit();

    exit(0);
}
