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
#include "entities/Vehicle.h"
#include <vector>

typedef std::vector<Vehicle*> VehiclesVector;

class Simulation {
public:
  Simulation(std::string schedule, std::string infrastructure);
  Simulation(const Simulation& orig);
  virtual ~Simulation();

  void update();
private:
  Board board;
  TiXmlDocument scheduleFile;
  VehiclesVector vehicles;
  Sim::DateTime simTime;
  
  

  


};

#endif	/* SIMULATION_H */

