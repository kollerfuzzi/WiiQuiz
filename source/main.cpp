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
#include "menu.hpp"
#include "mjpegplayer.hpp"
#include "quizloaderapiclient.hpp"

int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);

    WiiMote::init();
    Resources* resources = new Resources();
    Quiz* templateQuiz = QuizTemplate::getDefaultQuiz(resources);

    QuizLoaderApiClient quizLoaderApiClient;
    std::vector<Quiz*> quizzes = quizLoaderApiClient.loadQuizzes(resources);

    std::set<std::string> resourcePaths;

    for (std::string path : templateQuiz->getResourcePaths()) {
        resourcePaths.emplace(path);
    }
    for (Quiz* quiz : quizzes) {
        for (std::string path : quiz->getResourcePaths()) {
            resourcePaths.emplace(path);
        }
    }
    resources->fetchStaticAndPathResources(resourcePaths);


    Clock frameClock;

    AudioPlayer::init();

    MenuItem::Builder quizzesMenuItemBuidler = MenuItem::builder()
                   .text("Start")
                   .child(MenuItem::builder()
                          .text(templateQuiz->getName())
                          .renderable(templateQuiz)
                          .build());
    for (Quiz* loadedQuiz : quizzes) {
        quizzesMenuItemBuidler.child(MenuItem::builder()
            .text(loadedQuiz->getName())
            .renderable(loadedQuiz)
            .build());
    }

    MenuItem* root = MenuItem::builder()
        .child(quizzesMenuItemBuidler.build())
        .child(MenuItem::builder()
                   .text("Quit")
                   .quit(true)
                   .build())
        .build();
    Menu* mainMenu = new Menu(resources, root);
    resources->addReserved(resources->pathOf(Texture::CURSOR));
    mainMenu->runUntilDone(frameClock, resources->getTexture(Texture::CURSOR));
    resources->removeReserved(resources->pathOf(Texture::CURSOR));
    AudioPlayer::stop(resources);
    ScreenDebug::destroy();

    delete mainMenu;
    delete templateQuiz;
    for (Quiz* loadedQuiz : quizzes) {
        delete loadedQuiz;
    }
    delete resources;

    GRRLIB_Exit();

    exit(0);
}
