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

void MainClass::performActions(){
  sf::Event event;
  while (window.pollEvent(event)){
    switch(event.type){
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::Resized:
        //if screen is resized fix the views dimensions
        {
          int windowWidth=event.size.width;
          int windowHeight=event.size.height;
          mainView.reset(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
        }
        break;
      // case blah blah:
      // / break;
    }
    
  }

}
