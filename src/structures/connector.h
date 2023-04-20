/*
  Daren Kostov

  Licence: GPLv3

  A class that connects 2 nodes in GUI
    
*/

#include "link.h"
#include "box.h"
#include <SFML/Graphics.hpp>

#ifndef CONNECTOR
#define CONNECTOR


class Connector : public Link{

  private:
    // Box* pointStart;
    // Box* pointEnd;
    // sf::Vertex line[2];
    
  public:
    Connector();
    ~Connector();

    //getters
    // std::string getLabel();
    // char getColor();
  
    // //setters
    // void setLabel(std::string);
    // void setColor(char);


};



#endif
