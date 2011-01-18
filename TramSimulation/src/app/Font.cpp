/* 
 * File:   Font.cpp
 * Author: bartek
 * 
 * Created on 18 styczeń 2011, 18:46
 */

#include "Font.h"

int Font::loadedFonts = 0;

Font::Font(const char *filename, int size) {
  if (Font::loadedFonts <= 0 && TTF_WasInit() == 0) {
    if (TTF_Init() == -1) throw TTFException(TTF_GetError());
  }
  Font::loadedFonts++;

  this->name = NULL;
  this->name = new char[strlen(filename) + 1];
  strcpy(this->name, filename);
  this->size = size;
  
  if ((this->font = TTF_OpenFont(this->name, this->size)) == NULL) {
    throw TTFException(TTF_GetError());
  }

}

Font::Font(const Font & f) {
if (Font::loadedFonts <= 0 && TTF_WasInit() == 0) {
    if (TTF_Init() == -1) throw TTFException(TTF_GetError());
  }
  Font::loadedFonts++;

  this->name = NULL;
  this->name = new char[strlen(f.name) + 1];
  strcpy(this->name, f.name);
  this->size = f.size;

  if ((this->font = TTF_OpenFont(this->name, this->size)) == NULL) {
    throw TTFException(TTF_GetError());
  }
}

Font::~Font() {
  if (this->font != NULL) {
    TTF_CloseFont(this->font);
    this->font = NULL;
  }
  if (Font::loadedFonts > 1 && TTF_WasInit() == 1) {
    TTF_Quit();
  }
  Font::loadedFonts--;
}

bool Font::setSize(int size) {
  if (this->size == size) return true;
  
  if (this->font != NULL) {
    TTF_CloseFont(this->font);
    this->font = NULL;
  }
  
  this->size = size;
  if ((this->font = TTF_OpenFont(this->name, this->size)) == NULL) {
    throw TTFException(TTF_GetError());
  }
  return true;
}

int Font::getSize() const {
  return this->size;
}

int Font::setStyle(int style) {
  int old = TTF_GetFontStyle(this->font);
  TTF_SetFontStyle(this->font, style);
  return old;
}

TTF_Font * Font::getFontStruct() const {
  return this->font;
}