/* 
 * File:   Board.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:37
 */

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
  if ( ! doc.LoadFile() )
    throw TiXmlException("Error loading file");

  int x, y;
  TiXmlElement * root = doc.RootElement();
  root->FirstChildElement("size")->Attribute("x", &x);
  root->FirstChildElement("size")->Attribute("y", &y);
  

  Surface::Init(SDL_CreateRGBSurface(SDL_SWSURFACE, x, y, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff));
  
  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x26,0x99,0x26)) ;

  SDL_Rect rect = {0,0, 5,5};
  TiXmlElement *stop, *loc;


  stop  = root->FirstChildElement("Przystanki")->FirstChildElement();
  for(;stop;stop = stop->NextSiblingElement()) {
    std::cout << "Przystanek: " << stop->Attribute("name") << std::endl;
    loc = stop->FirstChildElement("locations")->FirstChildElement("loc");
    for(loc; loc; loc = loc->NextSiblingElement()) {
      loc->Attribute("x", &x);
      loc->Attribute("y", &y);
      rect.x = x;
      rect.y = y;
      SDL_FillRect(surf, &rect, SDL_MapRGB(surf->format, 0x1b,0x07,0x73)) ;
      
    }
  }

  
  
}
