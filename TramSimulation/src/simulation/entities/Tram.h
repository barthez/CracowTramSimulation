/* 
 * File:   Tram.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:31
 */

#ifndef TRAM_H
#define	TRAM_H

class Tram: public Vehicle {
public:
    Tram();
    Tram(const Tram& orig);
    virtual ~Tram();
private:

};

#endif	/* TRAM_H */

