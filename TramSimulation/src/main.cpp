/* 
 * File:   main.cpp
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:29
 */

#include <cstdlib>

#include "app/Application.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  Application app(800,600,32, "Symulacja Krakowskiej Sieci Tramwajowej");
  return app.Execute();
}

