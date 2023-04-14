/*
  Daren Kostov

  a class that contains the main startup and loop

  it's not called just "Main" because "main" is too close to it
  
*/

// #include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "structures/node.h"
#include <vector>

class MainClass{

  private:
    //variables:
    std::vector<Node> nodes;

    
  public:

    //constructor, like a atStartUp function
    MainClass();

    //deconstror
    ~MainClass();

    //the function that does all the logic, basically the main function
    void startCLIProgram();
    void startGUIProgram();

};
