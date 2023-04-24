/*
  Daren Kostov

  Licence GPLv3
  
  the MainClass logic



*/


#include "mainClass.h"
#include <iostream>
#include <fstream>



MainClass::MainClass(){

  pathToWorkingFile="";
  haveWeMadeAnyChanges=false;
}
MainClass::~MainClass(){
    std::cout << "Main class deleting\n";
  
    while(!nodes.empty()){
      std::cout << "Erasing node\n";
      nodes.erase(nodes.begin());
    }

    for(auto& row : links) {
      auto& linksRow=row.second;
      for(auto& link : linksRow) {

        if(link.second!=nullptr){//if statemtn not neccesery but fixes the amount of "Erasing link" messages
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
        a b c w
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
  std::fstream file;
  
  file.open(path, std::fstream::in | std::fstream::out | std::ios::trunc);
  
  if(!file.good()){
   std::cout << "bad file!\n";
   return 1;
  }
  std::cout << "good file\n";
  
  file << "# This is a sgdt file :/\n\n";


  //==NODES
  file << "# create [Id] [X coordinate] [Y coordinate] [Width] [Heigh] [Content]\n";

  for(auto node : nodes){
    file << "create " << node->getId();
    file << " " << node->getX();
    file << " " << node->getY();
    file << " " << node->getW();
    file << " " << node->getH();
    file << " " << node->getContent();
    file << "\n";
  }


  //==LINKS
  file << "\n# link [Start id] [End id]\n";

  for(auto& row : links) {
    auto& linksRow=row.second;
    auto x=row.first;
    for(auto& link : linksRow) {
      auto y=link.first;
      if(links[x][y]==nullptr) continue;

      file << "link " << x->getId();
      file << " " << y->getId();
      file << "\n";
    }
  }


  file.close();
  


  return 0;  

}

int MainClass::loadFromFile(std::string path){


  return 0;
}


