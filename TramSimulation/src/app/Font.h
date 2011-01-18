/* 
 * File:   Font.h
 * Author: bartek
 *
 * Created on 18 styczeń 2011, 18:46
 */

#ifndef FONT_H
#define	FONT_H

#include <SDL/SDL_ttf.h>
#include "Exceptions.h"

class Font {
public:
  Font(const char *filename, int size = 10);
  Font(const Font & f);
  ~Font();

  bool setSize(int size);
  int getSize() const;

  int setStyle(int style);

  TTF_Font * getFontStruct() const;

private:
  static int loadedFonts;
  char * name;
  TTF_Font * font;
  int size;
};

#endif	/* FONT_H */

