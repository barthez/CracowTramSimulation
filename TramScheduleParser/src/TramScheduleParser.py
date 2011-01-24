#!/usr/bin/python

import math
import sys
import xml.dom.minidom

import urllib.error
import urllib.request

__author__ = "Bartłomiej Bułat <bartek.bulat at gmail.com>"
__date__ = "$2010-12-29 20:25:58$"

def main(argv):
  lineNum = [i for i in range(1, 25)]
  lineNum.extend([40, 50, 51])
  minN = 60;
  maxN = 0;
  minE = 60;
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
          if not name in przystanki:
            przystanki[name] = {"location": []}
          if not (tt,gg) in przystanki[name]["location"]:
            przystanki[name]["location"].append( (tt, gg) )

          if tt > maxN:
            maxN = tt
          if tt < minN:
            minN = tt;

          if gg > maxE:
            maxE = gg
          if gg < minE:
            minE = gg;

  for name, info in przystanki.items():
    xx = [a for a, b in przystanki[name]["location"]];
    yy = [b for b, b in przystanki[name]["location"]];
    przystanki[name]["mean_location"] = (sum(xx) / len(xx), sum(yy) / len(yy))
    przystanki[name]["locations_number"] = len(przystanki[name]["location"])

  connections = [];

  for line in lineNum:
    rozklad = xml.dom.minidom.parse("rozklady/rozklad{}.xml".format(line))
    for p in rozklad.getElementsByTagName("stop"):
      next = p.nextSibling.nextSibling;
      prev = p.previousSibling.previousSibling;
      name = p.getAttribute("name")
      if not "directions" in przystanki[name]:
        przystanki[name]["directions"] = []
      if not "stops" in przystanki[name]:
        przystanki[name]["stops"] = { "from" : [], "to" : [] }

      if next == None:
        next = p.parentNode.firstChild.nextSibling
      if prev == None:
        prev = p.parentNode.lastChild.previousSibling

      nextName = next.getAttribute("name")
      prevName = prev.getAttribute("name")

      pair = (prevName, nextName)
      if not pair in przystanki[name]["directions"]:
        przystanki[name]["directions"].append( pair )

      conn = (name, nextName)
      if not conn in connections:
        connections.append( conn )

      if next != None:
        nextName = next.getAttribute("name")
        if not nextName in przystanki[name]["stops"]["to"]:
          przystanki[name]["stops"]["to"].append( nextName )

      if prev != None:
        prevName = prev.getAttribute("name")
        if not prevName in przystanki[name]["stops"]["from"]:
          przystanki[name]["stops"]["from"].append( prevName )

  minTT = minN;
  minGG = minE;
  maxTT = maxN;
  maxGG = maxE;

  factor = 5000;

  y = round(round(maxTT-minTT, 4) * factor)
  x = round(round(maxGG-minGG, 4) * factor)



  for przys, info in przystanki.items():
    #przystanki[przys]["location"] = [(round(round(e-minGG, 4) * factor), y - round(round(n-minTT, 4) * factor)) for n, e in info["location"]]
    (n, e) = info["mean_location"]
    przystanki[przys]["mean_location"] = (round(round(e-minGG, 4) * factor), y - round(round(n-minTT, 4) * factor) )

  print(len(przystanki))
  # @type doc Document
  doc = xml.dom.minidom.Document();
  root = doc.createElement("TramMap")
  przyElem = doc.createElement('TramStops')
  for przys, info in przystanki.items():
    #print("Przystanek: {}".format(przys));
    #print("    info: {}".format( info["directions"] ))
    #print("    info: {}".format( info["locations_number"] ))
#    print("    to: {}".format( przystanki[przys]["stops"]["to"]))
#    print("    MeanLoc: {}/{}".format( przystanki[przys]["mean_location"], przystanki[przys]["location"] ) )
    pElem = doc.createElement("TramStop")
    pElem.setAttribute("name", przys)
    pElem.setAttribute("locations", str(info["locations_number"]))
    #początek lokalizacji
    locElem = doc.createElement("location")
    (n, e) = info["mean_location"]
    locElem.setAttribute("x", str(n))
    locElem.setAttribute("y", str(e))
    pElem.appendChild(locElem)
    #koniec lokalizacji

    #poczatek przystanków z i do
    prevElem = doc.createElement("PrevStops")
    for s in info["stops"]["from"]:
      prevStopElem = doc.createElement("Stop")
      prevStopElem.appendChild( doc.createTextNode(s))
      prevElem.appendChild(prevStopElem)

    nextElem = doc.createElement("NextStops")
    for s in info["stops"]["to"]:
      nextStopElem = doc.createElement("Stop")
      nextStopElem.appendChild( doc.createTextNode(s))
      nextElem.appendChild(nextStopElem)

    pElem.appendChild(prevElem)
    pElem.appendChild(nextElem)

    przyElem.appendChild(pElem)
  sizeElem = doc.createElement("size")
  sizeElem.setAttribute("x", str(x))
  sizeElem.setAttribute("y", str(y))

  connElem = doc.createElement("Connections")
  connElem.setAttribute("connections", str(len(connections)))
  for _from, _to in connections:
    cElem = doc.createElement("Connect")
    cElem.setAttribute("from", _from)
    cElem.setAttribute("to", _to)
    connElem.appendChild(cElem)

  root.appendChild(sizeElem)
  root.appendChild(przyElem)
  root.appendChild(connElem)
  doc.appendChild(root)

  file = open("przystanki.xml", "w")
  file.write(doc.toxml())
  file.close();
  print ("File save OK!")

 
    

  #print("N {}-{} E {}-{}".format(minN, maxN, minE, maxE))
  #print("N {} E {}".format( maxN -minN, maxE - minE))

  
  #print("Map size {}x{}".format(x, y))
  #print(przystanki["Kabel"])
  #print(przystanki["Bieżanowska"])
if __name__ == "__main__":
  main(sys.argv)
