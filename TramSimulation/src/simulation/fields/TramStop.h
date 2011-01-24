/* 
 * File:   TramStop.h
 * Author: bartek
 *
 * Created on 23 styczeń 2011, 22:55
 */

#ifndef TRAMSTOP_H
#define	TRAMSTOP_H

#include "Field.h"

class TramStop : public Field {
public:
  TramStop(int x, int y, String name = "");
  TramStop(const TramStop& orig);
  virtual ~TramStop();

  virtual Uint32 getColor(const SDL_PixelFormat * format) const;
private:
  int i;

};

#endif	/* TRAMSTOP_H */

