/*
  Daren Kostov

  Licence: GPLv3

  A link class that connects 2 nodes
    
*/

#include "string"

#ifndef LINK
#define LINK

//link styles
enum linkStyle {continuous, dashed, dotted};


class Link{
  protected:
    std::string label;

    linkStyle style;
  
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
  linkStyle getStyle();
  char getColor();
  
  //setters
  void setLabel(std::string);
  void setStyle(linkStyle);
  void setColor(char);
  

};



#endif

