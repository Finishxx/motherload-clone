#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
/**
 * @brief Implemented as a singleton. Handles input.
 * 
 * Inspired by book SDL Game Development.
 */
class Input {
public:

  static Input * getInstance();

  /**
   * @brief Updates input, i.e. stores what keys are pressed atm
   */
  void update();
  /**
   * @brief Checks if given key is pressed
   */
  bool isKeyPressed ( SDL_Scancode key ) const;
  /**
   * @brief Returns true if key has just been pressed down.
   */
  bool isKeyDown ( SDL_Scancode key ) const;
  
  private:
  Input() = default;
  static Input * m_Instance;
  const Uint8 * m_KeysPressed;
  Uint8 m_KeysPressedPrevious[ 322 ];
};

#endif /* INPUT_H */