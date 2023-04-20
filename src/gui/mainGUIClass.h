/*
  Daren Kostov

  a class that contains the main startup and loop for GUI
  
*/

#include "../mainClass.h"
// #include "../structures/box.h" // no SFML for CLI-only compatible builds
// #include <SFML/Graphics.hpp> // no SFML for CLI-only compatible builds
#include <vector>
#include <set>

class MainGUIClass : public MainClass{

  protected:
    //variables:
    std::set<Node*> selectedNodes;
    Node* selectedMainNode;

    //tells us we are editing text
    bool editingText;
    
  public:

    //constructor, like a atStartUp function
    MainGUIClass();

    //deconstror
    ~MainGUIClass();

    //the function that does all the logic, basically the main function
    void startProgram();


    //management functions

    void removeNode(Node*);

    //GUI management functions
      
    //manage node selection, give it the coords of the mouse IN the world
    void manageSelection(float, float);
    
    //manages node selection, will select all or none, when apropriate
    void manageSelection();

    //returns you what the mouse is hovering over (if you give it the mouse coords), if nothing returns nullptr
    Node* hoveringOver(float, float);


    //manages editing the contest of the selected node
    void editContentOfNode(uint32_t);
    void stopEditContentOfNode();
    void startEditContentOfNode();


};
