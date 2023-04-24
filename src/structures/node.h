/*
  Daren Kostov

  Licence: GPLv3

  A node class that stores info about a node
    
*/


#ifndef NODE
#define NODE
#include <string>

class Node{

  protected:
    int XCoordinate;
    int YCoordinate;
    int Width;
    int Height;
    std::string content;

    //used to identify this node
    long id;

    
  public:



    //constructor with X, Y, W, and H (and font)
    Node(int, int, int, int);


    virtual ~Node();

    //get X & Y coordinates and width & height
    int getX();
    int getY();
    int getW();
    int getH();

    //set X & Y coordinates and width & height
    virtual void setX(int);
    virtual void setY(int);
    virtual void setW(int);
    virtual void setH(int);
    virtual void move(int, int);


    std::string getContent();
    virtual void setContent(std::string);
    
    //tells you weather or not the box is colliding with these coords
    bool collidingWithCoords(int, int);


    //id stuff
    long getId();
    void changeId(long);

  
};


#endif