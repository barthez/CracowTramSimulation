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
#include <SDL/SDL_gfxPrimitives.h>
#include "../tinyxml/tinyxml.h"
#include "../app/Exceptions.h"

class Board : public Surface {
public:
    Board(std::string filename = "");
    Board(const Board& orig);
    virtual ~Board();

protected:
  void Init();
private:
  TiXmlDocument doc;

};

#endif	/* BOARD_H */

