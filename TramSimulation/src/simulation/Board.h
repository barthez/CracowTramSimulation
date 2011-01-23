/* 
 * File:   Board.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:37
 */

#ifndef BOARD_H
#define	BOARD_H

#include "../app/Surface.h"
#include <string>

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <SDL/SDL_gfxPrimitives.h>
#include "../tinyxml/tinyxml.h"
#include "../app/Exceptions.h"
#include "fields/Field.h"
#include "fields/TramStop.h"



typedef std::auto_ptr<Field> pField;
typedef std::vector< Field* > FieldVector;
typedef std::vector< FieldVector > FieldMatrix;
typedef std::map<std::string, TramStop* > StopMap;

class Board : public Surface {
public:
    Board(std::string filename = "");
    Board(const Board& orig);
    virtual ~Board();

    virtual void LMBPressed(Uint16 x, Uint16 y);

protected:
  void Init();
private:
  TiXmlDocument doc;
  FieldMatrix board;
  StopMap tramStops;

};

#endif	/* BOARD_H */

