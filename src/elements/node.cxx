/*
Copyright (c) 2023 Daren Kostov

This file is part of SGDT

SGDT is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

SGDT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SGDT
If not, see <https://www.gnu.org/licenses/>.
*/

#include "node.hxx"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

Node::Node(sf::Font& font, sf::Vector2f location, sf::Vector2f size, std::string text){

  //set up drawing mode
  changeDrawingMode(normal);
  
  //set up thicknesses
  setBodyThickness(2);
  setOuterBodyThickness(6);
  
  //==set up up coordinates and sizes and stuff
  body=sf::RectangleShape();
  outerBody=sf::RectangleShape();
  setCoordinates(location);
  setDimensions(size);

  //==set up the content
  content.setFont(font);
  content.setString(text);
  content.setCharacterSize(15);
  content.setFillColor(textColor);
  updateContentProperties();

  //==init colors
  setColors(
    sf::Color::Black,
    sf::Color::White,
    sf::Color::White,
    sf::Color(255, 162, 0, 255),
    sf::Color(255, 66, 0, 255),
    sf::Color(0, 162, 255, 255)
  );



  //set id
  id=objectCount;
  objectCount++;
}

Node::~Node(){
  //do nothing for now
}

void Node::updateContentProperties(){
  //center the origin of the text
  auto properties=content.getLocalBounds();
  content.setOrigin(properties.left+properties.width/2.0f, properties.top+properties.height/2.0f);

  //center the text on the box
  sf::Vector2f newPosition=coordinates+(dimensions/2.0f);
  content.setPosition(newPosition);

}

void Node::setCoordinates(sf::Vector2f newCoordinates){
  coordinates=newCoordinates;
  body.setPosition(newCoordinates);

  //offset the outer body by the outline thickness of the main body
  outerBody.setPosition(newCoordinates+sf::Vector2f(bodyThickness, bodyThickness));

  updateContentProperties();
}




void Node::setDimensions(sf::Vector2f newDimensions){
  dimensions=newDimensions;
  body.setSize(newDimensions);

  //offset the outer body size by the outline thickness of the main body
  outerBody.setSize(newDimensions-sf::Vector2f(bodyThickness*2, bodyThickness*2));

  //update the positions
  setCoordinates(coordinates);

  updateContentProperties();
}


void Node::move(sf::Vector2f deltaCoordinates){
  body.move(deltaCoordinates);
  outerBody.move(deltaCoordinates);
  coordinates+=deltaCoordinates;
  updateContentProperties();
}

void Node::resize(sf::Vector2f deltaSizes){

  setDimensions(dimensions+deltaSizes);  
}

sf::Vector2f Node::getCoordinates(){
  return coordinates;
}

sf::Vector2f Node::getDimensions(){
  return dimensions;
}





void Node::setBodyThickness(int in){
  bodyThickness=in;

  //update the positions
  setCoordinates(coordinates);
}

void Node::setOuterBodyThickness(int in){
  outerBodyThickness=in;

  //update the positions
  setCoordinates(coordinates);
}

int Node::getBodyThickness(){
  return bodyThickness;
}

int Node::getOuterBodyThickness(){    
  return outerBodyThickness;
}



//==handle colors

void Node::setColors(sf::Color fill, sf::Color outline, sf::Color text, sf::Color selected, sf::Color highlight, sf::Color hover){

  fillColor=fill;
  outlineColor=outline;
  textColor=text;

  selectColor=selected;
  highlightColor=highlight;
  hoverColor=hover;
  
  //update the color of the main body
  body.setFillColor(fillColor);
  body.setOutlineColor(outlineColor);
  content.setFillColor(textColor);
  
  //update the color of the outline body
  changeDrawingMode(drawingMode);
}


void Node::setFillColor(sf::Color fill){
  fillColor=fill;
  body.setFillColor(fillColor);
}

void Node::setOutlineColor(sf::Color outline){
  outlineColor=outline;
  body.setOutlineColor(outlineColor);
}

void Node::setTextColor(sf::Color text){
  textColor=text;
  content.setFillColor(textColor);
}

void Node::setSelectedColor(sf::Color selected){
  selectColor=selected;
  changeDrawingMode(drawingMode);
}

void Node::setHighlightedColor(sf::Color highlight){
  highlightColor=highlight;
  changeDrawingMode(drawingMode);
}

void Node::setHoveredColor(sf::Color hover){
  hoverColor=hover;
  changeDrawingMode(drawingMode);
}



sf::Color Node::getFillColor(){
  return fillColor;
}

sf::Color Node::getOutlineColor(){
  return outlineColor;
}

sf::Color Node::getTextColor(){
  return textColor;
}

sf::Color Node::getSelectedColor(){
  return selectColor;
}

sf::Color Node::getHighlightedColor(){
  return highlightColor;
}

sf::Color Node::getHoveredColor(){
  return hoverColor;
}


std::string Node::getContent(){
  return content.getString();
}

void Node::setContent(std::string newText){
  content.setString(newText);
  updateContentProperties();
}


void Node::changeDrawingMode(Node::DrawingMode mode){
  drawingMode=mode;

  switch(mode){
    case normal:
      outerBody.setFillColor(sf::Color::Transparent);
      break;
    case selected:
      outerBody.setFillColor(selectColor);
      break;
    case highlighted:
      outerBody.setFillColor(highlightColor);
      break;
    case hovered:
      outerBody.setFillColor(hoverColor);
      break;
    default:
      // do nothng
      break;
  }
  
}






