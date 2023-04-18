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
      std::cout << "Erasing\n";
      nodes.erase(nodes.begin());
    }
}

void MainClass::startProgram(){

  std::cout << "Something has gone horribly wrong\n"; 
}
