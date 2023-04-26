 /*
  Daren Kostov

  a class that contains the main startup and loop

  it's not called just "Main" because "main" is too close to it
  
*/
#ifndef MAIN_CLASS
#define MAIN_CLASS


#include "structures/node.h"
#include "structures/link.h"
#include "terminal.h"
#include <vector>
#include <set>
#include <unordered_map>

class MainClass{

  protected:
    //variables:
    std::set<Node*> nodes;
    std::unordered_map<Node*, std::unordered_map<Node*, Link*>> links;
    Terminal terminal;

    //the path to the file we opened, are working with;
    std::string pathToWorkingFile;


    //tells us if we have made any changes since last save
    bool haveWeMadeAnyChanges;

    
  public:

    
    //constructor, like a atStartUp function
    MainClass();

    //deconstror
    virtual ~MainClass();

    //the function that does all the logic, basically the main function
    virtual void startProgram();


    //management functions

    virtual void addNode(Node*);
    virtual void removeNode(Node*);
    virtual void addLink(Node*, Node*, Link*);
  
    virtual void clearEverything();
  
    //gives you a new Node pointer
    virtual Node* giveMeNewNode();
  
    //gives you a new Link pointer
    virtual Link* giveMeNewLink();

    //saves the data to a file
    virtual int saveToFile(std::string);

    //loads the data from a file
    virtual int loadFromFile(std::string);

  
};

#endif