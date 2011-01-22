/* 
 * File:   Surface.cpp
 * Author: bartek
 * 
 * Created on 18 styczeń 2011, 19:21
 */


#include "Surface.h"

void Surface::Clean() {
  if (surf != NULL) {
    SDL_FreeSurface(surf);
    surf = NULL;
  }
}

void Surface::Init(SDL_Surface * s) {
  this->surf = s;

  this->setOffset(0, 0);
  this->setCrop(0, 0, surf->w, surf->h);
}

Surface::Surface() {
  surf = NULL;
  this->setOffset(0, 0);
  this->setCrop(0, 0, 0, 0);
}

Surface::Surface(const Surface & s) {
  SDL_Surface * copy;
  if ((copy = SDL_ConvertSurface(s.surf, s.surf->format, s.surf->flags)) == NULL)
    throw SDLException("Nie mogę skopiować powieszchni");

  Init(copy);
  setOffset(s.offset.x, s.offset.y);
  setCrop(s.crop.x, s.crop.y, s.crop.w, s.crop.h);
}

Surface & Surface::operator=(const Surface & s) {
  if (this == &s) return *this;

  SDL_Surface * copy;
  if ((copy = SDL_ConvertSurface(s.surf, s.surf->format, s.surf->flags)) == NULL)
    throw SDLException("Nie mogę skopiować powieszchni");

  Clean();
  Init(copy);
  setOffset(s.offset.x, s.offset.y);
  setCrop(s.crop.x, s.crop.y, s.crop.w, s.crop.h);
}

Surface::~Surface() {
  Clean();
}

void Surface::setCrop(int x, int y, int w, int h) {
  this->crop.x = x;
  this->crop.y = y;
  if (w > 0 && h > 0) {
    this->crop.h = h;
    this->crop.w = w;
  }
}

void Surface::setOffset(int x, int y) {
  this->offset.x = x;
  this->offset.y = y;
}

bool Surface::draw(const Surface & s) {
  if (surf == NULL) {
    std::cout << "Empty surface";
    return false;
  }

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
  Surface d;
  d.Init(display);
  return d;
}

Surface Surface::loadBMP(const char * filename, int r, int g, int b) {
  SDL_Surface *loadedImage, *image = NULL;

  loadedImage = SDL_LoadBMP(filename);

  if (loadedImage == NULL)
    throw SDLException("Nie mogę załadować obrazka");


  image = SDL_DisplayFormat(loadedImage);
  SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, r, g, b));
  SDL_FreeSurface(loadedImage);

  Surface s;
  s.Init(image);

  return s;
}

Surface Surface::loadIMG(const char * filename) {
  SDL_Surface *loadedImage, *image = NULL;


  loadedImage = IMG_Load(filename);

  if (loadedImage == NULL)
    throw SDLException("Nie mogę załadować obrazka");

  image = SDL_DisplayFormat(loadedImage);
  SDL_FreeSurface(loadedImage);
  Surface s;
  s.Init(image);

  return s;
}

DisplaySurface::DisplaySurface() : Surface() {
  opened = false;
}

DisplaySurface::~DisplaySurface() {

}

bool DisplaySurface::open(int x, int y, int bpp, Uint32 flags) {
  if (!opened) {
    Init(SDL_SetVideoMode(x, y, bpp, flags));
    opened = true;
    return true;
  }
  return false;
}

bool DisplaySurface::close() {
  if (opened) {
    Clean();
    opened = false;
    return true;
  }
  return false;
}

void TextSurface::Init(const char* t, int style, int r, int g, int b) {
  this->style = style;
  this->color.r = r;
  this->color.g = g;
  this->color.b = b;

  this->text = new char[strlen(t) + 1];
  strcpy(this->text, t);

  Surface::Init(font.renderText(this->text, style, &color));
}

void TextSurface::Clean() {
  Surface::Clean();
  if (this->text != NULL) {
    delete [] this->text;
    this->text = NULL;
  }
}

TextSurface::TextSurface(const char* text, const char* fontfile, int size, int style, int r, int g, int b) : font(fontfile, size) {
  Init(text, style, r, g, b);
}

TextSurface::TextSurface(const TextSurface& s) : font(s.font) {
  Init(s.text, s.style, s.color.r, s.color.g, s.color.b);
}

TextSurface & TextSurface::operator =(const TextSurface& s) {
  if (this == &s) return *this;

  Clean();
  this->font = font;
  Init(s.text, s.style, s.color.r, s.color.g, s.color.b);
  return *this;
}

TextSurface::~TextSurface() {
  Clean();
}

void TextSurface::setText(const char * t) {
  if (t == this->text) {
    Surface::Clean();
    Surface::Init(font.renderText(t, style, &color));
  } else {
    Clean();
    Init(t, this->style, this->color.r, this->color.g, this->color.b);
  }
}

void TextSurface::setSize(int size) {
  if (font.setSize(size) != size) {
    this->setText(this->text);
  }
}

