/*
  Daren Kostov

  Licence: GPLv3

  method definitions for the node class
    
*/

#include "box.h"


Box::Box(int x, int y, int w, int h, sf::Font& font): Node(x, y, w, h){
  prevXCoordinate=x;
  prevYCoordinate=y;
  lineThickness=2;
  
  body=sf::RectangleShape();
  
  body.setPosition(x, y);
  body.setSize(sf::Vector2f(w, h));

  body.setOutlineColor(sf::Color::White);
  body.setFillColor(sf::Color::Transparent);

  
  body.setOutlineThickness(lineThickness);
  
  
  outerBody=body;
  outerBody.setOutlineThickness(lineThickness*3);

  outerBody.move(lineThickness, lineThickness);
  outerBody.setSize(sf::Vector2f(w-lineThickness*2, h-lineThickness*2));
  

  contentText.setString(content);
  contentText.setCharacterSize(20);
  contentText.setFont(font);
  contentText.setFillColor(sf::Color::White);


  
  updateContentProperties();

}


Box::~Box(){}

  
void Box::updatePreviousCoordinates(){
  prevXCoordinate=XCoordinate;
  prevYCoordinate=YCoordinate;
}


void Box::setX(int in){
  XCoordinate=in;
  body.setPosition(in, YCoordinate);
  outerBody.setPosition(in+lineThickness, YCoordinate+lineThickness);
  updateContentProperties();
}
void Box::setY(int in){
  YCoordinate=in;
  body.setPosition(XCoordinate, in);
  outerBody.setPosition(XCoordinate+lineThickness, in+lineThickness);
  updateContentProperties();
}
void Box::setW(int in){
  Width=in;
  body.setSize(sf::Vector2f(in, Height));
  outerBody.setSize(sf::Vector2f(in-lineThickness*2, Height-lineThickness*2));
  updateContentProperties();
}
void Box::setH(int in){
  Height=in;
  body.setSize(sf::Vector2f(Width, in));
  outerBody.setSize(sf::Vector2f(Width-lineThickness*2, in-lineThickness*2));
  updateContentProperties();
}

void Box::move(int dx, int dy){
  body.move(dx, dy);
  XCoordinate+=dx;
  YCoordinate+=dy;
  updateContentProperties();
}


sf::RectangleShape Box::getBody(){
  return body;
}

sf::Text Box::getContentText(){
  return contentText;
  
}
void Box::setContent(std::string in){
  Node::setContent(in);
  
  
  contentText.setString(content);
  updateContentProperties();
}


bool Box::collidingWithCoords(int x, int y){
  
  if(x>XCoordinate && x<XCoordinate+Width)//we are on the same X level
    if(y>YCoordinate && y<YCoordinate+Height)//we are on the same Y level
      return true;
  return false;
}


void Box::updateContentProperties(){

  //center the origin of the text
  auto properties=contentText.getLocalBounds();
  contentText.setOrigin(properties.left+properties.width/2.0f, properties.top+properties.height/2.0f);

  //center the text on the box
  contentText.setPosition(XCoordinate+Width/2, YCoordinate+Height/2);

}


void Box::draw(sf::RenderWindow& window){
  window.draw(body);
  window.draw(contentText);
}

void Box::drawHighlight(sf::RenderWindow& window){
  outerBody.setOutlineColor(sf::Color(255, 66, 0, 255));
  window.draw(outerBody);
}
void Box::drawSelected(sf::RenderWindow& window){
  outerBody.setOutlineColor(sf::Color(255, 162, 0, 255));
  window.draw(outerBody);
}
void Box::drawHovered(sf::RenderWindow& window){
  outerBody.setOutlineColor(sf::Color(0, 162, 255, 255));
  window.draw(outerBody);
}

