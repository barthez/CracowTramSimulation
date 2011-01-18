/* 
 * File:   Surface.cpp
 * Author: bartek
 * 
 * Created on 18 styczeń 2011, 19:21
 */


#include "Surface.h"

Surface::Surface() {
  surf = NULL;
}

Surface::Surface(SDL_Surface * s, int xoffset, int yoffset) {
  if ((this->surf = SDL_ConvertSurface(s, s->format, s->flags)) == NULL)
    throw SDLException("Nie mogę skopiować powieszchni");

  this->offset.x = xoffset;
  this->offset.y = yoffset;
  this->offset.w = 0;
  this->offset.h = 0;

  this->crop.x = 0;
  this->crop.y = 0;
  this->crop.w = this->surf->w;
  this->crop.h = this->surf->h;
}

Surface::Surface(const Surface & s) {
  if ((this->surf = SDL_ConvertSurface(s.surf, s.surf->format, s.surf->flags)) == NULL)
    throw SDLException("Nie mogę skopiować powieszchni");

  this->offset.x = s.offset.x;
  this->offset.y = s.offset.y;
  this->offset.w = s.offset.w;
  this->offset.h = s.offset.h;

  this->crop.x = s.crop.x;
  this->crop.y = s.crop.y;
  this->crop.w = s.crop.w;
  this->crop.h = s.crop.h;
}


Surface & Surface::operator=(const Surface & s) {
  if (surf != NULL) {
    SDL_FreeSurface(surf);
    surf = NULL;
  }

  if ((this->surf = SDL_ConvertSurface(s.surf, s.surf->format, s.surf->flags)) == NULL)
    throw SDLException("Nie mogę skopiować powieszchni");

  this->offset.x = s.offset.x;
  this->offset.y = s.offset.y;
  this->offset.w = s.offset.w;
  this->offset.h = s.offset.h;

  this->crop.x = s.crop.x;
  this->crop.y = s.crop.y;
  this->crop.w = s.crop.w;
  this->crop.h = s.crop.h;
}

Surface::~Surface() {
  if (surf != NULL) {
    SDL_FreeSurface(surf);
    surf = NULL;
  }
}

void Surface::setCrop(int x, int y, int w, int h) {
  this->crop.x = x;
  this->crop.y = y;
  this->crop.h = w;
  this->crop.w = h;
}

void Surface::setOffset(int x, int y) {
  this->offset.x = x;
  this->offset.y = y;
}

bool Surface::draw(const Surface & s) {
  if (surf == NULL) return false;
  
  if (SDL_BlitSurface(this->surf, &this->crop, s.surf, &this->offset) < 0)
    throw SDLException("Nie można wyrysować powieszchni");
  return true;
}

bool Surface::flip() {
  return surf != NULL && SDL_Flip(this->surf) == 0;
}

int Surface::getWidth() const {
  if (surf == NULL) throw SDLException("Powieszchnia nie istnieje");
  return this->surf->w;
}

int Surface::getHeight() const {
  if (surf == NULL) throw SDLException("Powieszchnia nie istnieje");
  return this->surf->h;
}

SDL_Rect Surface::getOffset() const {
  if (surf == NULL) throw SDLException("Powieszchnia nie istnieje");
  return this->offset;
}

SDL_Rect Surface::getCrop() const {
  if (surf == NULL) throw SDLException("Powieszchnia nie istnieje");
  return this->crop;
}

Surface Surface::createDisplay(int x, int y, int bpp, Uint32 flags) {
  SDL_Surface * display = SDL_SetVideoMode(x, y, bpp, flags);
  if (display == NULL) {
    throw SDLException("Nie można utworzyć warstwy wyświetlacza");
  }
  Surface d = Surface(display);
  SDL_FreeSurface(display);
  return d;
}

Surface Surface::loadBMP(const char * filename, int r, int g, int b) {
  SDL_Surface *loadedImage, *image = NULL;

  loadedImage = SDL_LoadBMP(filename);

  if (loadedImage == NULL)
    throw SDLException("Nie mogę załadować obrazka");


  image = SDL_DisplayFormat(loadedImage);
  SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, r, g, b));
  Surface s(image);

  SDL_FreeSurface(loadedImage);
  SDL_FreeSurface(image);

  return s;
}

Surface Surface::loadIMG(const char * filename) {
  SDL_Surface *loadedImage, *image = NULL;


  loadedImage = IMG_Load(filename);

  if (loadedImage == NULL)
    throw SDLException("Nie mogę załadować obrazka");


  image = SDL_DisplayFormat(loadedImage);
  Surface s(image);

  SDL_FreeSurface(loadedImage);
  SDL_FreeSurface(image);

  return s;
}

Surface Surface::createText(Font & font, const char * text, int style, const int r, const int g, const int b) {
  SDL_Surface * surf, *surfformat;


  font.setStyle(style);
  SDL_Color color = {r, g, b};

  surf = TTF_RenderUTF8_Blended(font.getFontStruct(), text, color);
  if (surf == NULL)
    throw SDLException("Nie mogę utworzyć powieszchni tekstowej");
  surfformat = SDL_DisplayFormat(surf);
  if (surf == NULL)
    throw SDLException("Nie mogę sformatować powieszchni do formatu wyświetlacza");

  Surface s(surf);

  SDL_FreeSurface(surf);
  SDL_FreeSurface(surfformat);

  return s;
}

Surface Surface::createShadowedText(Font & font, const char * text, int style, const int r, const int g, const int b, const int sr, const int sg, const int sb) {
  SDL_Surface * surf, *surfformat;


  font.setStyle(style);
  SDL_Color color = {r, g, b};
  SDL_Color shadow = {sr, sg, sb};

  surf = TTF_RenderUTF8_Shaded(font.getFontStruct(), text, color, shadow);
  if (surf == NULL)
    throw SDLException("Nie mogę utworzyć powieszchni tekstowej");
  surfformat = SDL_DisplayFormat(surf);
  if (surf == NULL)
    throw SDLException("Nie mogę sformatować powieszchni do formatu wyświetlacza");

  Surface s(surf);

  SDL_FreeSurface(surf);
  SDL_FreeSurface(surfformat);

  return s;
}

DisplaySurface::DisplaySurface(): Surface() {
  opened = false;
}

DisplaySurface::~DisplaySurface() {

}

bool DisplaySurface::open(int x, int y, int bpp, Uint32 flags) {
  if (! opened) {
    this->surf = SDL_SetVideoMode(x, y, bpp, flags);;
    opened = true;
    return true;
  }
  return false;
}

bool DisplaySurface::close() {
  if (opened) {
    if (this->surf != NULL) {
      SDL_FreeSurface(this->surf);
      this->surf = NULL;
    }
    opened = false;
    return true;
  }
  return false;
}