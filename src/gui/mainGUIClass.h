/*
  Daren Kostov

  a class that contains the main startup and loop for GUI
  
*/

#include "../mainClass.h"
#include "../structures/box.h"
#include <SFML/Graphics.hpp>
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

    //tells us if we are in terminal mode or GUI mode
    bool terminalMode;
  
    //notification text, tells us what we did error messages, etc
    sf::Text notification;

    //the window we will be drawwing on/using
    sf::RenderWindow window;

    //Views
    sf::View mapView;
    sf::View UIView;

    //the font used
    sf::Font TheFontWeAreUsing;

    //how much have we zoomed
    double ZoomFactor=1;

    //global clock
    sf::Clock clock;
  
    
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
    void manageSelection(sf::Vector2f);
    
    //manages node selection, will select all or none, when apropriate
    void manageSelection();



    //==returns you what the mouse is hovering over (if you give it the mouse coords), if nothing returns nullptr
    //Works with overlapping nodes!!! (ex: you use the non selected function on a overlapping selected and non seleceted node-> it returns the non selected node)

    //whatever you are hovering over
    Node* hoveringOver(sf::Vector2f);
    //whatever you are hovering as long as its not selected  
    Node* hoveringOverNotSelected(sf::Vector2f);
    //whatever you are hovering as long as its not the main selected node  
    Node* hoveringOverNotSelectedMain(sf::Vector2f);  
    //whatever you are hovering as long as its selected  
    Node* hoveringOverSelected(sf::Vector2f);




    //edits the input in terminal mode
    void performTerminalModeInput(uint32_t);
    //performs actions depending on the output in terminal mode
    void performTerminalModeOutput();


    //these perform the actions of the terminal or GUI
    //give it a sf::RenderWindow, it uses void* because this file has to not include sfml
    void performTerminalActions();
    void performUIAction();

    
    //manages editing the contest of the selected node
    void editContentOfNode(uint32_t);
    void stopEditContentOfNode();
    void startEditContentOfNode();


};
