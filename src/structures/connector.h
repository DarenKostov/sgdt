/*
  Daren Kostov

  Licence: GPLv3

  A class that connects 2 nodes in GUI
    
*/

#include "link.h"
#include "box.h"
#include <SFML/Graphics.hpp>
#include "guiElement.h"

#ifndef CONNECTOR
#define CONNECTOR


class Connector : public Link{

  private:
    Box* pointStart;
    Box* pointEnd;
    sf::Vertex line[2];
    
  public:
    Connector(Box*, Box*);
    ~Connector();

    //getters
    // std::string getLabel();
    // char getColor();
  
    // //setters
    // void setLabel(std::string);
    // void setColor(char);

    void updatePositions();

    //draws itself on a RenderWindow
    void draw(sf::RenderWindow&);

};



#endif
