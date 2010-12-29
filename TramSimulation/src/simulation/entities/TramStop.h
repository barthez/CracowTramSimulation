/* 
 * File:   TramStop.h
 * Author: bartek
 *
 * Created on 30 grudzień 2010, 00:09
 */

#ifndef TRAMSTOP_H
#define	TRAMSTOP_H

#include "Entity.h"


class TramStop: public Entity {
public:
    TramStop();
    TramStop(const TramStop& orig);
    virtual ~TramStop();
private:

};

#endif	/* TRAMSTOP_H */

