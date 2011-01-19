/* 
 * File:   View.cpp
 * Author: bartek
 * 
 * Created on 19 styczeń 2011, 16:55
 */

#include <iostream>

#include "View.h"
#include "Exceptions.h"

View::View(Surface * display, Surface * background) {
  this->display = display;
  this->background = background;
  if (this->background != NULL)
    this->background->setCrop(0,0,this->display->getWidth(), this->display->getHeight());

}

View::View(const View & v) {
  this->background = v.background;
}

View::~View() {
  
}

void View::scrollAtScreenBorder(int size, int step) {
  if (background == NULL) throw SDLException("Nie ustawiono żadnej warstwy tła");
  int x, y;
  SDL_GetMouseState(&x, &y);
  int l, t, r, b;
  l = background->offset.x + size;
  r = background->offset.x + background->crop.w - size;
  t = background->offset.y + size;
  b = background->offset.y + background->crop.h - size;
  if ( x < l ) this->moveCrop(-step, 0);
  if ( x > r ) this->moveCrop(step, 0);
  if ( y < t ) this->moveCrop(0, -step);
  if ( y > b ) this->moveCrop(0, step);
//  std::cout << "(" << x << ", " << y << ") L: " << l << " R: " << r << " T: " << t << " B: " << b << std::endl;
}

bool View::draw() {
  background->draw(*this->display);

  for(SPLIt It = elements.begin(); It != elements.end(); ++It) {
    (*It)->draw(*this->display);
  }
}

bool View::addSurface(Surface * s, int x, int y) {
  return false;
}
bool View::removeSurface(Surface * s) {
  return false;
}

void View::moveCrop(int x, int y) {
  if (background == NULL) throw SDLException("Nie ustawiono żadnej warstwy tła");
  background->crop.x += x;
  background->crop.y += y;
  int maxx, maxy;
  maxx = background->getWidth() - background->crop.w;
  maxy = background->getHeight() - background->crop.h;
  if (background->crop.x < 0) background->crop.x = 0;
  if (background->crop.y < 0) background->crop.y = 0;
  if (background->crop.x > maxx ) background->crop.x = maxx;
  if (background->crop.y > maxy) background->crop.y = maxy;
//  std::cout << "Crop (" << background->crop.x << ", " << background->crop.y << ") W: " << background->crop.w << " H: " << background->crop.h << std::endl;
//  std::cout << "Max (" << maxx << ", " << maxy << ")" << std::endl;
}