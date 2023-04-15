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
  
  while(!nodes.empty()){
    std::cout << "Erasing\n";
    nodes.erase(nodes.begin());
  }
  
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
  bool editingText=false;

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
          case sf::Event::KeyPressed:

              
            manageSelection();

            
          
          
            break;
          case sf::Event::MouseButtonPressed:
          
            if(event.mouseButton.button==sf::Mouse::Right){
              //take the mouse coords relative to the window and convert them to the window coords (with all the shifting and NOT scaling)
              sf::Vector2f pos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
              nodes.insert(new Node((int)pos.x-50, (int)pos.y-25, 100, 50, ubuntuFont));
              break;
            }

            //=Manage the selection
            if(event.mouseButton.button==sf::Mouse::Left){
              sf::Vector2f mousePos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
              manageSelection(mousePos);
            }
                        
            break;
          case sf::Event::MouseButtonReleased:

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
    //draw highlights
    for(auto selectedNode : selectedNodes){
      auto tmpNodeRecoloring=selectedNode->getBody();      
      tmpNodeRecoloring.setFillColor(sf::Color(255, 66, 0, 100));

      //the main selected node has a different color
      if(selectedNode==selectedMainNode)
        tmpNodeRecoloring.setFillColor(sf::Color(255, 162, 0, 100));
      
      window.draw(tmpNodeRecoloring);
    }

    //draw actual bodies
    for(auto node : nodes){
      window.draw(node->getBody());
      window.draw(node->getContent());
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



void MainClass::manageSelection(sf::Vector2f mousePos){

  //selection addition
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){

    for(auto node : nodes){
      if(node->collidingWithCoords(mousePos.x, mousePos.y)){

        selectedNodes.insert(node);
        selectedMainNode=node;

        std::cout << "selection addition\n";
        return;
      }
    }

    //return anyway, we are adding with the LShift we dont want to have a chance to remove
    return;
  
  //selection removal
  }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){

    for(auto node=selectedNodes.begin(); node!=selectedNodes.end(); node++){
      if((*node)->collidingWithCoords(mousePos.x, mousePos.y)){
        if(selectedMainNode==*node)
          selectedMainNode=nullptr;
        
        selectedNodes.erase(node);
        std::cout << "selection removal\n";
        return;
      }
    }
    
    //return anyway, we are removing 1 with the LCtrl we dont want to have a chance to remove more than 1
    return;

  //single selection
  }else{

    for(auto node : nodes){
      if(node->collidingWithCoords(mousePos.x, mousePos.y)){
        selectedNodes.clear();
        selectedMainNode=node;
        selectedNodes.insert(node);
        std::cout << "single selection\n";
        return;
      }
    }
  }

  
  //clear selection
  selectedNodes.clear();
  selectedMainNode=nullptr;;

  

}

void MainClass::manageSelection(){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    
    selectedNodes.clear();
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
      for(auto node : nodes){
        selectedNodes.insert(node);
      }
      
  }

}

void editContentOfNode(Node&){




}

