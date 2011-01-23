/* 
 * File:   Simulation.cpp
 * Author: Bartłomiej Bułat <bartek.bulat at gmail.com>
 * 
 * Created on 21 styczeń 2011, 17:45
 */

#include "Simulation.h"

Simulation::Simulation(std::string schedule, std::string infrastructure) : board(infrastructure), scheduleFile(schedule.c_str()) {
  
}

Simulation::Simulation(const Simulation& orig) {
}

Simulation::~Simulation() {
}

