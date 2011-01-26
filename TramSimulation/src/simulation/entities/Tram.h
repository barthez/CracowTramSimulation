/* 
 * File:   Tram.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:31
 */

#ifndef TRAM_H
#define	TRAM_H

#include "Vehicle.h"
#include "../DateTime.h"
#include <map>

using Sim::Time;

class Tram: public Vehicle {
public:
    Tram(int l, int s);
    Tram(const Tram& orig);
    virtual ~Tram();

    void addSchedule(std::string day, std::map<Time, std::string> schedule);
    const std::string & nextStop() const;
    
private:
  int line, squad;
  std::map<std::string, std::map<Time, std::string> > schedules;
  std::string ns;
  
};

#endif	/* TRAM_H */

