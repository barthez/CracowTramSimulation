/* 
 * File:   Field.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:38
 */

#include "Field.h"

Field::Field(int x, int y, std::string name) {
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

const std::string & Field::getName() const {
  return this->name;
}

Uint32 Field::getColor(const SDL_PixelFormat * format) const {
  return SDL_MapRGB(format, 0xff, 0xff, 0xff);
}

SDL_Rect * Field::getRect() {
  return &rect;
}

void Field::addDirection(std::string stopname, Field* f) {
  dir[stopname] = f;
}

int Field::getX() const {
  return this->x;
}

int Field::getY() const {
  return this->y;
}