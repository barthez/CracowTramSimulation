/* 
 * File:   Surface.h
 * Author: bartek
 *
 * Created on 18 styczeń 2011, 19:21
 */

#ifndef SURFACE_H
#define	SURFACE_H


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "Exceptions.h"
#include "Font.h"

class Surface {
public:
  Surface();
  Surface(SDL_Surface * s, int xoffset = 0, int yoffset = 0);
  Surface(const Surface & s);
  Surface & operator=(const Surface & s);

  virtual ~Surface();

  void setCrop(int x, int y, int w, int h);
  void setOffset(int x, int y);
  bool draw(const Surface & s);
  bool flip();

  int getWidth() const;
  int getHeight() const;
  SDL_Rect getOffset() const;
  SDL_Rect getCrop() const;

  static Surface createDisplay(int x, int y, int bpp, Uint32 flags);
  static Surface loadBMP(const char * filename, int r = 255, int g = 0, int b = 255);
  static Surface loadIMG(const char * filename);
  static Surface createText(Font & font, const char * text, int style = TTF_STYLE_NORMAL, const int r = 0, const int g = 0, const int b = 0);
  static Surface createShadowedText(Font & font, const char * text, int style = TTF_STYLE_NORMAL, const int r = 0, const int g = 0, const int b = 0, const int sr = 255, const int sg = 255, const int sb = 255);
protected:
  SDL_Surface * surf;
  SDL_Rect offset;
  SDL_Rect crop;

};

class DisplaySurface: public Surface {
public:
  DisplaySurface();
  virtual ~DisplaySurface();

  bool open(int x, int y, int bpp, Uint32 flags);
  bool close();
private:
  bool opened;

};

#endif	/* SURFACE_H */

