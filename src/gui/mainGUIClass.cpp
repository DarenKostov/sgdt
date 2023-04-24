/*
  Daren Kostov

  Licence GPLv3
  
  the MainGUIClass logic



*/


#include "mainGUIClass.h"
#include <iostream>
#include <cmath>
#include "../structures/box.h"
#include "../structures/connector.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


//tells you wether or not a point (5 px diameter circle) intercects with a line, provide the point first the  the 2 points that make up the line
bool doesItIntersect(sf::Vector2f, sf::Vector2f, sf::Vector2f);

//check if 2 lines intersect
bool doesItIntersect(sf::Vector2f, sf::Vector2f, sf::Vector2f, sf::Vector2f);



MainGUIClass::MainGUIClass(){
  editingText=false;
  cuttingLinks=false;
  terminalMode=false;

  selectedMainNode=nullptr;
  HoveredNode=nullptr;

  pathToWorkingFile="";

  int mapX=12;  int mapY=12;

  //create the window
  window.create(sf::VideoMode(mapX, mapY), "sgdt- Simple Graphing/Diagramming Tool");

  mapView=sf::View(sf::FloatRect(0, 0, mapX, mapY));
  UIView=sf::View(sf::FloatRect(0, 0, mapX, mapY));

  //set ratios
  mapView.setViewport(sf::FloatRect(0, 0, 1, 1));
  UIView.setViewport(sf::FloatRect(0, 0, 1, 1));
  
  window.setView(mapView);


  //load font
  if(!TheFontWeAreUsing.loadFromFile("fonts/UbuntuMono-Regular.ttf"))
    std::cout << "fornt error\n";

  //how much have we zoomed (default is 1, aka we havent zoomed at all)
  ZoomFactor=1;

  //notification stuff
  notification.setCharacterSize(15);
  notification.setFont(TheFontWeAreUsing);
  notification.setFillColor(sf::Color::White);
  notification.setString("Program started!");
  
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



  //stats setup
  sf::Text stats;
  stats.setCharacterSize(10);
  stats.setFont(TheFontWeAreUsing);
  stats.setFillColor(sf::Color::White);
  stats.setPosition(1, 100);



  while(window.isOpen()){
    window.clear();



    if(terminalMode==true){
      performTerminalActions();
    }else{
      performUIAction();
    }
      
    

    window.setView(mapView);

    
    //==DRAW HIGHLIGHTS
    for(auto selectedNode : selectedNodes){
      if(selectedMainNode!=selectedNode && selectedNode!=HoveredNode)
        static_cast<Box*>(selectedNode)->drawHighlight(window);
    }
    
    if(nullptr!=HoveredNode)
      static_cast<Box*>(HoveredNode)->drawHovered(window);
    //the main selected node takes precedence
    if(selectedMainNode!=nullptr)
      static_cast<Box*>(selectedMainNode)->drawSelected(window);
    



    //==DRAW ACTUAL BODIES
    for(auto node : nodes){
      static_cast<Box*>(node)->draw(window);
    }

    //==DRAW LINKS
    for(auto& row : links) {
      auto& linksRow=row.second;
      auto x=row.first;
      for(auto& link : linksRow) {
        auto y=link.first;

        if(links[x][y]==nullptr) continue;
          static_cast<Connector*>(links[x][y])->draw(window);
       
      }
    }    


    // if()
    
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

void MainGUIClass::performTerminalActions(){

  sf::Event event;
  bool breakEventWhile=false;
  while (window.pollEvent(event)){
      switch(event.type){
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::Resized:
          //if screen is resized mix the views dimensions
          {
            int windowWidth=event.size.width;
            int windowHeight=event.size.height;
            mapView.reset(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
            UIView.reset(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
          }
          break;
        case sf::Event::KeyPressed:
          if(event.key.code==sf::Keyboard::Up){
            terminal.setHistoryCopy(terminal.getHistoryCopy()+1);

          }else if(event.key.code==sf::Keyboard::Down){
            terminal.setHistoryCopy(terminal.getHistoryCopy()-1);
          }

          break;
        case sf::Event::TextEntered:
          performTerminalModeInput(event.text.unicode);
          break;
    }

    if(breakEventWhile==true)
      break;
    
  }

  //=draw the current command
  sf::Text terminalText;

  int charSize=15;
  int textHeight=UIView.getCenter().y+UIView.getSize().y/2-charSize-5;
    
  terminalText.setCharacterSize(charSize);
  terminalText.setFont(TheFontWeAreUsing);
  terminalText.setFillColor(sf::Color::White);
  terminalText.setPosition(UIView.getCenter().x-UIView.getSize().x/2, textHeight);

  std::string terminalString=":";

  {
    auto command=terminal.returnCurrentCommand();

    for(auto argument : command){
      terminalString+=argument;
      terminalString+=" ";
    }
  }
  terminalString.pop_back();
  
  sf::Time time=clock.getElapsedTime();


  if(time.asSeconds()<0.5){
    terminalString+="|";
  }else if(time.asSeconds()>1){
      clock.restart();
  }

  terminalText.setString(terminalString);
  
  window.setView(UIView);
  
  window.draw(terminalText);

  //=draw the history
  int i=0;
  for(auto command : terminal.returnCommandHistory()){
    terminalString="";
    
    if(i==terminal.getHistoryCopy())
      terminalText.setFillColor(sf::Color::Red);
    else
      terminalText.setFillColor(sf::Color::White);
      
      
    for(auto argument : command){
      terminalString+=argument;
      terminalString+=" ";
    }
    textHeight-=(charSize+5);
    terminalText.setPosition(UIView.getCenter().x-UIView.getSize().x/2, textHeight);
    terminalText.setString(terminalString);
    window.draw(terminalText);
    i++;
  }
  


}

void MainGUIClass::performTerminalModeInput(uint32_t in){

  //the ESC key or 27 ascii | we are haulting the terminal here, exiting it without performing anything
  if(in=='\x1b'){
    terminalMode=false;
    terminal.haultCommand();
    return;
  }

  //newline or carriage return | we are done with the command and performing an action
  if(in=='\r' || in=='\n'){
    terminalMode=false;
    terminal.endCommand();
    performTerminalModeOutput();
    return;
  }

  clock.restart();
  
  terminal.addCharacterToCurrentCommmand(in);


}

void MainGUIClass::performTerminalModeOutput(){

  std::string a;
  // a.cc
  std::vector<std::string> command=terminal.returnCommandHistory()[0];




  //==WRITING
  if(command[0]=="w"){
    /*
      0- success
      1- failuare
      2- where file? (file is unspecified)
    */
    int returnCode=9999;

    
    if(command.size()!=1){
      pathToWorkingFile=command[1];
    }
      
    if(pathToWorkingFile==""){
      returnCode=2;
    }else{
      returnCode=saveToFile(pathToWorkingFile);
    }

    switch(returnCode){
      case 0:
        startNotification("File saved to "+pathToWorkingFile+".");
        break;
      case 1:
        startNotification("An error occured, try again.");
        break;
      case 2:
        startNotification("Unspecified file.");
        break;
    }
    return;
  }

  //==QUIT
  if(command[0]=="q"){
    std::cout << (haveWeMadeAnyChanges? "True" : "False") << "\n";
    if(haveWeMadeAnyChanges==true){
        startNotification("You have unsaved data. Run :q! to force quit.");
        return;
    }
    window.close();
    return;
  }

  if(command[0]=="q!"){
    window.close();
    return;
  }


  //==WRITE-QUIT
  if(command[0]=="wq"){
    /*
      0- success
      1- failuare
      2- where file? (file is unspecified)
    */
    int returnCode=9999;

    
    if(command.size()!=1){
      pathToWorkingFile=command[1];
    }
      
    if(pathToWorkingFile==""){
      returnCode=2;
    }else{
      returnCode=saveToFile(pathToWorkingFile);
    }

    switch(returnCode){
      case 0:
        startNotification("File saved to "+pathToWorkingFile+".");
        window.close();
        break;
      case 1:
        startNotification("An error occured, try again.");
        break;
      case 2:
        startNotification("Unspecified file.");
        break;
    }
    return;
  }


  //==WRITE-QUIT (but better)
  if(command[0]=="x"){

    if(haveWeMadeAnyChanges==false){
      window.close();
      return;
    }
    
    /*
      0- success
      1- failuare
      2- where file? (file is unspecified)
    */
    int returnCode=9999;
    
    if(command.size()!=1){
      pathToWorkingFile=command[1];
    }
      
    if(pathToWorkingFile==""){
      returnCode=2;
    }else{
      returnCode=saveToFile(pathToWorkingFile);
    }

    switch(returnCode){
      case 0:
        startNotification("File saved to "+pathToWorkingFile+".");
        window.close();
        break;
      case 1:
        startNotification("An error occured, try again.");
        break;
      case 2:
        startNotification("Unspecified file.");
        break;
    }
    return;
  }



  startNotification("Unknown command \""+command[0]+"\".");
  
  return;
}


void MainGUIClass::performUIAction(){

  sf::Event event;
  while(window.pollEvent(event)){

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
          }else{
            if(event.text.unicode==':'){
              terminalMode=true;
              terminal.startCommand();
              return;
            }
          
          }
          break;
        
    
    
        case sf::Event::KeyReleased:
      
          //we are diting text, dont take keys as command input
          if(editingText==true)
            break;

          if(event.key.code==sf::Keyboard::A && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
            sf::Vector2f pos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);
            addNode(new Box((int)pos.x-50, (int)pos.y-25, 100, 50, TheFontWeAreUsing));
          }else if(event.key.code==sf::Keyboard::D || event.key.code==sf::Keyboard::Delete || event.key.code==sf::Keyboard::Backspace){

            while(!selectedNodes.empty())
              removeNode(*selectedNodes.begin());
        
            // for(auto node : selectedNodes)
            //   removeNode(node);
         
      
          }
      
          break;
        case sf::Event::MouseButtonPressed:

          {
            sf::Vector2f mousePos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);

            //=Manage the selection
            if(event.mouseButton.button==sf::Mouse::Left){
              manageSelection(mousePos);
            }
      
            if(event.mouseButton.button==sf::Mouse::Right){
              selectedMainNode=hoveringOver(mousePos);
            
              if(selectedMainNode==nullptr){
                //cutting links
                cuttingLinks=true;
              }else{
                //creating links
                cuttingLinks=false;
                selectedNodes.insert(selectedMainNode);
              }
          
            }
          }
                              
          break;
        case sf::Event::MouseButtonReleased:

          if(event.mouseButton.button==sf::Mouse::Right){

            cuttingLinks=false;
        
            sf::Vector2f mousePos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);

            auto connectTo=hoveringOverNotSelectedMain(mousePos);

            //we actually have nodes to connect right?
            if(connectTo==nullptr) break;
            if(selectedMainNode==nullptr) break;

        
            addLink(selectedMainNode, connectTo, new Connector(static_cast<Box*>(selectedMainNode), static_cast<Box*>(connectTo)));
            selectedMainNode=nullptr;  
          }


        
          break;
        case sf::Event::Resized:
          //if screen is resized mix the views dimensions
          {
            int windowWidth=event.size.width;
            int windowHeight=event.size.height;
            mapView.reset(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
            UIView.reset(sf::FloatRect(0.f, 0.f, windowWidth, windowHeight));
          }
      
          break;
        case sf::Event::MouseMoved:

      
          static sf::Vector2f oldMousePos=sf::Vector2f(0, 0);
          static sf::Vector2f oldMapViewCenter=sf::Vector2f(0, 0);

        
          sf::Vector2f currentMousePos=window.mapPixelToCoords(sf::Mouse::getPosition(window), mapView);

          //==PAN THE VIEW
          if(sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
            sf::Vector2f newCenter=-(currentMousePos-oldMousePos)+oldMapViewCenter;

            sf::Vector2i tmpMousePos=window.mapCoordsToPixel(oldMousePos, mapView);
            mapView.setCenter(newCenter);
            oldMousePos=window.mapPixelToCoords(tmpMousePos, mapView);
        
        
            break;
          }

          //==MOVE BOXES
          if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
          
            for(auto selectedNode : selectedNodes){

              int newX=currentMousePos.x-oldMousePos.x+static_cast<Box*>(selectedNode)->prevXCoordinate;
              int newY=currentMousePos.y-oldMousePos.y+static_cast<Box*>(selectedNode)->prevYCoordinate;
            
              selectedNode->setX(newX);
              selectedNode->setY(newY);

              //update the link positions
              for(auto node : nodes){
                haveWeMadeAnyChanges=true;
                //the links actually exist right? if so update them
                if(links[selectedNode][node]!=nullptr)
                  static_cast<Connector*>(links[selectedNode][node])->updatePositions();
                if(links[node][selectedNode]!=nullptr)
                  static_cast<Connector*>(links[node][selectedNode])->updatePositions();
              }

          
            }

            break;
          }


          //==CUT LINKS
          if(cuttingLinks==true){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){

              window.setView(mapView);
              sf::Vertex line[2];

              float x, y;
              sf::Vector2f difference=oldMousePos-currentMousePos;
          
              line[0]=sf::Vertex(oldMousePos+difference);
              line[1]=sf::Vertex(currentMousePos-difference);
          
          
              window.draw(line, 2, sf::Lines);
              // window.display();

              for(auto& row : links) {
                auto& linksRow=row.second;
                auto x=row.first;
                for(auto& link : linksRow) {
                  auto y=link.first;

                  if(links[x][y]==nullptr)
                    continue;

                  //do we slash the link in 2?
                  if(doesItIntersect(currentMousePos, oldMousePos, static_cast<Connector*>(links[x][y])->getStart(), static_cast<Connector*>(links[x][y])->getEnd())){
                    haveWeMadeAnyChanges=true;
    
                    std::cout << "Cutting Link!\n" << std::flush;
                    delete links[x][y];
                    links[x][y]=nullptr;
                    break;
                  }

                }
              }
            }
          //==WE ARE ABOUT TO MAKE A LINK
          }else{


            //main selected excluded beacuse thats how the single selection works as well as node linking
            HoveredNode=hoveringOverNotSelectedMain(currentMousePos);
          }


      
          //==RESIZE BOXES
          if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){

            //we have a main node selected and we are in editing mode, right?
            if(!(selectedMainNode==nullptr || editingText==false)){;
              haveWeMadeAnyChanges=true;
            
              int newWidth=currentMousePos.x-selectedMainNode->getX();
              int newHeight=currentMousePos.y-selectedMainNode->getY();

              selectedMainNode->setW(newWidth);
              selectedMainNode->setH(newHeight);

              //update the link positions
              for(auto node : nodes){
                //the links actually exist right? if so update them
                if(links[selectedMainNode][node]!=nullptr)
                  static_cast<Connector*>(links[selectedMainNode][node])->updatePositions();
                if(links[node][selectedMainNode]!=nullptr)
                  static_cast<Connector*>(links[node][selectedMainNode])->updatePositions();
              }
            }
          }


          //update old positions
      
          oldMousePos=currentMousePos;
          oldMapViewCenter=mapView.getCenter();
          for(auto node : nodes){
            static_cast<Box*>(node)->updatePreviousCoordinates();
          }

      

                   
        break;
      }
  }

  //update and draw notification at position
  if(clock.getElapsedTime().asSeconds()<2){
    notification.setPosition(UIView.getCenter().x-UIView.getSize().x/2, UIView.getCenter().y+UIView.getSize().y/2-20);
    window.setView(UIView);
    window.draw(notification);
  }


}



void MainGUIClass::manageSelection(sf::Vector2f mousePos){


  //the node we will be working with
  auto node=hoveringOver(mousePos);


  
  //=SELECTION ADDITION
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){

    //what are we selecting? if it doesnt exist return
    if(node==nullptr)
      return;

      
    if(selectedMainNode!=node)
      stopEditContentOfNode();
    
    selectedNodes.insert(static_cast<Box*>(node));
    selectedMainNode=static_cast<Box*>(node);

    std::cout << "selection addition\n";
    return;

  
  //=SELECTION REMOVAL
  }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){

    //what are we removing? if it doesnt exist return
    if(node==nullptr)
      return;
    
    if(selectedMainNode==node){
      stopEditContentOfNode();
      selectedMainNode=nullptr;
    }
      
    selectedNodes.erase(node);
    std::cout << "selection removal\n";
    return;
    

  //=SINGLE SELECTION
  }else{


    //clear selection if we did not click on a node
    if(node==nullptr){
      selectedNodes.clear();
      stopEditContentOfNode();
      selectedMainNode=nullptr;;
      return;
    }


    node=hoveringOverNotSelectedMain(mousePos);

    
    std::cout << "single selection\n";

    selectedNodes.clear();

    //we selected the selectedMainNode and there are no overlaps
    if(node==nullptr){
      selectedNodes.insert(selectedMainNode);
      return;
    }

    
    stopEditContentOfNode();



    
    selectedMainNode=node;
    selectedNodes.insert(node);
    
    // update the hovering accordingly
    HoveredNode=hoveringOverNotSelectedMain(mousePos);
    
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

  if(in<128){
    //remove the ">"
    std::string content=selectedMainNode->getContent();
    if(content.size()!=0)
      content=content.substr(1, content.size());

    //if newline or any other "newlines"
    if(in=='\n' || in=='\r'){
      return;
    }
    
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

Node* MainGUIClass::hoveringOver(sf::Vector2f mousePos){
      for(auto node : nodes)
        if(node->collidingWithCoords(mousePos.x, mousePos.y))
          return node;

  return nullptr;
}
Node* MainGUIClass::hoveringOverSelected(sf::Vector2f mousePos){
      for(auto node : selectedNodes)
        if(node->collidingWithCoords(mousePos.x, mousePos.y))
          return node;

  return nullptr;
}
Node* MainGUIClass::hoveringOverNotSelectedMain(sf::Vector2f mousePos){
      for(auto node : nodes){
    
        //is it the main selected node? skip it if so
        if(node==selectedMainNode)
          continue;
    
        if(node->collidingWithCoords(mousePos.x, mousePos.y))
          return node;
      }

  return nullptr;
}
Node* MainGUIClass::hoveringOverNotSelected(sf::Vector2f mousePos){
      for(auto node : nodes){

        //is it selected? skip it if so
        if(selectedNodes.find(node)!=selectedNodes.end())
          continue;
    
        if(node->collidingWithCoords(mousePos.x, mousePos.y))
          return node;
      }

  return nullptr;
}

bool doesItIntersect(sf::Vector2f pointA, sf::Vector2f line1, sf::Vector2f line2){
//                                p1B-p2B               p1A                 p2A                
  

  
  //shift the cordinate system of the line to the 0, 0 of the point
  line1-=pointA;
  line2-=pointA;

  //get m
  float m=(line1.y-line2.y)/(line1.x-line2.x);

  //find b
  float b=-(m*line1.x-line1.y);

  //get perpendicular m
  float mPerpendicular=-1/m;

  //find perpendicular b, (0, 0) is the center of the circle btw! no need for "+pointA.x-pointA.y"
  float bPerpendicular=-mPerpendicular;


  //find the iterception point between the perpendicular and original line

  //some values for convenience    
  float a1=m;
  float b1=-1;
  float c1=b;

  float a2=mPerpendicular;
  float b2=-1;
  float c2=bPerpendicular;

  float x, y;

  //some complex math
  x=(b1*c2-b2*c1)/(a1*b2-a2*b1);
  y=(a2*c1-a1*c2)/(a1*b2-a2*b1);

  line1+=pointA;
  line2+=pointA;


  sf::Vector2f pointB(x, y);

  pointB+=pointA;

  // is the point on the line at all? (this is a line segment)
  if(pointB.x<std::min(line1.x,line2.x) || pointB.x>std::max(line1.x,line2.x) || pointB.y<std::min(line1.y,line2.y) || pointB.y>std::max(line1.y,line2.y))
    return false;

    
  //find distance between intercection and our point
  float distance=sqrt(pow(pointA.x-pointB.x, 2)+pow(pointA.y-pointB.y, 2));

  
  if(distance>5)
    return false;

  return true;

}

// https://flassari.is/2008/11/line-line-intersection-in-cplusplus/
bool doesItIntersect(sf::Vector2f pointA1, sf::Vector2f pointA2, sf::Vector2f pointB1, sf::Vector2f pointB2){

    double determinant=(pointA1.x-pointA2.x)*(pointB1.y-pointB2.y)-(pointA1.y-pointA2.y)*(pointB1.x-pointB2.x);


    //does the point exist?
    if(determinant==0){
      return false;
    }

  
    double pre=(pointA1.x*pointA2.y-pointA1.y*pointA2.x);
    double post=(pointB1.x*pointB2.y-pointB1.y*pointB2.x);
    double x=(pre*(pointB1.x-pointB2.x)-(pointA1.x-pointA2.x)*post)/determinant;
    double y=(pre*(pointB1.y-pointB2.y)-(pointA1.y-pointA2.y)*post)/determinant;

  
    //is the point within the ends of each line?
    if(x<std::min(pointA1.x,pointA2.x) || x>std::max(pointA1.x,pointA2.x) || x<std::min(pointB1.x,pointB2.x) || x>std::max(pointB1.x,pointB2.x))
      return false;
    if(y<std::min(pointA1.y,pointA2.y) || y>std::max(pointA1.y,pointA2.y) || y<std::min(pointB1.y,pointB2.y) || y>std::max(pointB1.y,pointB2.y))
      return false;

    return true;

}

void MainGUIClass::startNotification(std::string in){
  notification.setString(in);
  clock.restart();
  // notification.setPosition(UIView.getCenter().x-UIView.getSize().x/2, UIView.getCenter().y+UIView.getSize().y/2-20);
}
