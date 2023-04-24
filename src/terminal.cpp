/*
  Daren Kostov

  Licence: GPLv3


  The cpp file for the Terminal class

*/

#include "terminal.h"
#include <iostream>


Terminal::Terminal(){
  enteringCommand=false;
  currentArgument=0;
  currentHistoryCommandCopy=-1;
}
Terminal::~Terminal(){
  
}

void Terminal::startCommand(){
  if(enteringCommand==true) return;
  
  currentArgument=0;
  currentHistoryCommandCopy=-1;
  enteringCommand=true;
  currentCommand.push_back("");

}
void Terminal::endCommand(){
  if(enteringCommand==false) return;
  
  enteringCommand=false;
  history.insert(history.begin(), currentCommand);
  currentCommand.clear();
  currentArgument=0;
  currentHistoryCommandCopy=-1;
}


void Terminal::haultCommand(){  
  if(enteringCommand==false) return;
  
  enteringCommand=false;
  currentCommand.clear();
  currentArgument=0;
  currentHistoryCommandCopy=-1;

}

void Terminal::addCharacterToCurrentCommmand(char in){
  if(enteringCommand==false) return;


  //backspace?
  if(in=='\b'){
    //we can delete a char right?
    if(!currentCommand[currentArgument].empty()){
      currentCommand[currentArgument].pop_back();
    //we can delete an argument right?
    }else if(currentArgument!=0){
      currentArgument--;
      currentCommand.pop_back();
    //the current command is completly empty?
    }else{
      //do nothing
    }
    return;
  }

  //space?
  if(in==' '){
    
    //we inputted something right? we can start a new argument right?
    if(!currentCommand[currentArgument].empty()){
      currentArgument++;
      currentCommand.push_back("");
    //we havent inputted anything for this command?
    }else{
      //do nothing
    }
    return;
  }

  //any other character?
  currentCommand[currentArgument]+=in;
}


std::vector<std::string> Terminal::returnCurrentCommand(){
  return currentCommand;
}

std::vector<std::string> Terminal::returnCurrentCommandWithColor(){
  return currentCommand;
}

std::vector<std::vector<std::string>> Terminal::returnCommandHistory(){
  return history;
}

int Terminal::getHistoryCopy(){
  return currentHistoryCommandCopy;
}


void Terminal::setHistoryCopy(int in){
  // std::cout << "===========\n";
  // std::cout << "input: " << in << "\n";
  // std::cout << "history size: " << history.size() << "\n";
  // std::cout << "result with vars: " << (in<-1 || in>=static_cast<int>(history.size())) << "\n";
  // std::cout << "result in<-1: " << (in<-1) << "\n";
  // std::cout << "result in>=history.size(): " << (in>=history.size()) << "\n";
  // std::cout << "hardcoded result: " << (-1<-1 || -1>=2) << "\n";
  // std::cout << "hardcoded -1<-1: " << (-1<-1) << "\n";
  // std::cout << "hardcoded -1>=2: " << (-1>=2) << "\n";

  // std::cout << "history size: " << history.size() << "\n";

  if(in<-1 || in>=static_cast<int>(history.size()))
  // if(in<-1 || in>=history.size())
    return;

  currentHistoryCommandCopy=in;

  std::cout << in << "==\n";
  
  if(in==-1){
    currentCommand.clear();
    currentCommand.push_back("");
  }else{
    currentCommand=history[in];
  }
}

