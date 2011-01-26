/* 
 * File:   Entity.cpp
 * Author: bartek
 * 
 * Created on 30 grudzień 2010, 00:08
 */

#include "Entity.h"

Entity::Entity() {
}

Entity::Entity(const Entity& orig) {
}

Entity::~Entity() {
}

void Entity::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}