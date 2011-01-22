#!/usr/bin/python

from xml.dom.minidom import Document
from xml.etree.ElementTree import Element
from encodings.utf_16 import encode
import sys
import urllib.error
import urllib.request
import xml.dom.minidom
import math

__author__="Bartłomiej Bułat <bartek.bulat at gmail.com>"
__date__ ="$2010-12-29 20:25:58$"

def main(argv):
  lineNum = [i for i in range(1, 25)]
  lineNum.extend([40, 50, 51])
  minN =60;
  maxN = 0;
  minE =60;
  maxE = 0;
  przystanki = {}

  for line in lineNum:
    #print("Linia {}:".format(line))
    file = open("linie/linia{}.xml".format(line), "r", -1, "utf8")
    xmlstring = file.read()
    xmlstring = xmlstring.replace("windows-1250", "utf-8")
    #print(xmlstring)
    file.close()

    doc = xml.dom.minidom.parseString(xmlstring)
    for l in doc.getElementsByTagName("l"):
      #print("l ----")
      for stop in l.getElementsByTagName("c"):
        if stop.hasAttribute("s"):
          t = stop.firstChild
          g = t.nextSibling
          name = stop.getAttribute("s")
          tt = float(t.firstChild.nodeValue)
          gg = float(g.firstChild.nodeValue)
          #print("{} {} {}".format(name, tt, gg) )
          if name in przystanki:
            if len([ el for el in przystanki[name] if el == (tt, gg) ]) == 0:
              przystanki[name].append( ( tt,gg) )
          else:
            przystanki[name] = [ (tt,gg) ]

          if tt > maxN:
            maxN = tt
          if tt < minN:
            minN = tt;

          if gg > maxE:
            maxE = gg
          if gg < minE:
            minE = gg;

  minTT = minN - 0.002;
  minGG = minE - 0.002;
  maxTT = maxN + 0.002;
  maxGG = maxE + 0.002;

  y = round(round(maxTT-minTT,4)*20000)
  x = round(round(maxGG-minGG,4)*20000)

  for przys, loc in przystanki.items():
    przystanki[przys] = [ ( round(round(e-minGG,4)*20000),y - round(round(n-minTT,4)*20000)  ) for n, e in loc]

  # @type doc Document
  doc = xml.dom.minidom.Document();
  root = doc.createElement("mapa")
  przyElem = doc.createElement('Przystanki')
  for przys, loc in przystanki.items():
    pElem = doc.createElement("Przystanek")
    pElem.setAttribute("name", przys)
    locsElem = doc.createElement("locations")
    for n, e in loc:
      locElem = doc.createElement("loc")
      locElem.setAttribute("x", str(n));
      locElem.setAttribute("y", str(e));
      locsElem.appendChild(locElem)
    pElem.appendChild(locsElem)
    przyElem.appendChild(pElem)
  sizeElem = doc.createElement("size")
  sizeElem.setAttribute("x", str(x))
  sizeElem.setAttribute("y", str(y) )
  root.appendChild(sizeElem)
  root.appendChild(przyElem)
  doc.appendChild(root)

  file = open("przystanki.xml", "w")
  file.write( doc.toxml() )
  file.close();
  print ( "File save OK!" )
    

  #print("N {}-{} E {}-{}".format(minN, maxN, minE, maxE))
  #print("N {} E {}".format( maxN -minN, maxE - minE))

  
  #print("Map size {}x{}".format(x, y))
  #print(przystanki["Kabel"])
  #print(przystanki["Bieżanowska"])
if __name__ == "__main__":
    main(sys.argv)
