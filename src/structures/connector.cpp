/*
  Daren Kostov

  Licence: GPLv3

  the logic of the Connector class
  
*/
  


#include "connector.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

Connector::Connector(Box* start, Box* end){
  pointStart=start;
  pointEnd=end;
  updatePositions();

}
Connector::~Connector(){}


void Connector::updatePositions(){

  
  
  
  sf::Vector2f pointA=sf::Vector2f(pointStart->getX()+pointStart->getW()/2, pointStart->getY()+pointStart->getH()/2);
  sf::Vector2f pointB=sf::Vector2f(pointEnd->getX()+pointEnd->getW()/2, pointEnd->getY()+pointEnd->getH()/2);
  sf::Vector2f pointBTmp=pointB;

  
  {
    float rectMinX=pointEnd->getX();
    float rectMinY=pointEnd->getY();
    float rectMaxX=pointEnd->getX()+pointEnd->getW();
    float rectMaxY=pointEnd->getY()+pointEnd->getH();

    if(pointA.x<rectMinX)
      pointB.x=rectMinX;
    else if(pointA.x>rectMaxX)
      pointB.x=rectMaxX;

    if(pointA.y<rectMinY)
      pointB.y=rectMinY;
    else if(pointA.y>rectMaxY)
      pointB.y=rectMaxY;
  }
  
  {
    float rectMinX=pointStart->getX();
    float rectMinY=pointStart->getY();
    float rectMaxX=pointStart->getX()+pointStart->getW();
    float rectMaxY=pointStart->getY()+pointStart->getH();

    if(pointBTmp.x<rectMinX)
      pointA.x=rectMinX;
    else if(pointBTmp.x>rectMaxX)
      pointA.x=rectMaxX;

    if(pointBTmp.y<rectMinY)
      pointA.y=rectMinY;
    else if(pointBTmp.y>rectMaxY)
      pointA.y=rectMaxY;
  }
  
      
  

  
  line[0]=sf::Vertex(pointA);
  line[1]=sf::Vertex(pointB);

  // https://stackoverflow.com/questions/2339487/calculate-angle-of-2-points
  float angle=atan2(pointA.y-pointB.y, pointA.x-pointB.x);


  
  // https://stackoverflow.com/questions/29456466/calculate-a-point-which-is-perpendicular-to-a-line
  {
    float x=pointB.x+cos(angle+M_PI/6)*25;
    float y=pointB.y+sin(angle+M_PI/6)*25;
    arrow[0]=sf::Vertex(sf::Vector2f(x, y));
  } 
  arrow[1]=line[1];
  {
    float x=pointB.x+cos(angle-M_PI/6)*25;
    float y=pointB.y+sin(angle-M_PI/6)*25;
    arrow[2]=sf::Vertex(sf::Vector2f(x, y));
  } 


}

void Connector::draw(sf::RenderWindow& window){
  window.draw(line, 2, sf::Lines);
  window.draw(arrow, 3, sf::LinesStrip);
}
