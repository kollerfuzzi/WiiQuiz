#include <grrlib.h>

#include <memory>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "clock.hpp"
#include "resources.hpp"
#include "resourcemap.hpp"

#include "asndlib.h"
#include "mp3player.h"

#include "qastart.hpp"
#include "qaquestion.hpp"
#include "qascoreboard.hpp"
#include "quiz.hpp"
#include "player.hpp"
#include "quizapiclient.hpp"
#include "screendebug.hpp"


int main(int argc, char** argv) {
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0x00, 0x00, 0xFF);
    WPAD_Init();

    std::unique_ptr<Resources> resources = std::make_unique<Resources>();
    ScreenDebug::init(resources.get());

    Quiz* quiz = Quiz::builder()
                     .resources(resources.get())
                     .action(QAStart::builder().build())
                     .action(QAQuestion::builder()
                                 .question("Was ist der operative casflow?")
                                 .correctAnswer("OCF")
                                 .wrongAnswer("UCF")
                                 .wrongAnswer("FCF")
                                 .wrongAnswer("BUEB")
                                 .wrongAnswer("BAB")
                                 .build())
                     /*.action(QAQuestion::builder()
                                 .question("Was ist 4x4 (hexadezimal)?")
                                 .correctAnswer("10")
                                 .wrongAnswer("F")
                                 .wrongAnswer("FF")
                                 .wrongAnswer("8")
                                 .wrongAnswer("NullPointerException")
                                 .build())
                     .action(QAQuestion::builder()
                                 .question("What is the Answer?")
                                 .correctAnswer("correct")
                                 .wrongAnswer("wrong")
                                 .build())*/
                     .action(QAScoreboard::builder().build())
                     .build();


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
            MP3Player_PlayBuffer(resources->get(Audio::GETTING_READY).audioRef,
                                 resources->get(Audio::GETTING_READY).audioLen,
                                 NULL);


        quiz->render();
        ScreenDebug::render();

        GRRLIB_Render();
    }


    GRRLIB_Exit();

    ScreenDebug::destroy();
    //delete quiz;

    exit(0);
}
