/*
  Daren Kostov

  a class that contains the main startup and loop

  it's not called just "Main" because "main" is too close to it
  
*/

// #include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "structures/node.h"
#include <vector>
#include <set>

class MainClass{

  private:
    //variables:
    std::set<Node*> nodes;
    std::set<Node*> selectedNodes;
    Node* selectedMainNode;

    
  public:

    //constructor, like a atStartUp function
    MainClass();

    //deconstror
    ~MainClass();

    //the function that does all the logic, basically the main function
    void startCLIProgram();
    void startGUIProgram();


    //management functions

    //manage node selection, give it the coords of the mouse IN the world
    void manageSelection(sf::Vector2f);
    //manages node selection, will select all or none, when apropriate
    void manageSelection();

    //manages editing the contest of the selected node
    void editContentOfNode();


};
