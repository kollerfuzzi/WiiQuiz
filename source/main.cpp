#include <grrlib.h>
 
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "resources/c64font.hpp"
#include "resources/quizbg.hpp"
#include "textbox.hpp"
 
int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();
 
    // Initialise the Wiimotes
    WPAD_Init();

    GRRLIB_Font* font = GRRLIB_LoadTTF(c64font_ttf, c64font_ttf_len);

    TextBox textbox = TextBox::builder()
        .text("Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef Dellef ")
        .font(font)
        .fontSize(15)
        .build();
 
    // Loop forever
    while(true) {

        //GRRLIB_DrawImg();
 
        WPAD_ScanPads();  // Scan the Wiimotes
 
        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
 
        // ---------------------------------------------------------------------
        // Place your drawing code here
        // ---------------------------------------------------------------------
 
        GRRLIB_Render();  // Render the frame buffer to the TV
    }

    GRRLIB_FreeTTF(font);
 
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB
 
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}
