#!/usr/bin/python

import math
import sys
import xml.dom.minidom

import urllib.error
import urllib.request

__author__="Krzysiek"
__date__ ="$2011-01-26 22:00:01$"

def main(argv):
    numer = 20
    dzien = "Dzień powszedni"
    dzien_nr = 2   #0 - Święta, 1 - Soboty, 2 - Dzień powszedni

    # -------- parsowanie pliku z rozkladem brygadowym --------
    # w pliku godziny musza byc postaci x:xx albo xx:xx (z dwukropkiem!)
    # w pliku moga byc tylko godziny! (skasuj litery Z i podmiany na inne linie)
    # na poczatku pliku moze brakowac niektorych pustych tagow (gdy brygada nie
    #   rozpoczyna jako pierwsza) - dodaj te puste tagi!

    fileB = open("brygady/brygada{}.xml".format(numer), "r", -1, "utf-8")
    xmlstringB = fileB.read()
    xmlstringB = xmlstringB.replace("windows-1250", "utf-8")
    #print(xmlstringB)
    fileB.close()

    docB = xml.dom.minidom.parseString(xmlstringB)
    wiersze = docB.getElementsByTagName("Row")

    nazwy_petli = wiersze[0].getElementsByTagName("Data")  #pierwszy wiersz to nazwy petli
    nazwy_petli = nazwy_petli[1:]  #pierwszy element to slowo "brygada"

    brygady = wiersze[1:]

    # -------- parsowanie pliku z rozkladem linii --------

    fileR = open("rozklady/rozklad{}.xml".format(numer), "r", -1, "utf-8")
    xmlstringR = fileR.read()
    xmlstringR = xmlstringR.replace("windows-1250", "utf-8")
    #print(xmlstringR)
    fileR.close()

    docR = xml.dom.minidom.parseString(xmlstringR)
    przystanki = docR.getElementsByTagName("stop")
    licz_przyst = int(len(przystanki)/2)   #zalozenie: kazdy przystanek jest dwukierunkowy

    # -------- laczenie obydwu plikow (i tworzenie wynikowego pliku xml) --------

    doc = xml.dom.minidom.Document()
    root = doc.createElement("line")
    root.setAttribute("number", str(numer))

    for bryg in brygady:
        numer_bryg = bryg.getElementsByTagName("Data")[0].firstChild.nodeValue
        odjazdy = bryg.getElementsByTagName("Data")[1:]

        # do pliku xml:
        brygElem = doc.createElement("squad")
        brygElem.setAttribute("number", str(numer_bryg))

        dayElem = doc.createElement("day")
        dayElem.setAttribute("name", dzien)

        
        #print("----------------", numer_bryg, "----------------")
        for i in range(0,len(odjazdy)):
            if odjazdy[i].firstChild:
                #znajdz petle w rozkladzie linii:
                if nazwy_petli[i].firstChild.nodeValue == przystanki[0].getAttribute("name"):
                    #znajdz odjazd na rozkladzie petli:
                    rozkl_przyst = przystanki[0].getElementsByTagName("day")[dzien_nr].getElementsByTagName("time")
                    j = 0
                    print(odjazdy[i].firstChild.nodeValue, "=", rozkl_przyst[j].firstChild.nodeValue.strip())
                    while odjazdy[i].firstChild.nodeValue != rozkl_przyst[j].firstChild.nodeValue.strip():
                        j = j+1

                    #i lecimy po przystankach az do nastepnej petli:
                    for nr in range(0,licz_przyst):
                        rozkl_przyst = przystanki[nr].getElementsByTagName("day")[dzien_nr].getElementsByTagName("time")
                        czas = rozkl_przyst[j].firstChild.nodeValue.strip().split(':')

                        stopElem = doc.createElement("stop")
                        stopElem.setAttribute("hour", czas[0])
                        stopElem.setAttribute("minute", czas[1])
                        stopElem.appendChild( doc.createTextNode(przystanki[nr].getAttribute("name")) )
                        dayElem.appendChild(stopElem)

                        #print(przystanki[nr].getAttribute("name"), ":", rozkl_przyst[j].firstChild.nodeValue.strip())
                elif nazwy_petli[i].firstChild.nodeValue == przystanki[licz_przyst].getAttribute("name"):
                    #znajdz odjazd na rozkladzie petli:
                    rozkl_przyst = przystanki[licz_przyst].getElementsByTagName("day")[dzien_nr].getElementsByTagName("time")
                    j = 0
                    print(odjazdy[i].firstChild.nodeValue, "-", rozkl_przyst[j].firstChild.nodeValue.strip())
                    while odjazdy[i].firstChild.nodeValue != rozkl_przyst[j].firstChild.nodeValue.strip():
                        j = j+1
                    
                    #i lecimy po przystankach az do nastepnej petli:
                    for nr in range(licz_przyst,licz_przyst*2):
                        rozkl_przyst = przystanki[nr].getElementsByTagName("day")[dzien_nr].getElementsByTagName("time")
                        czas = rozkl_przyst[j].firstChild.nodeValue.strip().split(':')

                        stopElem = doc.createElement("stop")
                        stopElem.setAttribute("hour", czas[0])
                        stopElem.setAttribute("minute", czas[1])
                        stopElem.appendChild( doc.createTextNode(przystanki[nr].getAttribute("name")) )
                        dayElem.appendChild(stopElem)
                        #print(przystanki[nr].getAttribute("name"), ":", rozkl_przyst[j].firstChild.nodeValue.strip())
                else:
                    print("ERROR: Rozna liczba przystankow w roznych kierunkach!")


        brygElem.appendChild(dayElem)
        root.appendChild(brygElem)


    # --- zapis do pliku ---

    doc.appendChild(root)

    file = open("{}.xml".format(numer), "w")
    file.write(doc.toxml())
    file.close();
    print ("File save OK!")

if __name__ == "__main__":
    main(sys.argv)
