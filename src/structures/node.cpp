/*
  Daren Kostov

  Licence: GPLv3

  method definitions for the node class
    
*/

#include "node.h"


Node::Node(int x, int y, int w, int h, sf::Font& font){
  XCoordinate=x;
  YCoordinate=y;
  prevXCoordinate=x;
  prevYCoordinate=y;
  Width=w;
  Height=h;

  body=sf::RectangleShape();
  
  body.setPosition(x, y);
  body.setSize(sf::Vector2f(w, h));

  body.setOutlineColor(sf::Color::White);
  body.setFillColor(sf::Color::Transparent);
  body.setOutlineThickness(2);

  content.setString("*New Text*");
  content.setCharacterSize(20);
  content.setFont(font);
  content.setFillColor(sf::Color::White);


  
  updateContentProperties();

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
  updateContentProperties();
}
void Node::setY(int in){
  YCoordinate=in;
  body.setPosition(XCoordinate, in);
  updateContentProperties();
}
void Node::setW(int in){
  Width=in;
  body.setSize(sf::Vector2f(in, Height));
  updateContentProperties();
}
void Node::setH(int in){
  Height=in;
  body.setSize(sf::Vector2f(Width, in));
  updateContentProperties();
}

void Node::move(int dx, int dy){
  body.move(dx, dy);
  XCoordinate+=dx;
  YCoordinate+=dy;
  updateContentProperties();
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

  //if its the default value, erase it
  if(content.getString()=="*New Text*"){
    content.setString("");
    return;
  }
  
  content.setString(in);
  updateContentProperties();
}


bool Node::collidingWithCoords(int x, int y){
  
  if(x>XCoordinate && x<XCoordinate+Width)//we are on the same X level
    if(y>YCoordinate && y<YCoordinate+Height)//we are on the same Y level
      return true;
  return false;
}


void Node::updateContentProperties(){


  //center the origin of the text
  auto properties=content.getLocalBounds();
  content.setOrigin(properties.left+properties.width/2.0f, properties.top+properties.height/2.0f);

  //center the text on the box
  content.setPosition(XCoordinate+Width/2, YCoordinate+Height/2);

}


