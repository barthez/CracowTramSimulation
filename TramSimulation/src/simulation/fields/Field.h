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

class Field;

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
};

#endif	/* FIELD_H */

