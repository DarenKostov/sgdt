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

    //tells where in the command history we are
    int pointInHistory;

    //tells us where in the argument we are
    int pointArguemnt;

    
  public:

    Terminal();
    ~Terminal();

    //==KEYBOARD INPUT
  
    //start new command
    void startCommand();

    //end and accept current command
    void endCommand();

    //end and discard current command
    void haultCommand();

    //adds a character to the current command (argument)  
    void addCharacterToCurrentCommmand(char);

    //gors to the previous or next argument of the current command
    void goToNextArgument();
    void goToPreviousArgument();

    //go to the next or prevous char in the current command (command)
    void goToNextCharInCommand();
    void goToPreviousCharInCommand();

    //==MISC
    
    //returns us the full current command
    std::vector<std::string> returnCurrentCommand();

    //returnCurrentCommand but twice as long to give you which colors should the arguments be in
    std::vector<std::string> returnCurrentCommandWithColor();

    //returns us the last 10 commands we entered
    std::vector<std::vector<std::string>> returnCommandHistory();


    //io point in history
    void setPointInHistory(int);
    int getPointInHistory();


    //removes the latest command in the history
    void removeLatestHistoryEntry();
    

};

#endif


