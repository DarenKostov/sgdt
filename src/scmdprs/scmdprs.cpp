/*
  Daren Kostov

  Licence: GPLv3

  The logic behind the Simple CoMmanD PaRSer

*/

#include "scmdprs.h"


std::vector<std::string> readLine(){
  
  //dont ignore white spaces
  std::cin >> std::noskipws;

  std::vector<std::string> commands;
  int commandIndex=0;

  while(true){

    //new command?
    char element;
    commands.push_back(std::string());


    //initial quotes handling
    bool areWeInQuotes=false;
    std::cin >> element;
    if(element=='"')
      areWeInQuotes=true;
    else
      commands[commandIndex]+=element;

    
    //is there a separator?
    while(std::cin >> element && (areWeInQuotes+(element!=' ')) && element!='\n'){

      //closing the quotes?
      if(areWeInQuotes==true && element=='"'){
        areWeInQuotes=false;
      }else
        //if not, add the char to the current argument
        commands[commandIndex]+=element;
    
      
    }

    //end of commands?
    if(element=='\n')
      break;
    
    commandIndex++;
  } 
  
  //ignore whitespaces
  std::cin >> std::skipws;

  return commands;

}
