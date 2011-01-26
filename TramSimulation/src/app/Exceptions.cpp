/*
 * File:   Exceptions.cpp
 * Author: Bartłomiej Bułat <bartek.bulat at gmail.com>
 *
 * Created on 18 styczeń 2011, 16:11
 */

#include "Exceptions.h"


ApplicationException::ApplicationException(const string & s) throw() : std::exception() {
  this->msg = s;
}

const char * ApplicationException::what() const throw(){
  return msg.c_str();
}

SDLException::SDLException(const string & m)  throw() : ApplicationException(m) {

}

const char * SDLException::what() const throw(){
  return ApplicationException::what();
}

TTFException::TTFException(const string & m)  throw() : SDLException(m) {

}

TiXmlException::TiXmlException(const string & m) throw() : ApplicationException(m) {

}