/* 
 * File:   Application.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:30
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <iostream>

#include "Events.h"
#include "Exceptions.h"
#include "Surface.h"
#include "View.h"

using std::cout;
using std::cin;

class Application : public Events {
public:
    Application(int x, int y, int bpp, const char* title);
    virtual ~Application();
    int Execute();

    void QuitEv();

    void LMBPressed(Uint16 x, Uint16 y);
    void KeyPressed(SDLKey sym, SDLMod mod, Uint16 unicode);
    void KeyReleased(SDLKey sym, SDLMod mod, Uint16 unicode);

    void MouseMove(Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel, bool right, bool middle, bool left);
private:
    enum { AS_QUIT = 0, AS_MENU, AS_SIMULATION };
    int running;
    DisplaySurface display;
    Surface image;
    TextSurface * text;
    View view;
    Font * font;
    Uint32 TIME, TIME2;

protected:
    void onEvent(SDL_Event * Event);
    void Loop();
    void Render();

    bool Init(int x, int y, int bpp, const char * title);
    void Clean();

};

#endif	/* APPLICATION_H */

