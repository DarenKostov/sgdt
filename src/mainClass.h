/*
  Daren Kostov

  a class that contains the main startup and loop

  it's not called just "Main" because "main" is too close to it
  
*/
#ifndef MAIN_CLASS
#define MAIN_CLASS


#include "structures/node.h"
#include <vector>
#include <set>

class MainClass{

  protected:
    //variables:
    std::set<Node*> nodes;
     
  public:

    int i;
    
    //constructor, like a atStartUp function
    MainClass();

    //deconstror
    virtual ~MainClass();

    //the function that does all the logic, basically the main function
    virtual void startProgram();

};

#endif