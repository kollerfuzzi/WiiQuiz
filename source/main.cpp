#include <grrlib.h>
 
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "textbox.hpp"
#include "clock.hpp"
#include "resources.hpp"
#include "resourcemap.hpp"


int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();
    GRRLIB_SetBackgroundColour(0x00, 0xaa, 0x00, 0xFF);
 
    // Initialise the Wiimotes
    WPAD_Init();

    //GRRLIB_Font* font = GRRLIB_LoadTTF(c64font_ttf, c64font_ttf_len);
    //GRRLIB_texImg* img = GRRLIB_LoadTexturePNG(quizbg_png);

    Resources * resources = new Resources();


    TextBox textbox = TextBox::builder()
        .text("Weit hinten, hinter den Wortbergen, fern der Laender Vokalien und Konsonantien leben die Blindtexte. Abgeschieden wohnen Sie in Buchstabhausen an der Kueste des Semantik, eines groszen Sprachozeans. ")
        .font(resources->get(Font::C64FONT))
        .fontSize(15)
        .build();

    GRRLIB_texImg * img = GRRLIB_LoadTexturePNG(TEXTURE_DEFINITIONS[Texture::QUIZ_BG].textureRef);

    Clock frameClock;
    while(true) {
        frameClock.tick();

        WPAD_ScanPads();  // Scan the Wiimotes
 
        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;


        std::string elstring;
        elstring += "DELLLEF:::::: ";
        elstring += std::to_string(frameClock.currentFPS());
        textbox.setText(elstring);
        //timeElapsedTotal += clk.timeElapsedMillis();


        GRRLIB_DrawImg(0, 0, resources->get(Texture::QUIZ_BG), 0, 1, 1.4, RGBA(255, 255, 255, 255));
        //GRRLIB_DrawImg(0, 0, img, 0, 1, 1.4, RGBA(255, 255, 255, 255));
        //GRRLIB_PrintfTTF(20,20, font, "hey duke", 30, RGBA(255, 255, 255, 255));
        textbox.renderText();

        GRRLIB_Render();  // Render the frame buffer to the TV
    }

    delete resources;

    //GRRLIB_FreeTTF(font);
 
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
 
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}
