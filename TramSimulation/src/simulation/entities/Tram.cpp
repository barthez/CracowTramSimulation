/* 
 * File:   Tram.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:31
 */

#include "Tram.h"

Tram::Tram(int l, int s) : Vehicle() {
  img = Surface::loadIMG("tram.png");
  this->line = l;
  this->squad = s;
  state = STATE_WAIT;
}

Tram::Tram(const Tram& orig) : Vehicle(orig) {
}

Tram::~Tram() {
}

const std::string & Tram::nextStop() const {
  return this->next->second;;
}

void Tram::addSchedule(std::string day, std::map<Time, std::string> schedule) {
  schedules[day] = schedule;
  if (ns == "") {
    ns = schedule.begin()->second;
    next = schedules[day].begin();
  }
}

Surface & Tram::getSurface() {
  return img;
}

void Tram::update(const DateTime& time, std::string name) {

  if (time.dayOfWeek() == "Poniedziałek" ||
          time.dayOfWeek() == "Wtorek" ||
          time.dayOfWeek() == "Środa" ||
          time.dayOfWeek() == "Czwartek" ||
          time.dayOfWeek() == "Piątek"
          ) {
    currentSchedule = &this->schedules["Dzień powszedni"];
  } else {
    currentSchedule = NULL;
  }

  if (currentSchedule == NULL) return;

  if (currentSchedule->begin()->first == (Time) time) {
    state = STATE_RUN;
  }

  if (next->second == name && next->first < (Time) time && state == STATE_RUN) {

    next++;
  }
    

  if (next == currentSchedule->end())  {
    next = currentSchedule->begin();
    state = STATE_WAIT;
  }
  
//  ns = currentSchedule->upper_bound((Time) time)->second;
  //std::cout << line << "-" << squad << "-> " << ns << " t:" << (std::string) time << "\n";
}

int Tram::getLineNumber() const {
  return line;
}

int Tram::getSquadNumber() const {
  return squad;
}

Tram::operator std::string() const {
  std::ostringstream ss(std::ios::out);
  ss.width(2);
  ss.fill('0');
  ss << line << "-";
  ss.width(2);
  ss.fill('0');
  ss << squad;
  ss << " " << x << "," << y << " -> " << ns;
  return ss.str();
}