/*
  Daren Kostov

  Licence: GPLv3

  method definitions for the node class
    
*/

#include "node.h"
#include <iostream>


Node::Node(int x, int y, int w, int h){
  XCoordinate=x;
  YCoordinate=y;
  Width=w;
  Height=h;
  content="*New Text*";

}

Node::~Node(){
  std::cout << "deleting node\n";
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
}
void Node::setY(int in){
  YCoordinate=in;
}
void Node::setW(int in){
  Width=in;
}
void Node::setH(int in){
  Height=in;
}

void Node::move(int dx, int dy){
  XCoordinate+=dx;
  YCoordinate+=dy;
}



std::string Node::getContent(){

  
  return content;
}
void Node::setContent(std::string in){

  //if its the default value, erase it
  if(content=="*New Text*"){
    content="";
    return;
  }

  content=in;

}


bool Node::collidingWithCoords(int x, int y){
  
  if(x>XCoordinate && x<XCoordinate+Width)//we are on the same X level
    if(y>YCoordinate && y<YCoordinate+Height)//we are on the same Y level
      return true;
  return false;
}


