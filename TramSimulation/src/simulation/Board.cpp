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
  if (!doc.LoadFile())
    throw TiXmlException("Error loading file");

  int locations, x, y, i = 0;
  TiXmlElement * root = doc.RootElement();
  root->FirstChildElement("size")->Attribute("x", &x);
  root->FirstChildElement("size")->Attribute("y", &y);
  board = FieldMatrix(x + 1, FieldVector(y + 1, NULL));

  Surface::Init(SDL_CreateRGBSurface(SDL_SWSURFACE, 20 + FACTOR*x, 20 + FACTOR*y, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff));

  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x26, 0x99, 0x26));
  TiXmlElement *stop, *loc, *conn = NULL;

  stop = root->FirstChildElement("TramStops")->FirstChildElement();

  for (stop; stop; stop = stop->NextSiblingElement()) {
    std::string name = stop->Attribute("name");
    stop->Attribute("locations", &locations);
    
    loc = stop->FirstChildElement("location");
    loc->Attribute("x", &x);
    loc->Attribute("y", &y);

    TramStop * ts = new TramStop(x, y, name);

    SDL_FillRect(surf, ts->getRect(), ts->getColor(surf->format));

    this->board[x][y] = ts;
    this->tramStops[name] = ts;
  }

  conn = root->FirstChildElement("Connections")->FirstChildElement("Connect");
  for(conn; conn; conn = conn->NextSiblingElement()) {
    int xa, xb, ya, yb, dx, dy, i, j;
    std::string fromname, toname;
    fromname = conn->Attribute("from");
    toname = conn->Attribute("to");
    xa = this->tramStops[fromname]->getX();
    ya = this->tramStops[fromname]->getY();
    xb = this->tramStops[toname]->getX();
    yb = this->tramStops[toname]->getY();
    dx = abs(xa - xb);
    dy = abs(ya - yb);
    if (dx > dy) {
      if (xa > xb) {
        std::swap(xa, xb);
        std::swap(ya, yb);
      }
      for (i = xa; i <= xb; i++ ) {
        if ( xb != xa ) j = (yb - ya)*(i - xa)/(xb - xa) + ya;
        else j = xa;
        if (this->board[i][j] == NULL)
          this->board[i][j] = new Field(i, j, "Trasasasa");
        SDL_FillRect(surf, this->board[i][j]->getRect(), this->board[i][j] ->getColor(surf->format));
      }
    } else {
      if (ya > yb) {
        std::swap(xa, xb);
        std::swap(ya, yb);
      }
      for (j = ya; j <= yb; j++ ) {
        if (yb != ya) i = (xb - xa)*(j - ya)/(yb - ya) + xa;
        else i = ya;
        if (this->board[i][j] == NULL)
          this->board[i][j] = new Field(i, j, "Trasasasa");
        SDL_FillRect(surf, this->board[i][j]->getRect(), this->board[i][j] ->getColor(surf->format));
      }
    }

  }


 //SDL_SaveBMP(surf, "mapa.bmp");

}

void Board::LMBPressed(Uint16 x, Uint16 y) {
  if (x < 20 || y < 20) return;
  x = (x - 21) / FACTOR;
  y = (y - 21) / FACTOR;

  if (board[x][y] != NULL) {
    std::cout << "Przystanek na pozycji " << x << ", " << y << ": " << board[x][y]->getName() << std::endl;
  }
}
