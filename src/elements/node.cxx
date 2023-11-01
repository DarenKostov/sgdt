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

Node::Node(sf::Font& font, sf::Vector2i location, sf::Vector2i size, std::string text){

  //==init colors
  fillColor=sf::Color::Black;
  outlineColor=sf::Color::White;
  textColor=sf::Color::White;

  selectColor=sf::Color(255, 162, 0, 255);
  highlightColor=sf::Color(255, 66, 0, 255);
  hoverColor=sf::Color(0, 162, 255, 255);

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

  //set id
  id=objectCount;
  objectCount++;
}

Node::~Node(){
  //do nothing for now
}

void Node::setCoordinates(sf::Vector2i newCoordinates){
  coordinates=newCoordinates;
  body.setPosition(static_cast<sf::Vector2f>(newCoordinates));

  //offset the outer body by the outline thickness of the main body
  outerBody.setPosition(static_cast<sf::Vector2f>(newCoordinates+sf::Vector2i(bodyThickness, bodyThickness)));

  updateContentProperties();

}

void Node::updateContentProperties(){
  //center the origin of the text
  auto properties=content.getLocalBounds();
  content.setOrigin(properties.left+properties.width/2.0f, properties.top+properties.height/2.0f);

  //center the text on the box
  sf::Vector2i newPosition=coordinates+(dimensions/2);
  content.setPosition(static_cast<sf::Vector2f>(newPosition));

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






