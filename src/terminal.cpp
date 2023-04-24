/*
  Daren Kostov

  Licence: GPLv3


  The cpp file for the Terminal class

*/

#include "terminal.h"


Terminal::Terminal(){
  enteringCommand=false;
  currentArgument=0;
}
Terminal::~Terminal(){
  
}

void Terminal::startCommand(){
  if(enteringCommand==true) return;
  
  currentArgument=0;
  enteringCommand=true;
  currentCommand.push_back("");

}
void Terminal::endCommand(){
  if(enteringCommand==false) return;
  
  enteringCommand=false;
  history.push_back(currentCommand);
  currentCommand.clear();
  currentArgument=0;
}


void Terminal::haultCommand(){  
  if(enteringCommand==false) return;
  
  enteringCommand=false;
  currentCommand.clear();
  currentArgument=0;

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

