/* 
 * File:   DateTime.cpp
 * Author: bartek
 * 
 * Created on 20 styczeń 2011, 19:03
 */



#include "DateTime.h"

namespace Sim {

  string DateTime::DAYS_OF_WEEK[7] = {"Niedziela", "Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota"};

  TimeSpan::TimeSpan(int min, int hour) {
    this->min = min % 60;
    this->hour = hour + (min / 60);
  }

  TimeSpan::~TimeSpan() {

  }

  void TimeSpan::adjust(int min, int hour) {
    if (min < 0) {
      this->hour -= ((-min) / 60 + (this->min + (-min) % 60) / 60);
      this->min = (-(this->min + min)) % 60;
    } else {
      this->min += min;
      this->hour += hour + (this->min / 60);
      this->min %= 60;
    }
    this->hour + hour;

  }

  int TimeSpan::getHour() const {
    return this->hour;
  }

  int TimeSpan::getMinute() const {
    return this->min;
  }

  DateTimeSpan::DateTimeSpan(int min, int hour, int day, int week) : TimeSpan(min, hour) {
    this->day = day + this->hour / 24;
    this->hour %= 24;
    this->week = week + this->day / 7;
    this->day %= 7;

  }

  DateTimeSpan::DateTimeSpan(const TimeSpan & dt, int day, int week) {
    DateTimeSpan(dt.getMinute(), dt.getHour(), day, week);

  }

  DateTimeSpan::~DateTimeSpan() {

  }

  void DateTimeSpan::adjust(int min, int hour, int day, int week) {
    TimeSpan::adjust(min, hour);
    this->day += day + this->hour / 24;
    this->hour %= 24;
    this->week += week + this->day / 7;
    this->day %= 7;

  }

  Time::Time(int min, int hour) {
    this->min = min%60;
    this->hour = hour + (min/60);
  }

  Time::~Time() {

  }

  Time::operator string() const {
    std::ostringstream ss(std::ios::out);
    ss.width(2);
    ss << hour << ":";
    ss.width(2);
    ss.fill('0');
    ss << min;
    return ss.str();
  }

  Time Time::operator+(const TimeSpan & dt) {
    return Time(this->min + dt.getMinute(), this->hour += dt.getHour() );
    
  }

  Time & Time::operator +=(const TimeSpan & dt) {
    this->min += dt.getMinute();
    this->hour = hour + (this->min/60);
    this->min %= 60;
  }

  bool Time::operator==(const Time & t) {
    return this->hour == t.hour && this->min == t.min;
  }

  bool Time::operator>(const Time & t) {
    return this->hour > t.hour || (this->hour == t.hour && this->min > t.min);
  }

  bool Time::operator>=(const Time & t) {
    return this->operator ==(t) && this->operator >(t);
  }

  bool Time::operator<(const Time & t) {
    return this->hour < t.hour || (this->hour == t.hour && this->min < t.min);
  }

  bool Time::operator<=(const Time & t) {
    return this->operator ==(t) && this->operator <(t);
  }


}