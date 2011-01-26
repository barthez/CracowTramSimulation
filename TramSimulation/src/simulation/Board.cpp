/* 
 * File:   Board.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:37
 */


#include "Board.h"

Board::Board(String filename) : doc(filename.c_str()) {
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
  board = FieldMatrix(x + 1, FieldVector(y + 1, (Field *) NULL));

  Surface::Init(SDL_CreateRGBSurface(SDL_SWSURFACE, 40 + FACTOR*x, 40 + FACTOR*y, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff));

  SDL_FillRect(surf, NULL, SDL_MapRGB(surf->format, 0x26, 0x99, 0x26));
  TiXmlElement *stop, *loc, *conn = NULL;

  stop = root->FirstChildElement("TramStops")->FirstChildElement();

  for (stop; stop; stop = stop->NextSiblingElement()) {
    String name = String(stop->Attribute("name"));
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
  for (conn; conn; conn = conn->NextSiblingElement()) {
    int xa, xb, ya, yb, dx, dy, i, j;
    String fromname, toname;
    Field * prev = NULL;
    Field * current = NULL;
    fromname = String(conn->Attribute("from"));
    toname = String(conn->Attribute("to"));
    xa = this->tramStops[fromname]->getX();
    ya = this->tramStops[fromname]->getY();
    xb = this->tramStops[toname]->getX();
    yb = this->tramStops[toname]->getY();
    dx = abs(xa - xb);
    dy = abs(ya - yb);

    if (dx > dy) {
      if (xa < xb) {
        for (i = xa; i <= xb; i++) {

          if (xb != xa) j = (yb - ya)*(i - xa) / (xb - xa) + ya;
          else j = ya;
          prev = addField(i, j, toname, prev);
        }
      } else {

        for (i = xa; i >= xb; i--) {

          if (xb != xa) j = (yb - ya)*(i - xa) / (xb - xa) + ya;
          else j = ya;
          prev = addField(i, j, toname, prev);
        }
      }

    } else {
      if (ya < yb) {
        for (j = ya; j <= yb; j++) {

          if (yb != ya) i = (xb - xa)*(j - ya) / (yb - ya) + xa;
          else i = xa;
          prev = addField(i, j, toname, prev);
        }
      } else {
        for (j = ya; j >= yb; j--) {

          if (yb != ya) i = (xb - xa)*(j - ya) / (yb - ya) + xa;
          else i = xa;
          prev = addField(i, j, toname, prev);
        }
      }

    }
    prev = current = NULL;

  }


  //SDL_SaveBMP(surf, "mapa.bmp");

}

bool Board::draw(const Surface& s) {
  //TODO rysuj tramwaje
  return Surface::draw(s);
}

Field * Board::addField(int x, int y, String & to, Field * prev) {
  Field * current = NULL;
  if (this->board[x][y] == NULL) {
    current = new Field(x, y, String("Trasasasa"));
    this->board[x][y] = current;
    SDL_FillRect(surf, current->getRect(), current->getColor(surf->format));
  } else {
    current = this->board[x][y];
  }



  if (prev != NULL)
    prev->addDirection(to, current);

  return current;
}

void Board::update(const DateTime & time) {
//  Uint32 t = SDL_GetTicks();
  int i, j;

  for (i = 0; i < board.size(); ++i) {
    for (j = 0; j < board[i].size(); ++j) {
      if (board[i][j] == NULL) continue;
      board[i][j]->update(time);
    }
  }


  for (i = 0; i < board.size(); ++i) {
    for (j = 0; j < board[i].size(); ++j) {
      if (board[i][j] == NULL) continue;
      board[i][j]->nextState();
    }
  }

//  std::cout << "Update time: " << SDL_GetTicks() - t << "ms\n";
}

void Board::insertTram(Tram * t) {
  tramStops[t->nextStop()]->insertTram(t);
}

void Board::LMBPressed(Uint16 x, Uint16 y) {
  if (x < 20 || y < 20) return;
  x = (x - 21) / FACTOR;
  y = (y - 21) / FACTOR;

  if (board[x][y] != NULL) {
    std::cout << board[x][y]->toString() << std::endl;
  }
}
