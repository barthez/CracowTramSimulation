/* 
 * File:   Field.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:38
 */

#ifndef FIELD_H
#define	FIELD_H

#define FACTOR 4
#define SPEED 50


#include <ios>
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <map>
#include <SDL/SDL.h>
#include "../DateTime.h"
#include "../entities/Entity.h"
#include "../entities/Tram.h"


class Field;
class Tram;

using Sim::DateTime;

typedef std::string String;
typedef std::map< String, Field* > Directions;
typedef std::pair< String, Field* > DirPair;
typedef std::map< String, Field* >::iterator DirIT;
typedef std::map< String, Field* >::const_iterator CDirIT;

class Field {
public:
  Field(int x, int y, String name = String("Puste pole"));
  Field(const Field& orig);
  virtual ~Field();

  int getX() const;
  int getY() const;

  void insertTram(Tram * tram);
  void insertTramLater(Tram * tram, int dist);

  virtual void update(const DateTime & time);
  virtual void nextState();

  void addDirection(String & stopname, Field * f);

  virtual String toString() const;
  virtual const String & getName() const;
  virtual Uint32 getColor(const SDL_PixelFormat * format) const;
  SDL_Rect * getRect();

private:
  String name;
  int x, y;
  SDL_Rect rect;
  int speed;
  std::map< String, Field* > directs;
  std::map< String, Tram* > trams, nextTrams;
};

#endif	/* FIELD_H */

