/* 
 * File:   Car.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:31
 */

#ifndef CAR_H
#define	CAR_H

#include "Vehicle.h"

class Car: public Vehicle {
public:
    Car();
    Car(const Car& orig);
    virtual ~Car();
private:

};

#endif	/* CAR_H */

