#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include <string>
#include "Player.h"
#include "StartFlags.h"
#include "Camera.h"
#include "Map.h"
#include "HUD.h"
#include "MiningHandler.h"
#include "MovementHandler.h"
#include "ShopHandler.h"
#include "Component.h"
#include <vector>


/**
 * @brief Holds all major parts of the game. 
 * 
 * Implemented as a singleton. Is responsible for startup, cleanup and updating of all major parts including SDL elements.
 * Layout and singleton implementation inspired by the book SDL Game Development.
 */
class Game {

  public:
  static Game * getInstance();
  /**
   * @brief Starts SDL stuff and calls different inits depending on if user wants to load a save, start anew or load mapGen configuration.
   */
  bool init( std::string name,
             int windowStartPosX,
             int WindowStartPosY,
             int windowWidth,
             int windowHeight,
             std::ifstream & is,
             StartFlags startFlag );
  /**
   * @brief Initializes game by loading a previous save from a file.
   */
  bool initFromFile( std::ifstream & is );
  /**
   * @brief Initializes game standardly. If mapGen file is included ( userGenerated = true ) generate map with parameters from that file
   */
  bool initStandard( std::ifstream & is, bool userGenerated );
  /**
   * @brief Handles input of components.
   */
  void handleInput();
  /**
   * @brief Updates all components.
   */
  void update();
  /**
   * @brief Draws all components.
   */
  void render();
  /**
   * @brief Saves current GameState
   */
  void save();
  /**
   * @brief Called when m_Running = false. Cleans all components.
   */
  void end();

  bool isRunning() const { return m_Running; }
  SDL_Renderer * getRenderer() const { return m_Renderer; }


  private:
  Game() = default;
  static Game * m_Instance;
  bool m_Running;
  /**
   * @brief Inserts components after initialization into one vector.
   * 
   */
  void putComponentsIntoVector();

  Player * m_Player;
  Camera * m_Camera;
  Map * m_Map;
  HUD * m_HUD;
  MiningHandler * m_MiningHandler;
  MovementHandler * m_MovementHandler;
  ShopHandler * m_ShopHandler;

  std::vector<Component *> m_Components;

  SDL_Renderer * m_Renderer;
  SDL_Window * m_Window;
  char * m_FileName;

};

#endif /* GAME_H */