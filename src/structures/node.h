/*
  Daren Kostov

  Licence: GPLv3

  A node class that stores info about a node
    
*/


#ifndef NODE
#define NODE
#include <SFML/Graphics.hpp>
#include <string>

class Node{

  private:
    int XCoordinate;
    int YCoordinate;
    int Width;
    int Height;
    sf::RectangleShape body;
    sf::Text content;

    //updates the postion and size of the content text
    void updateContentProperties();

  public:


    //previous cooredinates
    int prevXCoordinate;
    int prevYCoordinate;
    void updatePreviousCoordinates();

    //constructor with X, Y, W, and H (and font)
    Node(int, int, int, int, sf::Font&);

    //get X & Y coordinates and width & height
    int getX();
    int getY();
    int getW();
    int getH();

    //set X & Y coordinates and width & height
    void setX(int);
    void setY(int);
    void setW(int);
    void setH(int);
    void move(int, int);

    void draw(sf::RenderWindow&);

    sf::RectangleShape getBody();

    //manages the content
    sf::Text getContent();
    void setContent(std::string);
    
    //tells you weather or not the box is colliding with these coords
    bool collidingWithCoords(int, int);


  
};


#endif