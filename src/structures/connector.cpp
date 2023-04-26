/*
  Daren Kostov

  Licence: GPLv3

  the logic of the Connector class
  
*/
  


#include "connector.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

//the bool value tells you if there is an intersection
sf::Vector2f getIntersection(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f, bool&);
sf::Vector2f getIntersection(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);


Connector::Connector(Box* start, Box* end){
  pointStart=start;
  pointEnd=end;

  
  positioningMode=1;
  updatePositions();
}

Connector::Connector(){
  pointStart=nullptr;
  pointEnd=nullptr;
  positioningMode=1;
}


Connector::~Connector(){}


sf::Vector2f Connector::getStart(){
  return line[0].position;
}
sf::Vector2f Connector::getEnd(){
  return line[1].position;
}

void Connector::setStart(Box* in){
  pointStart=in;

  if(pointEnd!=nullptr)
    updatePositions();
}
void Connector::setEnd(Box* in){
  pointEnd=in;
  
  if(pointStart!=nullptr)
    updatePositions();
}

void Connector::updatePositions(){

  sf::Vector2f pointA;
  sf::Vector2f pointB;
  
  
  switch(positioningMode){
    case 0:
      updatePositionsWacky(pointA, pointB);
      break;
    case 1:
      updatePositionsClosest(pointA, pointB);
      break;
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


void Connector::updatePositionsWacky(sf::Vector2f& pointA, sf::Vector2f& pointB){
  pointA=sf::Vector2f(pointStart->getX()+pointStart->getW()/2, pointStart->getY()+pointStart->getH()/2);
  pointB=sf::Vector2f(pointEnd->getX()+pointEnd->getW()/2, pointEnd->getY()+pointEnd->getH()/2);

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
}
void Connector::updatePositionsClosest(sf::Vector2f& pointA, sf::Vector2f& pointB){


  pointA=sf::Vector2f(pointStart->getX()+pointStart->getW()/2, pointStart->getY()+pointStart->getH()/2);
  pointB=sf::Vector2f(pointEnd->getX()+pointEnd->getW()/2, pointEnd->getY()+pointEnd->getH()/2);
  sf::Vector2f pointATmp=pointA;
  sf::Vector2f pointBTmp=pointB;



  //Manage ending point
  {
    float rectMinX=pointEnd->getX();
    float rectMinY=pointEnd->getY();
    float rectMaxX=pointEnd->getX()+pointEnd->getW();
    float rectMaxY=pointEnd->getY()+pointEnd->getH();

  
    float rectCenterX=pointEnd->getX()+pointEnd->getW()/2;
    float rectCenterY=pointEnd->getY()+pointEnd->getH()/2;

    bool didItHappen=false;

    if(pointA.x<=rectCenterX)
      pointB=getIntersection(pointA, pointB, sf::Vector2f(rectMinX, rectMinY), sf::Vector2f(rectMinX, rectMaxY), didItHappen);
    else
      pointB=getIntersection(pointA, pointB, sf::Vector2f(rectMaxX, rectMinY), sf::Vector2f(rectMaxX, rectMaxY), didItHappen);

    if(didItHappen==false){
      if(pointA.y<=rectCenterY)
        pointB=getIntersection(pointA, pointBTmp, sf::Vector2f(rectMinX, rectMinY), sf::Vector2f(rectMaxX, rectMinY), didItHappen);
      else
        pointB=getIntersection(pointA, pointBTmp, sf::Vector2f(rectMinX, rectMaxY), sf::Vector2f(rectMaxX, rectMaxY), didItHappen);
    }

      //no intersections?? at least have the point on the box
      if(didItHappen==false)
        pointB=pointBTmp;
  
  }

  //Manage starting point
  {
    float rectMinX=pointStart->getX();
    float rectMinY=pointStart->getY();
    float rectMaxX=pointStart->getX()+pointStart->getW();
    float rectMaxY=pointStart->getY()+pointStart->getH();
  
    float rectCenterX=pointStart->getX()+pointStart->getW()/2;
    float rectCenterY=pointStart->getY()+pointStart->getH()/2;

    bool didItHappen=false;

    if(pointBTmp.x<=rectCenterX)
      pointA=getIntersection(pointA, pointBTmp, sf::Vector2f(rectMinX, rectMinY), sf::Vector2f(rectMinX, rectMaxY), didItHappen);
    else
      pointA=getIntersection(pointA, pointBTmp, sf::Vector2f(rectMaxX, rectMinY), sf::Vector2f(rectMaxX, rectMaxY), didItHappen);

    if(didItHappen==false){
      if(pointBTmp.y<=rectCenterY)
        pointA=getIntersection(pointATmp, pointBTmp, sf::Vector2f(rectMinX, rectMinY), sf::Vector2f(rectMaxX, rectMinY), didItHappen);
      else
        pointA=getIntersection(pointATmp, pointBTmp, sf::Vector2f(rectMinX, rectMaxY), sf::Vector2f(rectMaxX, rectMaxY), didItHappen);
    }


      //no intersections?? at least have the point on the box
      if(didItHappen==false)
        pointA=pointATmp;

  
  }

    
}


// https://flassari.is/2008/11/line-line-intersection-in-cplusplus/
sf::Vector2f getIntersection(sf::Vector2f p1A, sf::Vector2f p2A, sf::Vector2f p1B, sf::Vector2f p2B, bool& didItHappen){

    didItHappen=false;
  
    double determinant=(p1A.x-p2A.x)*(p1B.y-p2B.y)-(p1A.y-p2A.y)*(p1B.x-p2B.x);


    //does the point exist?
    if(determinant==0){
      return sf::Vector2f();
    }

  
    double pre=(p1A.x*p2A.y-p1A.y*p2A.x);
    double post=(p1B.x*p2B.y-p1B.y*p2B.x);
    double x=(pre*(p1B.x-p2B.x)-(p1A.x-p2A.x)*post)/determinant;
    double y=(pre*(p1B.y-p2B.y)-(p1A.y-p2A.y)*post)/determinant;

  
    //is the point on the 2 lines?
    if(x<std::min(p1A.x,p2A.x) || x>std::max(p1A.x,p2A.x) || x<std::min(p1B.x,p2B.x) || x>std::max(p1B.x,p2B.x))
      return sf::Vector2f();
    if(y<std::min(p1A.y,p2A.y) || y>std::max(p1A.y,p2A.y) || y<std::min(p1B.y,p2B.y) || y>std::max(p1B.y,p2B.y))
      return sf::Vector2f();


    didItHappen=true;
    return sf::Vector2f(x, y);
}
sf::Vector2f getIntersection(sf::Vector2f p1A, sf::Vector2f p2A, sf::Vector2f p1B, sf::Vector2f p2B){
  bool unused;
  return getIntersection(p1A, p2A, p1B, p2B, unused);
}




