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

#include <iostream>

class Surface {
public:
  friend class View;
  Surface();
  Surface(const Surface & s);
  Surface & operator=(const Surface & s);

  virtual ~Surface();

  void setCrop(int x, int y, int w = 0, int h = 0);
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
  virtual void Init(SDL_Surface * s);
  virtual void Clean();
  SDL_Surface * surf;
  SDL_Rect offset;
  SDL_Rect crop;

};

class DisplaySurface : public Surface {
public:
  DisplaySurface();
  virtual ~DisplaySurface();

  bool open(int x, int y, int bpp, Uint32 flags);
  bool close();
private:
  bool opened;

};

class TextSurface : public Surface {
public:
  TextSurface(const char * text, const char * fontfile, int size, int style = TTF_STYLE_NORMAL, int r=0, int g =0, int b =0);
  TextSurface(const TextSurface & s);
  TextSurface & operator=(const TextSurface & s);
  virtual ~TextSurface();
  
  void setText(const char * text);
  void setSize(int size);
protected:
  virtual void Init(const char* text, int style, int r, int g, int b);
  virtual void Clean();
private:
  Font font;
  char * text;
  int style;
  SDL_Color color;

};

#endif	/* SURFACE_H */

