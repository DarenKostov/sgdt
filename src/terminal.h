/*
  Daren Kostov

  Licence: GPLv3


  A terminal interface that accepts multiple commands

*/
#ifndef TERMINAL
#define TERMINAL

#include <string>
#include <vector>

class Terminal{

  private:

    std::vector<std::vector<std::string>> history;
    std::vector<std::string> currentCommand;
    int currentArgument;
    bool enteringCommand;
    
  public:

    Terminal();
    ~Terminal();
      
    void startCommand();
    void endCommand();
    void haultCommand();


    
    void addCharacterToCurrentCommmand(char);
    std::vector<std::string> returnCurrentCommand();
    std::vector<std::string> returnCurrentCommandWithColor();
    std::vector<std::vector<std::string>> returnCommandHistory();

    

    

};

#endif


