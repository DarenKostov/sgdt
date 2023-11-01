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
    sf::Vector2f coordinates;
    sf::Vector2f dimensions;

    sf::Text content;
  
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
    
    int bodyThickness;
    int outerbodyThickness;
    
    void updateContentProperties();

  public:

    //modes in which to draw the node
    enum DrawingMode {normal, selected, highlighted, hovered};

  private:

    //the drawing mode of this particular node
    DrawingMode drawingMode;

  public:
    
    //font, coordinates, size, contents, outline color
    Node(sf::Font&, sf::Vector2f, sf::Vector2f=sf::Vector2f(100, 50), std::string="new text");

    //deconstructor
    ~Node();

    //sets the thickness of the main body outline
    void setBodyThickness(int);    
  
    //gets the thickness of the main body outline
    int getBodyThickness();    

    //sets the thickness of the outer body outline
    void setOuterBodyThickness(int);    
  
    //gets the thickness of the outer body outline
    int getOuterBodyThickness();    


    //sets the coordinates of the node (x and y)
    void setCoordinates(sf::Vector2f);

    //sets the dimensions of the node (width and height)
    void setDimensions(sf::Vector2f);

    //offsets the coordinates of the node (x and y)
    void move(sf::Vector2f);

    //resizes the dimensions of the node (width and height)
    void resize(sf::Vector2f);

    //gets the coordinates of the node (x and y)
    sf::Vector2f getCoordinates();

    //gets the dimensions of the node (width and height)
    sf::Vector2f getDimensions();

  
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

    //changes the drawing mode of the node
    void changeDrawingMode(DrawingMode);

    //gives you the drawing mode of the node
    DrawingMode getDrawingMode();
  
    //tels you if the coordinates (with 1x1 size) collide with the node
    bool collidingWithCoords(sf::Vector2f);

    //draws the node, including its content
    void draw(sf::RenderWindow&);

};



