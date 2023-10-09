#include <grrlib.h>

#include <memory>
#include <stdlib.h>
#include <wiiuse/wpad.h>

#include "textbox.hpp"
#include "clock.hpp"
#include "resources.hpp"
#include "resourcemap.hpp"

#include "asndlib.h"
#include "mp3player.h"

#include "qaquestion.hpp"
#include "qascoreboard.hpp"
#include "quiz.hpp"
#include "player.hpp"

int main(int argc, char** argv)
{
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0xaa, 0x00, 0xFF);
    WPAD_Init();

    std::unique_ptr<Resources> resources = std::make_unique<Resources>();

    Quiz* quiz = Quiz::builder()
                     .resources(resources.get())
                     .action(QAQuestion::builder()
                                 .question("choose correct plz")
                                 .correctAnswer("correct")
                                 .wrongAnswer("wrong")
                                 .build())
                     .action(QAScoreboard::builder().build())
                     .player(Player::builder().name("André").build())
                     .player(Player::builder().name("Alexander Paul").build())
                     .build();
/*
    TextBox textbox
        = TextBox::builder()
              .text("GRRLIB_texImg* img = GRRLIB_LoadTexturePNG(quizbg_png);GRRLIB_texImg* img = "
                    "GRRLIB_LoadTexturePNG(quizbg_png);")
              .font(resources->get(Font::C64FONT))
              .fontSize(25)
              .marginTop(50)
              .animationSpeed(100)
              .build();
*/
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

        /*
        GRRLIB_DrawImg(0, 0, resources->get(Texture::QUIZ_BG), 0, 1, 1.4, RGBA(255, 255, 255, 255));
        textbox.update(frameClock);
        textbox.render();
        */
        quiz->render();

        GRRLIB_Render();
    }

    GRRLIB_Exit();

    exit(0);
}
