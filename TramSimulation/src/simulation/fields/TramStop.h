/* 
 * File:   TramStop.h
 * Author: bartek
 *
 * Created on 23 styczeń 2011, 22:55
 */

#ifndef TRAMSTOP_H
#define	TRAMSTOP_H

#include "Field.h"
#include <string>

class TramStop : public Field {
public:
  TramStop(std::string name = "");
  TramStop(const TramStop& orig);
  virtual ~TramStop();
private:
  int i;

};

#endif	/* TRAMSTOP_H */

