/*
  Daren Kostov

  Licence GPLv3
  
  the MainClass logic



*/


#include "mainClass.h"
#include <iostream>



MainClass::MainClass(){
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
