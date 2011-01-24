/* 
 * File:   TramStop.cpp
 * Author: bartek
 * 
 * Created on 23 styczeń 2011, 22:55
 */

#include "TramStop.h"

TramStop::TramStop(int x, int y, String name) : Field(x, y, name) {
}

TramStop::TramStop(const TramStop& orig) : Field(orig) {
}

TramStop::~TramStop() {
}

Uint32 TramStop::getColor(const SDL_PixelFormat * format) const {
  return SDL_MapRGB(format, 0x11, 0x11, 0xff);
}