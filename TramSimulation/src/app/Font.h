/* 
 * File:   Font.h
 * Author: bartek
 *
 * Created on 18 styczeń 2011, 18:46
 */

#ifndef FONT_H
#define	FONT_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <cstring>
#include "Exceptions.h"

class Font {
public:
  static int loadedFonts;
  
  friend class TextSurface;
  Font(const char *filename, int size = 10);
  Font(const Font & f);
  virtual ~Font();
  Font & operator=(const Font & f);


  int setSize(int size);
  int getSize() const;

  int setStyle(int style);

protected:
  virtual void Init(const char * filename, int size);
  virtual void Clean();

  SDL_Surface * renderText(const char * text, int style = TTF_STYLE_NORMAL, SDL_Color * c = NULL);
  SDL_Surface * renderShadedText(const char * text, int style = TTF_STYLE_NORMAL, SDL_Color * c = NULL, SDL_Color * s = NULL);
private:
  static SDL_Color DEFAULT_COLOR;
  static SDL_Color DEFAULT_BG_COLOR;
  char * name;
  TTF_Font * font;
  int size;
};

#endif	/* FONT_H */

