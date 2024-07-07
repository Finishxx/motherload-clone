#include "Input.h"
#include <iostream>

Input * Input::m_Instance = nullptr;

Input * Input::getInstance() {
  if ( m_Instance == nullptr )
    m_Instance = new Input();
  return m_Instance;
}

void Input::update() {
  if ( m_KeysPressed != nullptr )
    for ( int i = 0; i < 322; i++ )
      m_KeysPressedPrevious[i] = m_KeysPressed[i];

  m_KeysPressed = SDL_GetKeyboardState( 0 );
}

bool Input::isKeyPressed ( SDL_Scancode key ) const {
  if ( m_KeysPressed == nullptr || m_KeysPressed[ key ] == 0 ) 
    return false;
  return true;
}

bool Input::isKeyDown ( SDL_Scancode key ) const {
  if ( m_KeysPressed == nullptr || ! ( m_KeysPressed[ key ] == 1 && m_KeysPressedPrevious[ key ] == 0 ) )
    return false;
  return true;
}

