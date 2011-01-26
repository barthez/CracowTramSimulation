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
#include <string>
#include <sstream>

using Sim::Time;

class Tram: public Vehicle {
public:
    Tram(int l, int s);
    Tram(const Tram& orig);
    virtual ~Tram();

    void addSchedule(std::string day, std::map<Time, std::string> schedule);
    const std::string & nextStop() const;
    void update(const DateTime & time, std::string name);

    Surface & getSurface();

    int getLineNumber() const;
    int getSquadNumber() const;

    operator std::string() const;
    
private:
  enum { STATE_RUN, STATE_WAIT };
  int state;
  int line, squad;
  std::map<std::string, std::map<Time, std::string> > schedules;
  std::map<Time, std::string> * currentSchedule;
  std::string ns;
  std::map<Time, std::string>::iterator next;
  
};

#endif	/* TRAM_H */

