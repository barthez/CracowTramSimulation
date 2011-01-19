/* 
 * File:   Application.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:30
 */

#include "Application.h"

Application::Application(int x, int y, int bpp, const char * title) {
  this->Init(x, y, bpp, title);
}

Application::~Application() {
  Clean();
}

bool Application::Init(int x, int y, int bpp, const char * title) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    throw SDLException("Nie można zainicjalizować SDL");
  }

  display.open(x,y,bpp, SDL_HWSURFACE | SDL_DOUBLEBUF );

  SDL_WM_SetCaption(title, NULL);

  SDL_EnableUNICODE(0);


  try {
    image = Surface::loadIMG("./vw_ogorek.jpg");
    text = new TextSurface("Bartek!", "czcionka.ttf", 20, TTF_STYLE_NORMAL, 255,255,255);
  } catch (SDLException & ex) {
    cout << ex.what() << std::endl;
    
  }

  view = View(&this->display, &this->image);


//  SDL_EnableKeyRepeat(10, SDL_DEFAULT_REPEAT_INTERVAL / 3);
  TIME = SDL_GetTicks();
  TIME2 = SDL_GetTicks();
  return true;
}

void Application::onEvent(SDL_Event * Event) {
  Events::onEvent(Event);
}

void Application::Loop() {
  //Do some modifications
  view.scrollAtScreenBorder(20, 5);

  if ((TIME2+ 1000) <SDL_GetTicks()) {
    text->setText("Super!");
  }

}

void Application::Render() {
  //Render surfaces
  view.draw();
  text->draw(display);

  display.flip();
}

int Application::Execute() {
  while (running) {

    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
      onEvent(&Event);
    }

    Loop();
    
    Uint32 NTIME = SDL_GetTicks();
    if ((Uint32) (TIME + 40) < NTIME ) {
      Render();
      TIME = SDL_GetTicks();
    } else SDL_Delay(10);

  }

  return 0;
}

void Application::QuitEv() {
  running = AS_QUIT;
}

void Application::LMBPressed(Uint16 x, Uint16 y) {

}

void Application::KeyPressed(SDLKey sym, SDLMod mod, Uint16 unicode) {
  
}

void Application::KeyReleased(SDLKey sym, SDLMod mod, Uint16 unicode) {

}

void Application::MouseMove(Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel, bool right, bool middle, bool left) {

}

void Application::Clean() {
  delete text;
  display.close();
  SDL_Quit();
}


