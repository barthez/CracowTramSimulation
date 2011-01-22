#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "Bartłomiej Bułat <bartek.bulat at gmail.com>"
__date__ = "$2011-01-21 20:54:10$"

from ScheduleParser import TramScheduleParser
import urllib.error
import urllib.request
import xml.dom.minidom
import re

class ScheduleDownloader:
  __adres = "http://rozklady.mpk.krakow.pl/aktualne/{linia:04d}/{linia:04d}t{stopnum:03d}.htm"
  stop = 0
  linia = 0;

  def __init__(self, linia):
    self.linia = linia

  def getSchedule(self):
    rozklady = {}
    tries = 3;

    
    while 1:
      try:
        self.stop += 1;
        #print(":::::::::::::::::::::::::::::::::::::::: {} ::::".format(self.stop))
        #print(self.__adres.format(linia=self.linia, stopnum=self.stop))
        strona = urllib.request.urlopen(self.__adres.format(linia=self.linia, stopnum=self.stop))
        tresc = strona.read()
        rozklad = tresc.decode("iso-8859-2")
        parser = TramScheduleParser()
        parser.feed(rozklad)
        rozklady[self.stop] = (parser.name, parser.rozklad)
        parser.close()
        #print(parser.name)
        #print(parser.rozklad)
      except urllib.error.HTTPError as _:
        tries -= 1;
        if tries == 0:
          break;
        pass
    return rozklady
    

if __name__ == "__main__":
  #lineNum = [i for i in range(1, 25)]
  #lineNum.extend([40, 51, 51])
  lineNum = [51]

  

  for line in lineNum:
    try:
      doc = xml.dom.minidom.Document()
      print("Linia {}".format(line))
      root = doc.createElement("tramline")
      root.setAttribute("number", str(line))
      down = ScheduleDownloader(line)
      print("Pobieram dane...")
      sche = down.getSchedule()
      for stop, schedule in sche.items():
        print("Przystanek {}. {}".format(stop, schedule[0]))
        stopElem = doc.createElement("stop")
        stopElem.setAttribute("number", str(stop))
        stopElem.setAttribute("name", schedule[0])
        for day, hours in schedule[1].items():
          dayElem = doc.createElement("day")
          dayElem.setAttribute("name", day)
          for h in hours:
            if re.match("^\d{1,2}\:\d{2}A?$", h) == None:
              raise Exception("linia {}/{}/{}/{}:  '{}' nie jest czasem".format(line, stop, schedule[0], day, h))
            hElem = doc.createElement("time")
            timeNode = doc.createTextNode(str(h))
            hElem.appendChild(timeNode)
            dayElem.appendChild(hElem)
          stopElem.appendChild(dayElem)
        root.appendChild(stopElem)
      doc.appendChild(root)
      tresc = doc.toprettyxml("  ")
      file = open("rozklady/rozklad{}.xml".format(line), "w")
      file.write(tresc)
      file.close()
    except Exception as er:
      print(er)
      
      


