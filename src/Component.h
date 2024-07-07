#ifndef COMPONENT_H
#define COMPONENT_H

#include <fstream>
/**
 * @brief Abstract parent of all main components of Motherload.
 * 
 * Has abstract methods update() for changing game state, save() for saving gamestate to a file,
 * input() for handling input from the player and draw() for drawing on the screen using Graphics.
 * Heavily inspired by book SDL Game Development.
 */
class Component {
  public:
  virtual void update() = 0;
  virtual void save( std::ofstream & os ) const = 0;
  virtual void input() = 0;
  virtual void draw() const = 0;

  virtual ~Component() = default;

};

#endif /* COMPONENT_H */