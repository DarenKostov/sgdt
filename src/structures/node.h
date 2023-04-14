/*
  Daren Kostov

  Licence: GPLv3

  A node class that stores info about a node
    
*/


#ifndef NODE
#define NODE
#include <SFML/Graphics.hpp>


class Node{

  private:
    int XCoordinate;
    int YCoordinate;
    int Width;
    int Height;
    sf::RectangleShape body;


  public:

    //constructor with X, Y, W, and H
    Node(int, int, int, int);

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


    void draw();

    sf::RectangleShape getBody();
    
  
};


#endif