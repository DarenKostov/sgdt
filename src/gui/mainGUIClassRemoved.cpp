/*
  Daren Kostov

  Licence GPLv3
  
  the MainGUIClass logic



*/


#include "mainGUIClass.h"
#include <iostream>



MainGUIClass::MainGUIClass(){
}
MainGUIClass::~MainGUIClass(){
}



void MainGUIClass::startProgram(){
  std::cout << "GUI mode was not compiled, please use the --cli (or -c) flag\n";
  
}

void MainGUIClass::removeNode(Node*){}

void MainGUIClass::manageSelection(float, float){}

void MainGUIClass::manageSelection(){}

void MainGUIClass::editContentOfNode(uint32_t){}
void MainGUIClass::stopEditContentOfNode(){}
void MainGUIClass::startEditContentOfNode(){}

