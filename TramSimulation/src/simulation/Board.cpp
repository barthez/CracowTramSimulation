/* 
 * File:   Board.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:37
 */

#define FACTOR 4

#include <vector>

#include "Board.h"

Board::Board(std::string filename) : doc(filename.c_str()) {
  std::cout << "Init board\n";
  Init();
}

Board::Board(const Board& orig) {
  std::cout << "Init board (copy)\n";
}

Board::~Board() {
  std::cout << "Kill board\n";
}

void Board::Init() {
  if (!doc.LoadFile())
    throw TiXmlException("Error loading file");

  int x, y;
  TiXmlElement * root = doc.RootElement();
  root->FirstChildElement("size")->Attribute("x", &x);
  root->FirstChildElement("size")->Attribute("y", &y);
  board = FieldMatrix(x + 1, FieldVector(y + 1, NULL ));

  Surface::Init(SDL_CreateRGBSurface(SDL_SWSURFACE, 20 + FACTOR*x, 20 + FACTOR*y, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff));

  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x26, 0x99, 0x26));
  TiXmlElement *stop, *loc;
  
  stop = root->FirstChildElement("Przystanki")->FirstChildElement();
  for (; stop; stop = stop->NextSiblingElement()) {
    loc = stop->FirstChildElement("locations")->FirstChildElement("loc");
    int x, y, i = 0;
    std::auto_ptr<SDL_Rect> sdlrect[200];
    for (loc; loc; loc = loc->NextSiblingElement()) {
      loc->Attribute("x", &x);
      loc->Attribute("y", &y);
      //      xsum += x;
      //      ysum += y;
      //      size += 1;
      //      std::cout << xsum << ", " << ysum << " " << size<< "\n";
      sdlrect[i] = std::auto_ptr<SDL_Rect>(new SDL_Rect);
      sdlrect[i]->x = 20 + FACTOR*x;
      sdlrect[i]->y = 20 + FACTOR*y;
      sdlrect[i]->w = 5;
      sdlrect[i]->h = 5;
      std::string name = stop->Attribute("name");
      SDL_FillRect(surf, sdlrect[i].get(), SDL_MapRGB(surf->format, 0x1b, 0x07, 0x73));
      board[x][y] = new TramStop(name);
      
      i++;

    }
  }

  SDL_SaveBMP(surf, "mapa.bmp");

}

void Board::LMBPressed(Uint16 x, Uint16 y) {
  if (x < 20 || y < 20) return;
  x = (x - 21) / FACTOR;
  y = (y - 21) / FACTOR;
  
  if (board[x][y] != NULL) {
    std::cout << "Przystanek na pozycji " << x << ", " << y << ": "<< board[x][y]->getName() << std::endl;
  }
}
