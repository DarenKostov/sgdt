/*
  Daren Kostov

  Licence: GPLv3

  the logic of the Connector class
  
*/
  


#include "connector.h"


Connector::Connector(Box* start, Box* end){
  pointStart=start;
  pointEnd=end;
  updatePositions();

}
Connector::~Connector(){}


void Connector::updatePositions(){
  line[0]=sf::Vertex(sf::Vector2f(pointStart->getX()+pointStart->getW()/2, pointStart->getY()+pointStart->getH()/2));
  line[1]=sf::Vertex(sf::Vector2f(pointEnd->getX()+pointEnd->getW()/2, pointEnd->getY()+pointEnd->getH()/2));
}

void Connector::draw(sf::RenderWindow& window){
  window.draw(line, 2, sf::Lines);
}
