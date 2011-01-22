/* 
 * File:   Exceptions.h
 * Author: bartek
 *
 * Created on 18 styczeń 2011, 17:53
 */

#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

#include <exception>
#include <string>

using std::string;

class ApplicationException : public std::exception {
public:
  ApplicationException(const string & msg = "Application Exception") throw();
  virtual ~ApplicationException() throw() {}

  virtual const char * what() throw();
private:
  string msg;
};

class SDLException : public ApplicationException {
public:
  SDLException(const string & m = "SDL Exception") throw();
};

class TTFException : public SDLException {
public:
  TTFException(const string & m = "TTF Exception") throw();
};

class TiXmlException : public ApplicationException {
public:
  TiXmlException(const string & m = "TiXml Exception") throw();
};

#endif	/* EXCEPTIONS_H */

