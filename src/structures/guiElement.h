/*
  Daren Kostov

  Licence: GPLv3

  A general gui element
    
*/


#ifndef GUI_ELEMENT
#define GUI_ELEMENT
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GUIElement{
  protected:
    int lineThickness;
 
  public:

  virtual void draw(sf::RenderWindow&)=0;

};

#endif

