#ifndef LOADINGBAR_HPP
#define LOADINGBAR_HPP

#include <grrlib.h>
#include "sys/time.h"

class LoadingBar {
public:
    static void setTicks(int ticks);
    static void tick(GRRLIB_ttfFont* font);
private:
    static timeval _lastRender;
    static int _ticks;
    static int _currentTick;
};

#endif // LOADINGBAR_HPP