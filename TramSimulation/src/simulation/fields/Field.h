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


#include <string>
#include <map>
#include <SDL/SDL.h>

class Field;

typedef std::map<std::string, Field*> Directions;

class Field {
public:
    Field(int x, int y, std::string name = "Puste pole");
    Field(const Field& orig);
    virtual ~Field();

    int getX() const;
    int getY() const;

    void addDirection(std::string stopname, Field * f);

    virtual const std::string & getName() const;
    virtual Uint32  getColor(const SDL_PixelFormat * format) const;
    SDL_Rect * getRect();
    
private:
  std::string name;
  int x, y;
  SDL_Rect rect;
  int speed;
  Directions dir;
};

#endif	/* FIELD_H */

