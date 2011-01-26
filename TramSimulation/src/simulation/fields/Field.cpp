/* 
 * File:   Field.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:38
 */

#include <vector>

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
  ss << "Pole '" << this->name << "'" << x << "," << y << "\n";
  ss << "Prowadzi do:\n";
  for (CDirIT it = directs.begin(); it != directs.end(); ++it) {
    ss << "\t" << it->first << "\n";
  }
  return ss.str();
}

void Field::update(const DateTime & time) {

  std::vector< Tram*>::iterator it;
  for (it = this->trams.begin(); it != this->trams.end(); ++it) {
    if (directs.count((*it)->nextStop()) > 0) {
      directs[(*it)->nextStop()]->insertTramLater((*it), speed / 2);
    } else {
      nextTrams.push_back(*it);
    }
    (*it)->update(time, name);
  }
}

void Field::nextState() {

  trams = nextTrams;
  nextTrams = std::vector< Tram*>();
  if (trams.size() > 0) {
//    std::cout << name << ":\n";
    std::vector<Tram*>::iterator it;
    for (it = trams.begin(); it != trams.end(); ++it) {
//      std::cout << "\t" << (std::string) **it << "\n";
      (*it)->setPosition(x, y);
    }
  }
}

void Field::insertTram(Tram* tram) {
  trams.push_back(tram);
  tram->setPosition(x, y);
  //std::cout << this->name << ": Tram insert\n";
}

void Field::insertTramLater(Tram* tram, int dist) {
  //std::cout << this->name << this->x << "," << this->y << ": Tram insert " << dist << " -> " << tram->nextStop() << "\n";
  if (dist == 0 || tram->nextStop() == this->getName()) {
    nextTrams.push_back(tram);
  } else {
    directs[tram->nextStop()]->insertTramLater(tram, dist - 1);
  }
}