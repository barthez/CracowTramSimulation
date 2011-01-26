/* 
 * File:   Simulation.cpp
 * Author: Bartłomiej Bułat <bartek.bulat at gmail.com>
 * 
 * Created on 21 styczeń 2011, 17:45
 */

#include "Simulation.h"

Simulation::Simulation(std::vector < std::string > schedules, std::string infrastructure) : board(infrastructure), simTime(2,1,5,2), timeSurf("-", "czcionka.ttf", 20) {
  timeSurf.setText(((std::string) simTime).c_str());
  timeSurf.setOffset(20, 550);

  
  std::vector< std::string >::iterator it;
  for (it = schedules.begin(); it != schedules.end(); ++it) {
    TiXmlDocument doc(it->c_str());
    if(! doc.LoadFile() )
      return;
      //throw TiXmlException("Błąd otwarcia pliku " + *it);

    TiXmlElement *linia, *brygada, *dzien, *przystanek;
    int l, b, g, m;
    std::string dz, przy;
    linia = doc.RootElement();
    linia->Attribute("number", &l);
    for(brygada = linia->FirstChildElement("squad"); brygada; brygada = brygada->NextSiblingElement("brygada") ) {
      brygada->Attribute("number", &b);
      Tram * t = new Tram(l,b);
      for(dzien = brygada->FirstChildElement("day"); dzien; dzien = dzien->NextSiblingElement("day")) {
        dz = dzien->Attribute("name");
        std::map< Time, std::string > rozklad;
        for(przystanek = dzien->FirstChildElement("stop"); przystanek; przystanek = przystanek->NextSiblingElement("stop") ) {
          przystanek->Attribute("hour", &g);
          przystanek->Attribute("minute", &m);
          przy = std::string(przystanek->FirstChildElement()->GetText());
          rozklad[ Time(m, g) ] = przy;          
        }
        t->addSchedule(dz, rozklad);
      }
      vehicles.push_back(t);
      board.insertTram(t);
    }

  }

}

Simulation::Simulation(const Simulation& orig) : timeSurf(orig.timeSurf) {

}

Simulation::~Simulation() {
}

Simulation * Simulation::operator= (const Simulation & s) {

}

void Simulation::update() {
  simTime.adjust(1);
  timeSurf.setText(((std::string) simTime).c_str());
  board.update(simTime);  
}

Board * Simulation::getBoard() {
  return &this->board;
}

Surface * Simulation::getTimeSurface() {
  return & this->timeSurf;
}