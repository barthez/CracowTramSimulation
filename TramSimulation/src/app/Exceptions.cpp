/*
 * File:   Exceptions.cpp
 * Author: Bartłomiej Bułat <bartek.bulat at gmail.com>
 *
 * Created on 18 styczeń 2011, 16:11
 */

#include "Exceptions.h"

ApplicationException::ApplicationException() {
  std::exception();
}

ApplicationException::ApplicationException(const char * msg) {
  this->msg = new char[strlen(msg) + 1];
  strcpy(this->msg, msg);
}

ApplicationException::ApplicationException(const ApplicationException * ex) {
  this->msg = new char[strlen(ex->msg) + 1];
  strcpy(this->msg, ex->msg);
}

const char * ApplicationException::what() {
  return msg;
}

ApplicationException::~ApplicationException() throw () {
  if (msg != NULL) {
    delete [] msg;
    msg = NULL;
  }
}

SDLException::SDLException(const char* m) : ApplicationException(m) {

}

TTFException::TTFException(const char* m) : SDLException(m) {

}