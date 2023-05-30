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

char Link::getColor(){
  return color;
}

void Link::setLabel(std::string in){
  label=in;
}
void Link::setColor(char in){
  color=in;
}
