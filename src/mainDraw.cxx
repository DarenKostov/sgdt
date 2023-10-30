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

#include "mainClass.hxx"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

void MainClass::draw(){

  window.clear();
  window.setView(mainView);
  
  sf::RectangleShape rect(sf::Vector2f(30, 30));
  rect.setFillColor(sf::Color(255, 255, 255, 255));
  rect.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window), mainView));
  window.draw(rect);

  window.display();
  
}
