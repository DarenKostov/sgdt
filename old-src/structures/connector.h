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

    //constructir, give it the start & end points (Boxes)
    Connector(Box*, Box*, linkStyle);

    //does nothing
    ~Connector();

    //empty constructor DO NOT use unless needed, will give segfault if you touch it without initializing the start & end points
    Connector();
    Connector(linkStyle);

    //getters
    // std::string getLabel();
    // char getColor();
  
    // //setters
    // void setLabel(std::string);
    // void setColor(char);  

    sf::Vector2f getStart();
    sf::Vector2f getEnd();
  
    void setStart(Box*);
    void setEnd(Box*);

    //tels you if the coordinates (with 1x1 size) collide with the link
    bool collidingWithCoords(sf::Vector2i);

    void updatePositions();

    //draws itself on a RenderWindow
    void draw(sf::RenderWindow&);

};



#endif
