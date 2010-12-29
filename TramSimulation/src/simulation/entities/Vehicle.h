/* 
 * File:   Vehicle.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:30
 */

#ifndef VEHICLE_H
#define	VEHICLE_H

#include "Entity.h"


class Vehicle : public Entity {
public:
    Vehicle();
    Vehicle(const Vehicle& orig);
    virtual ~Vehicle();
private:

};

#endif	/* VEHICLE_H */

