/* 
 * File:   Font.cpp
 * Author: bartek
 * 
 * Created on 18 styczeń 2011, 18:46
 */

#include "Font.h"

int Font::loadedFonts = 0;
//SDL_Color Font::DEFAULT_COLOR = {0,0,0};
//SDL_Color Font::DEFAULT_BG_COLOR = {255,255,255};

void Font::Init(const char* filename, int size) {
  if (loadedFonts <= 0 && TTF_WasInit() == 0) {
    if (TTF_Init() == -1) throw TTFException(TTF_GetError());
  }

  this->name = new char[strlen(filename) + 1];
  strcpy(this->name, filename);
  this->size = size;

  if ((this->font = TTF_OpenFont(this->name, this->size)) == NULL) {
    throw TTFException(TTF_GetError());
  }

  loadedFonts++;
}

void Font::Clean() {
  if (this->font != NULL) {
    TTF_CloseFont(this->font);
    this->font = NULL;
  }

  if (this->name != NULL) {
    delete [] this->name;
    this->name = NULL;
  }

  if (loadedFonts == 1 && TTF_WasInit() == 1) {
    TTF_Quit();
  }
  
  loadedFonts--;
}

Font::Font(const char *filename, int size) {
  Init(filename, size);
}

Font::Font(const Font & f) {
  Init(f.name, f.size);
}

Font::~Font() {
  Clean();
}

Font & Font::operator =(const Font& f) {
  if (this == &f) return *this;

  Clean();
  Init(f.name, f.size);
}

int Font::setSize(int size) {
  if (this->size == size) return size;
    int old = this->size;

  if (this->font != NULL) {
    TTF_CloseFont(this->font);
    this->font = NULL;
  }

  this->size = size;
  if ((this->font = TTF_OpenFont(this->name, this->size)) == NULL) {
    throw TTFException(TTF_GetError());
  }
  
  return old;
}

int Font::getSize() const {
  return this->size;
}

int Font::setStyle(int style) {
  int old = TTF_GetFontStyle(this->font);
  TTF_SetFontStyle(this->font, style);
  return old;
}

SDL_Surface * Font::renderText(const char * text, int style, SDL_Color * c) {
  SDL_Surface * surf;

  int old = this->setStyle(style);
  SDL_Color color = {0,0,0};
  if (c == NULL) c = &color;

  surf = TTF_RenderUTF8_Blended(this->font, text, *c);
  if (surf == NULL)
    throw SDLException(TTF_GetError());

  this->setStyle(old);

  return surf;
}

SDL_Surface * Font::renderShadedText(const char * text, int style, SDL_Color * c, SDL_Color * s) {
  SDL_Surface * surf;

  int old = this->setStyle(style);

  SDL_Color color = {0,0,0};
  SDL_Color bg = {0,0,0};
  if (c == NULL) c = &color;
  if (s == NULL) s = &bg;

  surf = TTF_RenderUTF8_Shaded(this->font, text, *c, *s);
  if (surf == NULL)
    throw SDLException("Nie mogę utworzyć powieszchni tekstowej");

  this->setStyle(old);

  return surf;
}