/* 
 * File:   Entity.h
 * Author: bartek
 *
 * Created on 30 grudzień 2010, 00:08
 */

#ifndef ENTITY_H
#define	ENTITY_H

#define FACTOR 4

#include "../../app/Surface.h"
#include "../DateTime.h"


using Sim::DateTime;
using Sim::Time;


class Entity {
public:
  Entity();
  Entity(const Entity& orig);
  virtual ~Entity();

  void setPosition(int x, int y);
protected:
  int x, y;
  Surface img;
};

#endif	/* ENTITY_H */

