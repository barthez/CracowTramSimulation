/* 
 * File:   Field.cpp
 * Author: bartek
 * 
 * Created on 29 grudzień 2010, 20:38
 */

#include "Field.h"

Field::Field(std::string name) {
  this->name = name;
}

Field::Field(const Field& orig) {
}

Field::~Field() {
}

const std::string & Field::getName() const {
  return this->name;
}