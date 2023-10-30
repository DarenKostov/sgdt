/*
  Daren Kostov

  a class that contains the main startup and loop for CLI

  
*/

// #include <SFML/Window.hpp>
#include "../mainClass.h"
#include <vector>
#include <set>

class MainCLIClass : public MainClass{

  protected:
    //variables:
    std::set<Node*> nodes;
    std::set<Node*> selectedNodes;
    Node* selectedMainNode;

    //tells us we are editing text
    bool editingText;
    
  public:

    //constructor, like a atStartUp function
    MainCLIClass();

    //deconstror
    ~MainCLIClass();

    //the function that does all the logic, basically the main function
    virtual void startProgram();


    //management functions

   
};
