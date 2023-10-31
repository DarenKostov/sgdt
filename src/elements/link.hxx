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

#pragma once

#include "node.hxx"
#include <SFML/System/Vector2.hpp>


class Link{

  private:

    //the nodes the link is connecting
    std::pair<Node*, Node*> conectees;

    //the body and head of the link (its an arrow)
    sf::Vertex line[2];
    sf::Vertex arrow[3];

    //the text the link contains
    std::string label;

    //the color of the link
    sf::Color linkColor;

    //the color of the link label
    sf::Color textColor;

    //color of when the link is selected
    sf::Color selectColor;

    //color of when the link is highlighted
    sf::Color highlightColor;

    //color of when the link is hovered over
    sf::Color hoverColor;

    //gives you 2 pints that are closest to eachother but still at the edges of the nodes we are connecting
    std::pair<sf::Vector2i, sf::Vector2i> giveMePointsAtTheEdgesOfTheConectees();

  public:

    //how is the link drawn
    enum LinkStyle {continuous, dashed, dotted};

  private:
    LinkStyle linkStyle;

  public:
  
    //from node, to node, link style
    Link(Node*, Node*, LinkStyle=continuous);

    //deconstructor
    ~Link();

  //gives you the link label
  std::string getLabel();

  //gives you the drawing style of the link
  LinkStyle getStyle();

  
  //sets the label of the link
  void setLabel(std::string);
  
  //sets the style in which the link is drawn
  void setStyle(LinkStyle);

  //gives the nodes the link is connecting
  std::pair<Node*, Node*> getConectees();  

  //sets the nodes the link is connecting
  void setConectees(std::pair<Node*, Node*>);

  //updates the positioons of the arrow (link) vased on where the conectees are
  void updatePositions();



  //link color, label color, selected color, highlighed color, hovered color
  void setColors(sf::Color, sf::Color, sf::Color, sf::Color, sf::Color);

  //gives you the color of the link
  sf::Color getLinkColor();
  
  //sets the color of the link
  void setLinkColor(sf::Color);
  
  //sets the label color, pretty self explanatory :/
  void setTextColor(sf::Color);

  //sets the selected color, pretty self explanatory :/
  void setSelectedColor(sf::Color);

  //sets the highlighed color, pretty self explanatory :/
  void setHighlightedColor(sf::Color);

  //sets the hovered color, pretty self explanatory :/
  void setHoveredColor(sf::Color);

  //gets the label color, pretty self explanatory :/
  sf::Color getTextColor();

  //gets the selected color, pretty self explanatory :/
  sf::Color getSelectedColor();

  //gets the highlighed color, pretty self explanatory :/
  sf::Color getHighlightedColor();

  //gets the hovered color, pretty self explanatory :/
  sf::Color getHoveredColor();


  //draws the node, including its content
  void draw(sf::RenderWindow&);

  //draws the highlight of the text
  void drawHighlight(sf::RenderWindow&);

  //draws the select highlight
  void drawSelect(sf::RenderWindow&);

  //draws the hover highlight
  void drawHover(sf::RenderWindow&);

  
  
  
  
  
};



