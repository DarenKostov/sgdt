/*
  Daren Kostov

  Licence GPLv3
  
  the MainGUIClass logic



*/


#include "mainGUIClass.h"
#include <iostream>
#include "../structures/box.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>




MainGUIClass::MainGUIClass(){
  editingText=false;
}
MainGUIClass::~MainGUIClass(){
  std::cout << "GUI class deleting\n";

}
void MainGUIClass::removeNode(Node* in){
  if(in==nullptr) return;

  
  selectedNodes.erase(in);
  if(selectedMainNode==in)
    selectedMainNode=nullptr;

  MainClass::removeNode(in);
}



void MainGUIClass::startProgram(){

  int mapX=12;  int mapY=12;
  
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


  //stats setup
  sf::Text stats;
  stats.setCharacterSize(10);
  stats.setFont(ubuntuFont);
  stats.setFillColor(sf::Color::White);
  stats.setPosition(1, 100);



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

          case sf::Event::KeyPressed:
           
            //set up editing mode
            if(event.key.code==sf::Keyboard::Enter && selectedMainNode!=nullptr){
              if(editingText){
                stopEditContentOfNode();
              }else{
                startEditContentOfNode();            
              }
            }

            //we are diting text, dont take keys as command input
            if(editingText==true)
              break;

            
          
            manageSelection();

            break;







          case sf::Event::TextEntered:
            if(editingText==true){
              editContentOfNode(event.text.unicode);
              std::cout << "editing!!!\n";
            }
            break;
            
        
        
          case sf::Event::KeyReleased:
          
            //we are diting text, dont take keys as command input
            if(editingText==true)
              break;

            if(event.key.code==sf::Keyboard::A && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
              sf::Vector2f pos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
              addNode(new Box((int)pos.x-50, (int)pos.y-25, 100, 50, ubuntuFont));
            }else if(event.key.code==sf::Keyboard::D || event.key.code==sf::Keyboard::Delete || event.key.code==sf::Keyboard::Backspace){

              while(!selectedNodes.empty())
                removeNode(*selectedNodes.begin());
            
              // for(auto node : selectedNodes)
              //   removeNode(node);
             
          
            }
          
            break;
          case sf::Event::MouseButtonPressed:
          

            //=Manage the selection
            if(event.mouseButton.button==sf::Mouse::Left){
              sf::Vector2f mousePos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
            
            
              manageSelection(mousePos.x, mousePos.y);
              
            }
          
            if(event.mouseButton.button==sf::Mouse::Right){
              
            
              // sf::Vector2f mousePos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
            
            
              // manageSelection(mousePos.x, mousePos.y);
              
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
            static sf::Vector2f oldPos;
            static sf::Vector2f oldPosMapView;
            
            sf::Vector2f pos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
          

              sf::Vector2f newPos=-(pos-oldPos)+oldPosMapView;
              mapView.setCenter(newPos);
            }

            //move boxes
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
              
              // sf::Vector2i shift=oldPos-pos;
              for(auto selectedNode : selectedNodes){

                // selectedNode->move(shift.x*ZoomFactor, shift.y*ZoomFactor);
                int newX=pos.x-oldPos.x+static_cast<Box*>(selectedNode)->prevXCoordinate;
                int newY=pos.y-oldPos.y+static_cast<Box*>(selectedNode)->prevYCoordinate;
                
                selectedNode->setX(newX);
                selectedNode->setY(newY);
              }
            
            }else{

              oldPos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
              oldPosMapView=mapView.getCenter();
              for(auto node : nodes){
                static_cast<Box*>(node)->updatePreviousCoordinates();
              }
            }

          


            
            //resize a box
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
              if(selectedMainNode==nullptr) break;

            
              int newWidth=pos.x-selectedMainNode->getX();
              int newHeight=pos.y-selectedMainNode->getY();

              selectedMainNode->setW(newWidth);
              selectedMainNode->setH(newHeight);

            
            }
          break;
        }
    }

    window.clear();

    window.setView(mapView);
    //draw highlights
    for(auto selectedNode : selectedNodes){
      auto tmpNodeRecoloring=static_cast<Box*>(selectedNode)->getBody();      
      tmpNodeRecoloring.setFillColor(sf::Color(255, 66, 0, 100));

      //the main selected node has a different color
      if(selectedNode==selectedMainNode)
        tmpNodeRecoloring.setFillColor(sf::Color(255, 162, 0, 100));
      
      window.draw(tmpNodeRecoloring);
    }

    //draw actual bodies
    for(auto node : nodes){
      window.draw(static_cast<Box*>(node)->getBody());
      window.draw(static_cast<Box*>(node)->getContentText());
    }

    //draw ui
    window.setView(UIView);
    sf::Vector2i pos=sf::Mouse::getPosition(window);
    stats.setString(stats.getString()+std::to_string(pos.x)+" : "+std::to_string(pos.y)+"\n"
      );
    window.draw(stats);


    //display everything
    window.display();

    stats.setString("");


    
  }
            


}



void MainGUIClass::manageSelection(float mouseX, float mouseY){


  //the node we will be working with
  auto node=hoveringOver(mouseX, mouseY);


  //clear selection if we did not click on a node
  if(node==nullptr){
    selectedNodes.clear();
    stopEditContentOfNode();
    selectedMainNode=nullptr;;
    return;
  }
  
  //selection addition
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){


      
    if(selectedMainNode!=node)
      stopEditContentOfNode();
    
    selectedNodes.insert(static_cast<Box*>(node));
    selectedMainNode=static_cast<Box*>(node);

    std::cout << "selection addition\n";
    return;

  
  //selection removal
  }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){

    if(selectedMainNode==node){
      stopEditContentOfNode();
      selectedMainNode=nullptr;
    }
      
    selectedNodes.erase(node);
    std::cout << "selection removal\n";
    return;
    

  //single selection
  }else{

    selectedNodes.clear();

    
    if(selectedMainNode!=node)
      stopEditContentOfNode();
    
    selectedMainNode=node;
    selectedNodes.insert(node);
    std::cout << "single selection\n";
    return;
  }

  

  

}

void MainGUIClass::manageSelection(){
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    
    selectedNodes.clear();
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
      for(auto node : nodes){
        selectedNodes.insert(node);
      }
      
  }

}

void MainGUIClass::editContentOfNode(sf::Uint32 in){

  if (in<128){
    //remove the ">"
    std::string content=selectedMainNode->getContent();
    if(content.size()!=0)
      content=content.substr(1, content.size());

    if(in==8){//if backspace
      content=content.substr(0, content.size()-1);
    }else{
      content += static_cast<char>(in);
    }

    //add the ">"
    selectedMainNode->setContent(">"+content);
  }

}
void MainGUIClass::startEditContentOfNode(){
  if(editingText) return;
  
  std::cout << "starting to edit!\n";
  editingText=true;
  
  //add the ">" signalling we are editing
  std::string content=selectedMainNode->getContent();
  selectedMainNode->setContent(">"+content);
}
void MainGUIClass::stopEditContentOfNode(){
  if(!editingText) return;
  
  std::cout << "stopping to edit!\n";
  editingText=false;
  
  //remove the ">" signalling we are NOT editing
  std::string content=selectedMainNode->getContent();
  if(content.size()!=0)
    content=content.substr(1, content.size());
  selectedMainNode->setContent(content);
}

Node* MainGUIClass::hoveringOver(float mouseX, float mouseY){
      for(auto node : nodes)
        if(node->collidingWithCoords(mouseX, mouseY))
          return node;

  return nullptr;
}
