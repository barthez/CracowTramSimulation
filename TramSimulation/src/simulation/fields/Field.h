/* 
 * File:   Field.h
 * Author: bartek
 *
 * Created on 29 grudzień 2010, 20:38
 */

#ifndef FIELD_H
#define	FIELD_H

#include <string>

class Field {
public:
    Field(std::string name = "Puste pole");
    Field(const Field& orig);
    virtual ~Field();

    virtual const std::string & getName() const;
private:
  std::string name;
};

#endif	/* FIELD_H */

