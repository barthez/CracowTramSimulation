/* 
 * File:   Field.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:38
 */

#include "Field.h"

Field::Field(int x, int y, String name) {
  this->name = name;
  this->x = x;
  this->y = y;
  rect.x = 20 + FACTOR*x;
  rect.y = 20 + FACTOR*y;
  rect.w = FACTOR;
  rect.h = FACTOR;
  speed = SPEED;
}

Field::Field(const Field& orig) {
}

Field::~Field() {
}

const String & Field::getName() const {
  return this->name;
}

Uint32 Field::getColor(const SDL_PixelFormat * format) const {
  return SDL_MapRGB(format, 0xff, 0xff, 0xff);
}

SDL_Rect * Field::getRect() {
  return &rect;
}

void Field::addDirection(String & stopname, Field* f) {

  this->directs[stopname] = f;
}

int Field::getX() const {
  return this->x;
}

int Field::getY() const {
  return this->y;
}

String Field::toString() const {
  std::stringstream ss(std::ios::out);
  ss << "Pole '" << this->name << "'\n";
  ss << "Prowadzi do:\n";
  for (CDirIT it = directs.begin(); it != directs.end(); ++it) {
    ss << "\t" << it->first << "\n";
  }
  return ss.str();
}

void Field::update(const DateTime & time) {
  std::map< String, Field* >::iterator it;
  for(it = this->directs.begin(); it != this->directs.end(); ++ it) {
    if (trams.count(it->first) > 0) {
      it->second->insertTramLater(trams[it->first], speed/10);
    }
  }
}

void Field::nextState() {
  trams = nextTrams;
}

void Field::insertTram(Tram* tram) {
  trams[tram->nextStop()] = tram;
  tram->setPosition(x, y);
}

void Field::insertTramLater(Tram* tram, int dist) {
  
}