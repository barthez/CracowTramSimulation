/* 
 * File:   Tram.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:31
 */

#include "Tram.h"

Tram::Tram(int l, int s) :Vehicle() {
  img = Surface::loadIMG("tram.png");
  this->line =l;
  this->squad = s;
}

Tram::Tram(const Tram& orig) : Vehicle(orig) {
}

Tram::~Tram() {
}

const std::string & Tram::nextStop() const {
  return this->ns;
}

void Tram::addSchedule(std::string day, std::map<Time, std::string> schedule) {
  schedules[day] = schedule;
}