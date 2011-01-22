#! /usr/bin/python

# To change this template, choose Tools | Templates
# and open the template in the editor.

__author__ = "Bartłomiej Bułat <bartek.bulat at gmail.com>"
__date__ = "$2011-01-21 19:01:28$"

import html.parser
import urllib.request
import math

class TramScheduleParser(html.parser.HTMLParser):
  def __init__(self):
    html.parser.HTMLParser.__init__(self)
    self.tables = 0;
    self.stable = False;
    self.row = 0;
    self.days = [];
    self.column = 0;
    self.rozklad = {}
    self.info = False;
    self.bs = 0;
    self.isName = False;
    self.name =""


  def feed(self, feed):
    html.parser.HTMLParser.feed(self, feed)
    #print(self.name)
    #print(self.rozklad)

    #print("########################################")
    for day, hours in self.rozklad.items():
      newHours = []
      for hour in hours:
        #print(hour)
        newHours.extend([ "{}:{}".format(hour[0], min) for min in hour[1] ])
      self.rozklad[day] = newHours;
    

  def handle_starttag(self, tag, attrs):
    if tag == "table":
      self.handle_table_start(attrs)
    if tag == "tr":
      self.tr_start(attrs)
    if tag == "td":
      self.td_start(attrs)
    if tag == "b":
      self.b_start(attrs)

  def handle_endtag(self, tag):
    if tag == "table":
      self.handle_table_end()
    if tag == "tr":
      self.tr_end()

  def b_start(self, attrs):
    self.bs += 1;
    if self.bs == 2:
      self.isName = True

  def handle_table_start(self, attrs):
    bgcolor = [el[1] for el in attrs if el[0] == "bgcolor"]
    if len(bgcolor) == 1 and bgcolor[0] == '#EFF7FF':
      self.stable = True;
    if self.stable:
      self.tables += 1;

  def handle_table_end(self):
    if self.stable:
      self.tables -= 1;
      if self.tables == 0:
        self.stable = False

  def td_start(self, attrs):
    colspan = [el[1] for el in attrs if el[0] == "colspan"]
    if len(colspan) == 1 and colspan[0] == '6':
      #print( colspan[0] )
      self.info = True

  def tr_start(self, attrs):
    if self.stable:
      self.row += 1;
    pass

  def tr_end(self):
    if self.stable:
      self.column = 0;
    pass

  def handle_data(self, data):
    if self.isName:
      self.name = data
      self.isName = False
    if data[:3] == "Zak":
      self.info = True
    if self.info:
      return
    if self.row == 1:
      self.days.append(data);
      self.rozklad[data] = [];
    if self.row > 1:
      day = self.days[math.floor(self.column/2)]
      if self.column % 2 == 0:
        self.rozklad[day].append([data]);
      else:
        self.rozklad[day][self.row-2].append([min for min in data.split(" ") if min != '' and min != '-']);
      #print("{}: {}".format(self.column, data))
    if self.stable:
      self.column += 1



if __name__ == "__main__":
  adres = "http://rozklady.mpk.krakow.pl/aktualne/{linia:04d}/{linia:04d}t{stop:03d}.htm"
  strona = urllib.request.urlopen(adres.format(linia=40, stop=111))
  tresc = strona.read()
  rozklad = tresc.decode("iso-8859-2")
  parser = TramScheduleParser()
  parser.feed(rozklad)

  print( parser.name )
  print( str(parser.rozklad))
