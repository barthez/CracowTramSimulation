/* 
 * File:   Application.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:30
 */

#include <ios>
#include <iostream>
#include <string>
#include <sstream>

#include "Application.h"

std::string linie[] = { "linia12.xml", "50.xml" };


Application::Application(int x, int y, int bpp, const char * title) : sim(std::vector<std::string>(linie, linie+2), "przystanki.xml") {
  this->Init(x, y, bpp, title);
}

Application::~Application() {
  Clean();
}

bool Application::Init(int x, int y, int bpp, const char * title) {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    throw SDLException("Nie można zainicjalizować SDL");
  }

  display.open(x, y, bpp, SDL_HWSURFACE | SDL_DOUBLEBUF);

  SDL_WM_SetCaption(title, NULL);

  SDL_EnableUNICODE(0);


  try {
    image = Surface::loadIMG("./vw_ogorek.jpg");
  } catch (SDLException & ex) {
    cout << ex.what() << std::endl;

  }

  view = View(&this->display, this->sim.getBoard());


  //  SDL_EnableKeyRepeat(10, SDL_DEFAULT_REPEAT_INTERVAL / 3);
  TIME = SDL_GetTicks();
  TIME_FPS = SDL_GetTicks();
  FRAME_COUNT = 0;
  fps = new TextSurface("FPS: 0", "czcionka.ttf", 20, TTF_STYLE_ITALIC, 240, 10, 10);


  showExecTime = showFPS = startSim = false;
  return true;
}

void Application::onEvent(SDL_Event * Event) {
  Events::onEvent(Event);
}

void Application::Loop() {
  //Do some modifications
  if (running == AS_SIMULATION) {
    if (startSim) sim.update();
    view.scrollAtScreenBorder(20, 5);
  }


  if ((TIME_FPS + 1000) < SDL_GetTicks()) {
    TIME_FPS = SDL_GetTicks();
    std::ostringstream ss(std::ios::out);
    ss << "FPS: " << FRAME_COUNT;
    FRAME_COUNT = 0;
    fps->setText(ss.str().c_str());
  }


}

void Application::Render() {
  //Render surfaces
  FRAME_COUNT++;

  view.draw();


  if (showFPS) fps->draw(display);
  this->sim.getTimeSurface()->draw(display);
  display.flip();
}

int Application::Execute() {
  Uint32 execTime = SDL_GetTicks();
  running = AS_SIMULATION;
  while (running) {
    //    execTime = SDL_GetTicks() - execTime;
    //    std::cout << "Render time " << execTime << "ms\n";
    //    execTime = SDL_GetTicks();
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
      onEvent(&Event);
    }

    Loop();

    execTime = SDL_GetTicks() - execTime;
    if (showExecTime)
      std::cout << "Exec time " << execTime << "ms\n";
    SDL_Delay(40 - (execTime > 40 ? 0 : execTime));
    execTime = SDL_GetTicks();
    Render();
  }

  return 0;
}

void Application::QuitEv() {
  running = AS_QUIT;
}

void Application::LMBPressed(Uint16 x, Uint16 y) {
  view.LMBPressed(x, y);
}

void Application::KeyPressed(SDLKey sym, SDLMod mod, Uint16 unicode) {
  switch (sym) {
    case SDLK_F1:
      showFPS = !showFPS;
      break;
    case SDLK_F2:
      showExecTime = !showExecTime;
      break;
    case SDLK_F3:
      startSim = !startSim;
      break;
  }
}

void Application::KeyReleased(SDLKey sym, SDLMod mod, Uint16 unicode) {

}

void Application::MouseMove(Uint16 x, Uint16 y, Sint16 xrel, Sint16 yrel, bool right, bool middle, bool left) {

}

void Application::Clean() {
  delete fps;
  display.close();
  SDL_Quit();
}


