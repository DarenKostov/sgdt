/*
  Daren Kostov

  Licence: GPLv3

  method definitions for the node class
    
*/

#include "node.h"


Node::Node(int x, int y, int w, int h, sf::Font& font){
  XCoordinate=x;
  YCoordinate=y;
  Width=w;
  Height=h;

  body=sf::RectangleShape();
  
  body.setPosition(x, y);
  body.setSize(sf::Vector2f(w, h));

  body.setOutlineColor(sf::Color::White);
  body.setFillColor(sf::Color::Transparent);
  body.setOutlineThickness(2);

  content.setString("New Text");
  content.setCharacterSize(20);
  content.setFont(font);
  content.setFillColor(sf::Color::White);
  content.setPosition(x, y);

}

int Node::getX(){
  return XCoordinate;
}
int Node::getY(){
  return YCoordinate;
}
int Node::getW(){
  return Width;
}
int Node::getH(){
  return Height;
}

void Node::setX(int in){
  XCoordinate=in;
  body.setPosition(in, YCoordinate);
}
void Node::setY(int in){
  YCoordinate=in;
  body.setPosition(XCoordinate, in);
}
void Node::setW(int in){
  Width=in;
  body.setSize(sf::Vector2f(in, Height));
}
void Node::setH(int in){
  Height=in;
  body.setSize(sf::Vector2f(Width, in));
}


void Node::draw(sf::RenderWindow& window){
  //TODO?
  // window.draw(body);
}

sf::RectangleShape Node::getBody(){
  return body;
}

sf::Text Node::getContent(){
  return content;
}
void Node::setContent(std::string in){
  content.setString(in);
}


bool Node::collidingWithCoords(int x, int y){
  
  if(x>XCoordinate && x<XCoordinate+Width)//we are on the same X level
    if(y>YCoordinate && y<YCoordinate+Height)//we are on the same Y level
      return true;
  return false;
}

