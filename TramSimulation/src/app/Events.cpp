/* 
 * File:   Events.cpp
 * Author: Bartłomiej Bułat <bartek.bulat at gmail.com>
 * 
 * Created on 18 styczeń 2011, 16:11
 */

#include "Events.h"

Events::Events() {
}

Events::~Events() {
}

void Events::onEvent(SDL_Event * Event) {
    switch (Event->type) {
        case SDL_ACTIVEEVENT:
        {
            switch (Event->active.state) {
                case SDL_APPMOUSEFOCUS:
                {
                    if (Event->active.gain) MouseFocus();
                    else MouseBlur();
                    break;
                }
                case SDL_APPINPUTFOCUS:
                {
                    if (Event->active.gain) InputFocus();
                    else InputBlur();
                    break;
                }
                case SDL_APPACTIVE:
                {
                    if (Event->active.gain) Restore();
                    else Minimaze();
                    break;
                }
                default: break;

            }
        }
        case SDL_KEYDOWN:
        {
            KeyPressed(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
            break;
        }
        case SDL_KEYUP:
        {
            KeyReleased(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            MouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, Event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT), Event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE), Event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT));
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT:
                {
                    LMBPressed(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    MMBPressed(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    RMBPressed(Event->button.x, Event->button.y);
                    break;
                }
                default: break;
            }
        }
        case SDL_MOUSEBUTTONUP:
        {
            switch (Event->button.button) {
                case SDL_BUTTON_LEFT:
                {
                    LMBReleased(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE:
                {
                    MMBReleased(Event->button.x, Event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    RMBReleased(Event->button.x, Event->button.y);
                    break;
                }
                default: break;
            }
        }
        case SDL_JOYAXISMOTION:
        {
            break;
        }
        case SDL_JOYBALLMOTION:
        {
            break;
        }
        case SDL_JOYHATMOTION:
        {
            break;
        }
        case SDL_JOYBUTTONDOWN:
        {
            break;
        }
        case SDL_JOYBUTTONUP:
        {
            break;
        }
        case SDL_QUIT:
        {
            QuitEv();
            break;
        }
        case SDL_SYSWMEVENT:
        {
            SystemWM();
            break;
        }
        case SDL_VIDEORESIZE:
        {
            ResizeEv(Event->resize.w, Event->resize.h);
            break;
        }
        case SDL_VIDEOEXPOSE:
        {
            ExposeEv();
            break;
        }
        default:
        {
            UserEv(Event->user.code, Event->user.data1, Event->user.data2);
            break;
        }
    }
}

void Events::MouseFocus() {
}

void Events::MouseBlur() {
}

void Events::InputFocus() {
}

void Events::InputBlur() {
}

void Events::Minimaze() {
}

void Events::Restore() {
}

void Events::KeyPressed(SDLKey sym, SDLMod mod, Uint16 unicode) {
}

void Events::KeyReleased(SDLKey sym, SDLMod mod, Uint16 unicode) {
}

void Events::MouseMove(Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel, bool right, bool middle, bool left) {
}

void Events::RMBPressed(Uint16 x, Uint16 y) {
}

void Events::RMBReleased(Uint16 x, Uint16 y) {
}

void Events::MMBPressed(Uint16 x, Uint16 y) {
}

void Events::MMBReleased(Uint16 x, Uint16 y) {
}

void Events::LMBPressed(Uint16 x, Uint16 y) {
}

void Events::LMBReleased(Uint16 x, Uint16 y) {
}

void Events::JoyAxis(Uint8 which, Uint8 axis, Sint16 value) {
}

void Events::JoyBall(Uint8 which, Uint8 ball, Sint16 relx, Sint16 rely) {
}

void Events::JoyHat(Uint8 which, Uint8 hat, Uint8 value) {
}

void Events::JoyButtonPressed(Uint8 which, Uint8 button) {
}

void Events::JoyButtonReleased(Uint8 which, Uint8 button) {
}

void Events::QuitEv() {
}

void Events::SystemWM() {
}

void Events::ResizeEv(int w, int h) {
}

void Events::ExposeEv() {
}

void Events::UserEv(int code, void * data1, void * data2) {
}

