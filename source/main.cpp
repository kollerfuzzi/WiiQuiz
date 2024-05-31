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
#include "mjpegplayer.hpp"

int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    WiiMote::init();

    Resources* resources = new Resources();
    resources->fetchStaticResources();

    Quiz* quiz = QuizTemplate::getDefaultQuiz(resources);
    resources->fetchResourcesByPaths(quiz->getResourcePaths());
    resources->fetchResourcesByPaths({"videos/tp_trailer.avi", "videos/tp_trailer.mp3"});
    
    Clock frameClock;

    AudioPlayer::init();

    MJpegPlayer* player = resources->getVideo("videos/tp_trailer.avi", "videos/tp_trailer.mp3");

    MenuItem* root = MenuItem::builder()
        .child(MenuItem::builder()
                   .text("Start")
                   .child(MenuItem::builder()
                          .text("Quiz 1")
                          .renderable(quiz)
                          .build())
                   .child(MenuItem::builder()
                          .text("Video")
                          .renderable(player)
                          .build())
                   .build())
        .child(MenuItem::builder()
                   .text("Quit")
                   .quit(true)
                   .build())
        .build();
    Menu* testMenu = new Menu(resources, root);
    testMenu->runUntilDone(frameClock, resources->getTexture(Texture::CURSOR));
    AudioPlayer::stop();
    ScreenDebug::destroy();

    delete player;
    delete testMenu;
    delete quiz;
    delete resources;

    GRRLIB_Exit();

    exit(0);
}
