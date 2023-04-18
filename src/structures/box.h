/*
  Daren Kostov

  Licence: GPLv3

  A box class that is meant for gui
    
*/


#ifndef BOX
#define BOX
#include <SFML/Graphics.hpp>
#include <string>
#include "node.h"

class Box : public Node{

  private:
    sf::RectangleShape body;
    sf::Text contentText;

    //updates the postion and size of the content text
    void updateContentProperties();

  public:


    //previous cooredinates
    int prevXCoordinate;
    int prevYCoordinate;
    void updatePreviousCoordinates();

    //constructor with X, Y, W, and H (and font)
    Box(int, int, int, int, sf::Font&);

    ~Box();

    //set X & Y coordinates and width & height
    void setX(int);
    void setY(int);
    void setW(int);
    void setH(int);
    void move(int, int);

    void draw(sf::RenderWindow&);

    sf::RectangleShape getBody();

    //manages the content
    sf::Text getContentText();
    void setContent(std::string);
    
    //tells you weather or not the box is colliding with these coords
    bool collidingWithCoords(int, int);


  
};


#endif