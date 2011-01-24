/* 
 * File:   Board.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:37
 */

#ifndef BOARD_H
#define	BOARD_H


#include "fields/Field.h"
#include "../app/Surface.h"
#include <string>

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <memory>
#include <SDL/SDL_gfxPrimitives.h>
#include "../tinyxml/tinyxml.h"
#include "../app/Exceptions.h"
#include "fields/TramStop.h"



typedef std::auto_ptr<Field> pField;
typedef std::vector< Field* > FieldVector;
typedef std::vector< FieldVector > FieldMatrix;
typedef std::map<String, TramStop* > StopMap;

class Board : public Surface {
public:
    Board(String filename = String() );
    Board(const Board& orig);
    virtual ~Board();

    virtual void LMBPressed(Uint16 x, Uint16 y);

protected:
  void Init();
private:
  TiXmlDocument doc;
  FieldMatrix board;
  StopMap tramStops;

  Field * addField(int x, int y, String & to, Field * prev);

};

#endif	/* BOARD_H */

