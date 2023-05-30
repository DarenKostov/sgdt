/*
  Daren Kostov

  Licence GPLv3
  
  the MainClass logic



*/


#include "mainClass.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>



MainClass::MainClass(){

  pathToWorkingFile="";
  haveWeMadeAnyChanges=false;
}
MainClass::~MainClass(){
  std::cout << "Main class deleting\n";
  
  eraseEverything();
  
}

void MainClass::eraseEverything(){
  
    while(!nodes.empty()){
      std::cout << "Erasing node\n";
      nodes.erase(nodes.begin());
    }

    for(auto& row : links) {
      auto& linksRow=row.second;
      for(auto& link : linksRow) {

        if(link.second!=nullptr){//if statement not neccesery but fixes the amount of "Erasing link" messages
          std::cout << "Erasing link\n";
          delete link.second;
        }

      }
      linksRow.clear();
    }
    links.clear();

}

void MainClass::startProgram(){
  std::cout << "Something has gone horribly wrong\n"; 
}


Node* MainClass::giveMeNewNode(){
  return new Node(0, 0, 0, 0);
}
Link* MainClass::giveMeNewLink(){
  return new Link();
}

  
void MainClass::addNode(Node* in){
  haveWeMadeAnyChanges=true;
  nodes.insert(in);

  /*add to the 2d table
  
    we are adding w
    - means nullptr
    = means any Link* or nullptr
    + means un-initialized or doesn't exist

    goal:
  
      a b c w
    a = = = -
    b = = = -
    c = = = -
    w - - - -
  
  */


  
  links[in]= std::unordered_map<Node*, Link*>();
  /*^^^^^^
      a b c
    a = = =
    b = = =
    c = = =
    w + + +
  */


  
  for(auto& row : links){
    links[in][row.first]=nullptr;
    /*^^^^^^
        // a b c w
      a = = = +
      b = = = +
      c = = = +
      w - - - -
    */
    links[row.first][in]=nullptr;
    /*^^^^^^
        a b c w
      a = = = -
      b = = = -
      c = = = -
      w + + + -
    */
    
  }

  
}

void MainClass::removeNode(Node* in){
  haveWeMadeAnyChanges=true;
  
  nodes.erase(in);


  //remove the links associated with this node
  
  //free the memory
  for(auto& row : links){
    delete links[in][row.first];
    delete links[row.first][in];
  }

  
  //remove on the Y axis
  for(auto& row : links){
    links[row.first].erase(in);
  }

  //remove on the X axis
  links.erase(in);
  
  delete in;
}

void MainClass::addLink(Node* from, Node* to, Link* in){
  haveWeMadeAnyChanges=true;
  
  //all of the inputs exist right?
  if(from==nullptr) return;
  if(to==nullptr) return;
  if(in==nullptr) return;

  //connect a node to itself?
  if(from==to) return;

  //we are not overwriting a link right?
  if(links[from][to]!=nullptr) return;

  
  std::cout << "creating link\n";
  
  links[from][to]=in;
  
}


int MainClass::saveToFile(std::string path){
  haveWeMadeAnyChanges=false;
  std::ofstream file;
  
  file.open(path, std::fstream::out | std::ios::trunc);
  
  if(!file.good()){
   std::cout << "bad file!\n";
   return 1;
  }
  std::cout << "good file\n";
  
  file << "# Simple Graphing File\n";
  file << "# This is a sgdt file :/\n";
  file << "# Don't edit, sgdt is not made to work with broken files\n\n";


  //==NODES
  file << "# create [Id] [X coordinate] [Y coordinate] [Width] [Heigh] [Color] [Content]\n";

  for(auto node : nodes){
    file << "create " << node->getId();
    file << " " << node->getX();
    file << " " << node->getY();
    file << " " << node->getW();
    file << " " << node->getH();
    file << " " << node->getColor();
    file << " " << node->getContent();
    file << "\n";
  }


  //==LINKS
  file << "\n# link [Start id] [End id] [Style]\n";

  for(auto& row : links) {
    auto& linksRow=row.second;
    auto x=row.first;
    for(auto& link : linksRow) {
      auto y=link.first;
      if(links[x][y]==nullptr) continue;

      file << "link " << x->getId();
      file << " " << y->getId();
      file << " " << (int)links[x][y]->getStyle();
      file << "\n";
    }
  }


  file.close();
  


  return 0;  

}

int MainClass::loadFromFile(std::string path){

  //make sure the file exists
  if(std::filesystem::exists(path)==false){
    return 2;
  }
  
  std::ifstream file;
  file.open(path, std::fstream::in);

  
  if(!file.good()){
   std::cout << "bad file!\n";
   return 1;
  }
  std::cout << "good file\n";

  pathToWorkingFile=path;
  
  eraseEverything();
    
  std::cout << "everything cleared\n";

  std::string currentLine="";
  
  while(getline(file, currentLine, '\n')){

    //ignore comments
    if(currentLine[0]=='#' || (currentLine.size()>1 && currentLine[0]=='/' && currentLine[1]=='/')){
      continue;
    }

    //get what comamnd it is
    std::stringstream ss(currentLine);
    std::string argument="";
    Node* newNode=giveMeNewNode();
      
    getline(ss, argument, ' ');

    if(argument=="create"){

      int x, y, height, width;
      long id;
      std::string content, color;
      
      getline(ss, argument, ' ');
      id=std::stol(argument);
      
      getline(ss, argument, ' ');
      x=std::stoi(argument);
      
      getline(ss, argument, ' ');
      y=std::stoi(argument);
      
      getline(ss, argument, ' ');
      width=std::stoi(argument);
      
      getline(ss, argument, ' ');
      height=std::stoi(argument);
      
      getline(ss, argument, ' ');
      color=argument;

      getline(ss, argument);
      content=argument;
      
      newNode->changeId(id);
      newNode->setX(x);
      newNode->setY(y);
      newNode->setW(width);
      newNode->setH(height);
      newNode->setColor(color);
      newNode->setContent(content);
      newNode->setContent(content);

      addNode(newNode);
      
    }else if(argument=="link"){

      long idStart, idEnd;
      Link* newLink;
      Node* startNode;
      Node* endNode;
      linkStyle style;
      
      getline(ss, argument, ' ');
      idStart=std::stol(argument);
      
      getline(ss, argument, ' ');
      idEnd=std::stol(argument);
      
      getline(ss, argument, ' ');
      style=(linkStyle)std::stoi(argument);


      //find the nodes by id
      for(auto node : nodes){
        if(node->getId()==idStart)
          startNode=node;
        else if(node->getId()==idEnd)
          endNode=node;
      }

      newLink=giveMeNewLink();
      newLink->setStyle(style);
      
      std::cout << "new link given!\n";
      addLink(startNode, endNode, newLink);
      std::cout << startNode->getContent() << " : " << endNode->getContent() << "\n";
  
      
    }
  
  }
  
  haveWeMadeAnyChanges=false;
  std::cout << "everything loaded\n";
  
  return 0;
}


