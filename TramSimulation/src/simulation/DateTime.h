/* 
 * File:   DateTime.h
 * Author: bartek
 *
 * Created on 20 styczeń 2011, 19:03
 */

#ifndef DATETIME_H
#define	DATETIME_H

#include <string>
#include <ios>
#include <iostream>
#include <sstream>

using std::string;

namespace Sim {

  class TimeSpan {
  public:
    TimeSpan(int min = 0, int hour = 0);
    virtual ~TimeSpan();

    int getMinute() const;
    int getHour() const;
  protected:
    int min, hour;
  };

  class DateTimeSpan : public TimeSpan {
  public:
    DateTimeSpan(int min = 0, int hour = 0, int day = 0, int week = 0);
    DateTimeSpan(const TimeSpan & dt, int day = 0, int week = 0);
    virtual ~DateTimeSpan();


    int getDay() const;
    int getWeek() const;
  private:
    int day, week;
  };

  class Time {
  public:
    Time(int sec = 0, int min = 0, int hour = 0);
    virtual ~Time();



    virtual void adjust(int sec, int min = 0, int hour = 0);

    virtual operator string() const;
    Time operator+(const TimeSpan & st);
    Time & operator +=(const TimeSpan & dt);
    virtual bool operator==(const Time & t) const;
    virtual bool operator>(const Time & t) const;
    virtual bool operator>=(const Time & t) const;
    virtual bool operator<(const Time & t) const;
    virtual bool operator<=(const Time & t) const;
  protected:
    int sec,  min, hour;
  };

  class DateTime : public Time {
  public:
    static string DAYS_OF_WEEK[7];

    DateTime(int sec =0, int min = 0, int hour = 0, int day = 0, int week = 0);
    DateTime(const Time & t, int day = 0, int week = 0);
    virtual ~DateTime();

    const string & dayOfWeek() const;
    void adjust(int sec, int min =0, int hour = 0, int day = 0, int week = 0);

    virtual operator string() const;
    DateTime operator+(const DateTimeSpan & st);
    DateTime & operator +=(const DateTimeSpan & dt);
    virtual bool operator==(const DateTime & t) const;
    virtual bool operator>(const DateTime & t) const;
    virtual bool operator>=(const DateTime & t) const;
    virtual bool operator<(const DateTime & t) const;
    virtual bool operator<=(const DateTime & t) const;


  private:
    int day, week;

  };


}

#endif	/* DATETIME_H */

