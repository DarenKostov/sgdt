/*
  Daren Kostov

  licence: GPLv3

  Simple Graphing/Diagramming Tool- lets you make simple or complex graphs with Simple tools


*/

#include "mainClass.h"
#include "gui/mainGUIClass.h"
#include "cli/mainCLIClass.h"

#include <iostream>
#include <csignal>
#include <string>
#include <fstream>
// #include "licence.cpp"

void printLicence();
void printHelp();




//at exit free the MainClass object 
void atExitFree(MainClass*);

static void freeVariable(){

    std::cout << "\e[93mAbout to Free Main\n\e[0m";
    atExitFree(NULL);
}

void atExitFree(MainClass* in){

    //store a static pointer to our Main
    static MainClass* eternalPtr;

    
    //if we give it a valid pointer, store it; if not, delete it
    if(in){
        std::cout << "\e[93mStoring Main\n\e[0m";
        eternalPtr=in;
        atexit(freeVariable);
    }else{
        std::cout << "\e[93mFreeing Main\n\e[0m";
        delete eternalPtr;
    }
}




void signal_handler(int signal_num){

  std::cout << "\n\e[93mSignal Handler!\n";
  std::cout << "Signal: " << signal_num << "\n\e[0m";
  exit(signal_num);
}


int main(int argc, char **argv){

  bool useGUI=true;

  //read in flags
  for(int i=0; i<argc; i++){
    std::string thisArg=std::string(argv[i]);
    if(thisArg=="-l" || thisArg=="--licence"){
      printLicence();
      return 0;
    }else if(thisArg=="-h" || thisArg=="--help"){
      printHelp();
      return 0;
    }else if(thisArg=="-v" || thisArg=="--version"){

      return 0;
    }else if(thisArg=="-c" || thisArg=="--cli"){
      useGUI=false;
    }else if(thisArg=="-g" || thisArg=="--gui"){
      useGUI=true;

    }

    
  
  }

  std::cout << "\e[93mstart of program\n\e[0m";
  signal(SIGINT, signal_handler);




  MainClass* mainInstance;


  if(useGUI){
    mainInstance=new MainGUIClass();
  }else{
    mainInstance=new MainCLIClass();
  }

  //set the function to be freed AFTER pointing it to memory
  atExitFree(mainInstance);
  
  mainInstance->startProgram();

}

//FUNCTION DEFINITION


void printHelp(){
  std::cout << "-h, --help: this help\n";
  std::cout << "-l, --licence: print the licence\n";
  std::cout << "-v, --version: prints the version\n";
  std::cout << "-c, --cli: opens the program in CLI mode\n";
  std::cout << "-g, --gui: opens the program in GUI mode\n";

}


