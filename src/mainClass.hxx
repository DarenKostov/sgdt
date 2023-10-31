/*
Copyright (c) 2023 Daren Kostov

This file is part of SGDT

SGDT is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

SGDT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SGDT
If not, see <https://www.gnu.org/licenses/>.
*/

#include <SFML/Graphics.hpp>
#include <set>
#include <unordered_map>

#include "elements/node.hxx"
#include "elements/link.hxx"


class MainClass{

  private:

    //store the graph
    std::set<Node*> nodes;
    std::unordered_map<Node*, std::unordered_map<Node*, Link*>> links;

    //editor variables
    std::string pathToWorkingFile;
    bool haveWeMadeAnyChanges;
  
    
    //sfml stuff
    sf::RenderWindow window;
    sf::View mainView;
    sf::Clock clock;

    enum ErrorMessage {
    success,
    inputted_nullptr,
    inputted_node_nullptr,
    inputted_link_nullptr,
    connecting_node_to_self,
    rewriting_existing_link,
    node_already_exists,
    link_does_not_exist,
    link_between_nodes_does_not_exist,
    file_path_non_existant_or_unable_to_reach,
    error_reading_from_file_path,
    error_writing_to_file_path,
    incorrect_sgdt_file_format,
   
    };
    
  public:

    //constructor, like a atSTartUp function
    MainClass();

    //deconstror
    ~MainClass();

    //the function that does all the logic, basically the main function
    void startProgram();

  
    private:
    //==Base Methods

    //this performs tasks depending on the actions in the enviroment, like resizing the window 
    void performActions();
  
    //this updates the program, like a "loop" function
    void update();

    //this draws he program, like update but for drawing
    void draw();


    //==Editor Related Methods
        
    //adds a node to the graph, you must provide the node in question
    ErrorMessage addNode(Node*);

    //removes a node from the graph, all links connected to it are severed
    //deletes the object
    ErrorMessage removeNode(Node*);

    //makes a link between 2 nodes, you must provide the link in question
    ErrorMessage addLink(Node*, Node*, Link*);
    ErrorMessage linkNodes(Node*, Node*, Link*);

    //removes a specific link
    //deletes the object
    ErrorMessage removeLink(Link*);

    //deletes a link between 2 nodes (one way, not both)
    //deletes the object
    ErrorMessage severLink(Node*, Node*);

    //gives you a new node pointer with the specific settings
    Node* giveMeNewNodeBasedOnSettings();
  
    //gives you a new link pointer with the specific settings
    Link* giveMeNewLinkBasedOnSettings();


    //deletes every link and node, the graph should be empty after calling this method
    ErrorMessage eraseEverything();
  
    //saves the current graph in a file
    ErrorMessage saveToFile(std::string);

    //loads a graph from a file
    ErrorMessage loadFromFile(std::string);

  

  
  
  
  
  
  
  
  
  
};
