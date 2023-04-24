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

    //selected nodes, self explanatory
    std::set<Node*> selectedNodes;

    //the selected node that we are currently working with
    Node* selectedMainNode;

    //this is a helper variable and will not be used a lot
    Node* HoveredNode;

    //tells us we are editing text
    bool editingText;

    //tells us if we are in the process of cutting links
    bool cuttingLinks;

    bool terminalMode;
    
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



    //==returns you what the mouse is hovering over (if you give it the mouse coords), if nothing returns nullptr
    //Works with overlapping nodes!!! (ex: you use the non selected function on a overlapping selected and non seleceted node-> it returns the non selected node)

    //whatever you are hovering over
    Node* hoveringOver(float, float);
    //whatever you are hovering as long as its not selected  
    Node* hoveringOverNotSelected(float, float);
    //whatever you are hovering as long as its not the main selected node  
    Node* hoveringOverNotSelectedMain(float, float);  
    //whatever you are hovering as long as its selected  
    Node* hoveringOverSelected(float, float);




    //edits the input in terminal mode
    void performTerminalModeInput(uint32_t);
    //performs actions depending on the output in terminal mode
    void performTerminalModeOutput(uint32_t);


    //these perform the actions of the terminal or UI
    //give it a sf::RenderWindow, it uses void* because this file has to not include sfml
    void performTerminalActions(void*);
    void performUIAction(void*);

    
    //manages editing the contest of the selected node
    void editContentOfNode(uint32_t);
    void stopEditContentOfNode();
    void startEditContentOfNode();


};
