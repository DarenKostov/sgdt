/*
  Daren Kostov

  a class that contains the main startup and loop for GUI
  
*/

#include "../mainClass.h"
#include "../structures/box.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <stdint.h>

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
  
    //tells us we are editing text
    bool editingColor;

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
  
    //the link style the next link will take
    linkStyle nextLinkStyle;
    
    //global clock
    sf::Clock clock;

    //types of notifications
    enum notificationType {info, error, warning};

    
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


    //loads a file and replaces the current "workspace" with its contents
    int loadFromFile(std::string);

    //edits the input in terminal mode
    void performTerminalModeInput(uint32_t);
    //performs actions depending on the output in terminal mode
    void performTerminalModeOutput();


    //these perform the actions of the terminal or GUI
    //give it a sf::RenderWindow, it uses void* because this file has to not include sfml
    void performTerminalActions();
    void performUIAction();

    //gives you a new Box pointer
    Node* giveMeNewNode();
  
    //gives you a new Connector pointer
    Link* giveMeNewLink();

    //adds a Connector
    void addLink(Node*, Node*, Link*);


    //removes every node (box) & link (connector)
    void eraseEverything();

    
    //manages editing the content of the selected node
    void editContentOfNode(uint32_t);
    void stopEditContentOfNode();
    void startEditContentOfNode();

    //manages editing of the color of the selected node
    void editColorOfNode(uint32_t);
    void stopEditColorOfNode();
    void startEditColorOfNode();

    //starts a notification :/
    void startNotification(std::string);
    void startNotification(std::string, notificationType);

};
