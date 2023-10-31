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

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Node{
  private:
    sf::Vector2i coordinates;
    sf::Vector2i dimensions;

    std::string content;
  
    sf::Color fillColor;
    sf::Color outlineColor;
    sf::Color textColor;
  
    sf::Color selectColor;
    sf::Color highlightColor;
    sf::Color hoverColor;
    
    uint id;
    // https://stackoverflow.com/questions/5019856/initialize-static-variables-in-c-class
    static inline uint objectCount=0;


    //variables for drawing purposes
    sf::RectangleShape body;
    sf::RectangleShape outerBody;


  public:
  
    //font, coordinates, size, contents, outline color
    Node(sf::Font&, sf::Vector2i, sf::Vector2i=sf::Vector2i(100, 50), std::string="new text");

    //deconstructor
    ~Node();


    //sets the coordinates of the node (x and y)
    void setCoordinates(sf::Vector2i);

    //sets the dimensions of the node (width and height)
    void setDimensions(sf::Vector2i);

    //offsets the coordinates of the node (x and y)
    void move(sf::Vector2i);

    //resizes the dimensions of the node (width and height)
    void resize(sf::Vector2i);

    //gets the coordinates of the node (x and y)
    sf::Vector2i setCoordinates();

    //gets the dimensions of the node (width and height)
    sf::Vector2i setDimensions();

  
    //fill color, outline color, text color, selected color, highlighed color, hovered color
    void setColors(sf::Color, sf::Color, sf::Color, sf::Color, sf::Color, sf::Color);
    
    //sets the fill color, pretty self explanatory :/
    void setFillColor(sf::Color);
  
    //sets the outline color, pretty self explanatory :/
    void setOutlineColor(sf::Color);
  
    //sets the text color, pretty self explanatory :/
    void setTextColor(sf::Color);
  
    //sets the selected color, pretty self explanatory :/
    void setSelectedColor(sf::Color);
  
    //sets the highlighed color, pretty self explanatory :/
    void setHighlightedColor(sf::Color);
  
    //sets the hovered color, pretty self explanatory :/
    void setHoveredColor(sf::Color);
  
    //gets the fill color, pretty self explanatory :/
    sf::Color getFillColor();
  
    //gets the outline color, pretty self explanatory :/
    sf::Color getOutlineColor();
  
    //gets the text color, pretty self explanatory :/
    sf::Color getTextColor();
  
    //gets the selected color, pretty self explanatory :/
    sf::Color getSelectedColor();
  
    //gets the highlighed color, pretty self explanatory :/
    sf::Color getHighlightedColor();
  
    //gets the hovered color, pretty self explanatory :/
    sf::Color getHoveredColor();
  

    //gives you the text stored in the node
    std::string getContent();

    //modifies the text in the node
    void setContent(std::string);


    //tels you if the coordinates (with 1x1 size) collide with the node
    bool collidingWithCoords(sf::Vector2i);

    //draws the node, including its content
    void draw(sf::RenderWindow&);

    //draws the highlight of the text
    void drawHighlight(sf::RenderWindow&);

    //draws the select highlight
    void drawSelect(sf::RenderWindow&);

    //draws the hover highlight
    void drawHover(sf::RenderWindow&);

};



