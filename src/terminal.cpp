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

  if(in<-1 || in>=static_cast<int>(history.size()))
    return;

  currentHistoryCommandCopy=in;

  std::cout << in << "==\n";
  
  if(in==-1){
    currentCommand.clear();
    currentCommand.push_back("");
    currentArgument=0;
  }else{
    currentCommand=history[in];
    currentArgument=currentCommand.size()-1;
  }
}

