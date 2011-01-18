/* 
 * File:   Events.h
 * Author: Bartłomiej Bułat <bartek.bulat at gmail.com>
 *
 * Created on 18 styczeń 2011, 16:11
 */

#ifndef EVENTS_H
#define	EVENTS_H

#include <SDL/SDL.h>

class Events {
public:
    Events();
    virtual ~Events();
protected:
    virtual void onEvent(SDL_Event * Event);

    virtual void MouseFocus();
    virtual void MouseBlur();

    virtual void InputFocus();
    virtual void InputBlur();

    virtual void Minimaze();
    virtual void Restore();

    virtual void KeyPressed(SDLKey sym, SDLMod mod, Uint16 unicode);
    virtual void KeyReleased(SDLKey sym, SDLMod mod, Uint16 unicode);

    virtual void MouseMove(Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel, bool right, bool middle, bool left);

    virtual void RMBPressed(Uint16 x, Uint16 y);
    virtual void RMBReleased(Uint16 x, Uint16 y);

    virtual void MMBPressed(Uint16 x, Uint16 y);
    virtual void MMBReleased(Uint16 x, Uint16 y);

    virtual void LMBPressed(Uint16 x, Uint16 y);
    virtual void LMBReleased(Uint16 x, Uint16 y);

    virtual void JoyAxis(Uint8 which, Uint8 axis, Sint16 value);
    virtual void JoyBall(Uint8 which, Uint8 ball, Sint16 relx, Sint16 rely);
    virtual void JoyHat(Uint8 which, Uint8 hat, Uint8 value);

    virtual void JoyButtonPressed(Uint8 which, Uint8 button);
    virtual void JoyButtonReleased(Uint8 which, Uint8 button);

    virtual void QuitEv();

    virtual void SystemWM();

    virtual void ResizeEv(int w, int h);
    virtual void ExposeEv();

    virtual void UserEv(int code, void * data1, void * data2);
};

#endif	/* EVENTS_H */

