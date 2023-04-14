/*
  Daren Kostov

  Licence GPLv3
  
  the MainClass logic



*/


#include "mainClass.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


MainClass::MainClass(){
  
}
MainClass::~MainClass(){
}



void MainClass::startCLIProgram(){}
void MainClass::startGUIProgram(){

  int mapX=12;
  int mapY=12;
  
  sf::RenderWindow window(sf::VideoMode(mapX, mapY), "map");

  sf::View mapView(sf::FloatRect(0, 0, mapX, mapY));
  sf::View UIView(sf::FloatRect(0, 0, mapX, mapY));

  //set ratios
  mapView.setViewport(sf::FloatRect(0, 0, 1, 1));
  UIView.setViewport(sf::FloatRect(0, 0, 1, 1));
  
  window.setView(mapView);


  //load font
  sf::Font ubuntuFont;
  if(!ubuntuFont.loadFromFile("fonts/UbuntuMono-Regular.ttf"))
    std::cout << "fornt error\n";

  //how much have we zoomed
  double ZoomFactor=1;

  while (window.isOpen()){
    sf::Event event;


    
    while (window.pollEvent(event)){

        switch(event.type){
          case sf::Event::Closed:
            window.close();
            break;
       
          case sf::Event::MouseWheelMoved:
            //==ZOOM
            {
              double zoomAddition=1-1.0*event.mouseWheel.delta/10;
              ZoomFactor*=zoomAddition;
              mapView.zoom(zoomAddition);
            }
          
            break;
          case sf::Event::KeyReleased:
            // sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
            break;
          case sf::Event::MouseButtonReleased:
          
            if(event.mouseButton.button==sf::Mouse::Left){
              //take the mouse coords relative to the window and convert them to the window coords (with all the shifting and NOT scaling)
              sf::Vector2f pos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
              Node newNode(pos.x-50, pos.y-25, 100, 50);
              nodes.push_back(newNode);
            }
            
            break;
          case sf::Event::MouseButtonPressed:

            break;
          case sf::Event::Resized:

            {
              int windowWidth=event.size.width;
              int windowHeight=event.size.height;
              mapView.reset(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
              UIView.reset(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
            }
            break;
          case sf::Event::MouseMoved:
          //==PAN
            static sf::Vector2i oldPos;
            
            if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
          
              sf::Vector2i pos=sf::Mouse::getPosition(window);
              sf::Vector2i shift=oldPos-pos;
              mapView.move(shift.x*ZoomFactor, shift.y*ZoomFactor);
              oldPos=pos;
            }else{
          
              oldPos=sf::Mouse::getPosition(window);
            }

            

            
          break;
        }
    }

    window.clear();

    window.setView(mapView);
    for(auto node : nodes){
      window.draw(node.getBody());
    }


    window.setView(UIView);
    sf::Text stats;
    stats.setCharacterSize(10);
    stats.setFont(ubuntuFont);
    stats.setFillColor(sf::Color::White);
    stats.setPosition(1, 100);

    
    sf::Vector2i pos=sf::Mouse::getPosition(window);
    stats.setString(std::to_string(pos.x)+" : "+std::to_string(pos.y)+"\n"
      );
    window.draw(stats);

    
    window.display();

    // if(sf::Mouse::isButton(sf::Mouse::Middle)){

    
  }
            


}




