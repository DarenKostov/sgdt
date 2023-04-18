/*
  Daren Kostov

  Licence: GPLv3

  A link class that connects 2 nodes
    
*/

#include "string"

#ifndef LINK
#define LINK

class Link{
  protected:
    std::string label;
  
    /*
    r-red
    o-orange
    y-yellow
    g-green
    b-blue
    p-purple
    m-magenta
    c-cyan
    w-white
    k-black
    a-gray
    */
    char color;

  public:

  Link();
  virtual ~Link();

  //getters
  std::string getLabel();
  char getColor();
  
  //setters
  void setLabel(std::string);
  void setColor(char);
  

};



#endif

