/* 
 * File:   Simulation.h
 * Author: Bartłomiej Bułat <bartek.bulat at gmail.com>
 *
 * Created on 21 styczeń 2011, 17:45
 */

#ifndef SIMULATION_H
#define	SIMULATION_H

#include "DateTime.h"
#include "Board.h"
#include "../app/Surface.h"
#include "entities/Vehicle.h"
#include <vector>
#include <map>

using Sim::DateTime;

typedef std::vector<Vehicle*> VehiclesVector;

class Simulation {
public:
  Simulation(std::vector < std::string > schedules, std::string infrastructure);
  Simulation(const Simulation& orig);
  virtual ~Simulation();

  Simulation * operator= (const Simulation & s);

  void update();
  Board * getBoard();
  Surface * getTimeSurface();
private:
  Board board;
  VehiclesVector vehicles;
  DateTime simTime;
  TextSurface timeSurf;
  
  

  


};

#endif	/* SIMULATION_H */

