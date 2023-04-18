/*
  Daren Kostov

  Licence GPLv3
  
  the MainCLIClass logic



*/


#include "mainCLIClass.h"
#include <iostream>



MainCLIClass::MainCLIClass(){
  editingText=false;
}
MainCLIClass::~MainCLIClass(){
  
  while(!nodes.empty()){
    std::cout << "Erasing\n";
    nodes.erase(nodes.begin());
  }
  
}



void MainCLIClass::startProgram(){
}