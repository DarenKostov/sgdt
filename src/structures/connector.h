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

    // shape
    sf::Vertex line[2];
    sf::Vertex arrow[3];


    // positioning mode
    /*
      0-wacky
      1-closest that touches the border
    */
    int positioningMode;

    //updates the point you give it with a specific algorythm
    void updatePositionsWacky(sf::Vector2f&, sf::Vector2f&);
    void updatePositionsClosest(sf::Vector2f&, sf::Vector2f&);
    
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
