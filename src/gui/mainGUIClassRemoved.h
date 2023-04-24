/*
  Daren Kostov

  a class that contains the main startup and loop for GUI, BUT without the GUI
  
*/

#include "../mainClass.h"

class MainGUIClass : public MainClass{

  protected:

  public:

    //constructor, like a atStartUp function
    MainGUIClass();

    //deconstror
    ~MainGUIClass();

    //the function that does all the logic, basically the main function
    void startProgram();
};
