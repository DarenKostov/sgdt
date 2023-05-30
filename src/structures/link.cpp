/*
  Daren Kostov

  Licence: GPLv3

  the logic of the Link class
  
*/

#include "link.h"


Link::Link(){
  style=continuous;
}
Link::~Link(){}



std::string Link::getLabel(){
  return label;
}

linkStyle Link::getStyle(){
  return style;
}
char Link::getColor(){
  return color;
}

void Link::setLabel(std::string in){
  label=in;
}
void Link::setStyle(linkStyle in){
  style=in;
}
void Link::setColor(char in){
  color=in;
}
