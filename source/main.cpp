#include <grrlib.h>

#include <memory>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "clock.hpp"
#include "resources.hpp"
#include "resourcemap.hpp"

#include "asndlib.h"
#include "mp3player.h"

#include "qaquestion.hpp"
#include "qascoreboard.hpp"
#include "quiz.hpp"
#include "player.hpp"
#include "wiiapiclient.hpp"
#include "screendebug.hpp"

int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0xaa, 0x00, 0xFF);
    WPAD_Init();

    std::unique_ptr<Resources> resources = std::make_unique<Resources>();
    ScreenDebug::init(resources.get());

    WiiAPIClient* client = new WiiAPIClient();
    client->init();
    ScreenDebug::printLn("HEY_DUKE:");
    client->request(ApiCommand::HEY_DUKE);
    ScreenDebug::printLn("\nGET_PLAYERS:");
    client->request(ApiCommand::GET_PLAYERS);
    ScreenDebug::printLn("\nEND_QUESTION:");
    client->request(ApiCommand::END_QUESTION);



    Quiz* quiz = Quiz::builder()
                     .resources(resources.get())
                     .action(QAQuestion::builder()
                                 .question("What is the Answer?")
                                 .correctAnswer("correct")
                                 .wrongAnswer("wrong")
                                 .build())
                     .action(QAScoreboard::builder().build())
                     .player(Player::builder().name("Andre").build())
                     .player(Player::builder().name("Alexander Paul").build())
                     .player(Player::builder().name("Elias").build())
                     .player(Player::builder().name("Gabsy").build())
                     .player(Player::builder().name("Detlef").build())
                     .build();
    quiz->getPlayers()[0]->addPoints(1134);
    quiz->getPlayers()[1]->addPoints(2543);
    quiz->getPlayers()[2]->addPoints(45);
    quiz->getPlayers()[3]->addPoints(0);
    quiz->getPlayers()[4]->addPoints(20000);


    //MP3 TEST
    ASND_Init();
    MP3Player_Init();

    Clock frameClock;
    while(true) {
        frameClock.tick();


        WPAD_ScanPads();  // Scan the Wiimotes
 
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;

        quiz->update(frameClock);

        if (!MP3Player_IsPlaying())
            MP3Player_PlayBuffer(resources->get(Audio::EVAN_MM).audioRef,
                                 resources->get(Audio::EVAN_MM).audioLen,
                                 NULL);


        quiz->render();
        ScreenDebug::instance()->render();

        GRRLIB_Render();
    }

    ScreenDebug::destroy();
    GRRLIB_Exit();


    exit(0);
}
