/* 
 * File:   Exceptions.h
 * Author: bartek
 *
 * Created on 18 styczeń 2011, 17:53
 */

#ifndef EXCEPTIONS_H
#define	EXCEPTIONS_H

#include <exception>
#include <cstring>

class ApplicationException : public std::exception {
public:
  ApplicationException();
  ApplicationException(const char * msg);
  ApplicationException(const ApplicationException * ex);
  virtual ~ApplicationException() throw ();

  virtual const char * what();
private:
  char * msg;
};

class SDLException : public ApplicationException {
public:
  SDLException(const char * m);
};

class TTFException : public SDLException {
public:
  TTFException(const char * m);
};

#endif	/* EXCEPTIONS_H */

