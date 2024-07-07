#include <SDL2/SDL.h>
#include "Game.h"
#include <iostream>
#include "Config.h"
#include <fstream>
#include "StartFlags.h"

/**
 * @mainpage Motherload-like survival game
 * 
 * @section gameplay-sec Gameplay
 * 
 * Player can mine precious resources and earn money. Money is spent on gasoline for
 * player's mining vehicle, for repairs and upgrades to the vehicle. The player mine by
 * being on ground pressing SPACEBAR and tapping A/leftArrow, S/downArrow, D/rightArrow.
 * Player can buy fuel, repairs and upgrades only when he is above ground. Fuel & Health is
 * bought by pressing R and Upgrades by pressing U. Player can at any time save
 * his progress by hitting I. Savefiles are stored in saves directory.
 * 
 * @section polymorphism-sec Polymorphism
 * 
 * Map is divided into Tiles. There are a number of tiles that inherit much of their functionality from Tile.
 * Tile has 4 abstract getters for durability, value, solidness, ID for drawing by Graphics class.
 * Whenever a tile is mined mine( Player ) function is called with pointer to Player. Most mineable Tiles
 * give the player money, but Titanium also significantly damages the player. All main components inherit
 * from fully abstract class Component with member fucntions update(), save(), draw(), input().
 * 
 * @section how-to-start-sec How To Start
 * 
 * For playing a fully standard game start with ./tomanma9.
 * For playing a standard game with custom map generator use file MAP_GEN.txt as a template
 * then start the game with ./tomanma9 *map-gen-file*
 * For playing from previously saved file use ./tomanma9 *save-file* 
 * 
 * @section sources-sec Sources
 * For full list check out prohlaseni.txt. To clarify: idea to make Game, Graphics, Input singletons is directly from
 * source SDL Game Development, Schaun Mitchell. Also structure of main and Component class are heavily influenced.
 * 
 */

/**
 * @brief Initializes the game and starts off main loop
 * 
 *  Initializes Game singleton and starts main loop of eventHandling, updating and rendering
 *  also contains frameCounting logic. If we are too fast we wait here with SDL_Delay.
 *  Based on given parameters starts the game by either loading a save, generating a new
 *  map with default settings or generating map with settings from a file.
 *  Save and Load files have different headers.
 */
int main ( int argc, char *argv[] ) {
  Uint32 frameStart, frameDuration;
  bool startBool;

  if ( argc > 1 ) {
    std::ifstream is = std::ifstream( argv[ 1 ] );
    std::string header;
    getline( is, header );
    std::cout << "First header: " << header << std::endl;
    if ( *( header.end() - 1 ) != Config::g_CategoryDelimeter ) {
      std::cout << "Wrong format! " << header << std::endl;
      std::cout << "LastSymbol: " << *( header.end() - 1) << std::endl;
      return -1;
    }
    #ifdef DEBUG
    std::cout << "Header is: " << header << std::endl;
    #endif
    header = header.substr( 0, header.size() - 1 );
    #ifdef DEBUG
    std::cout << "Header after substr: " << header << std::endl;
    #endif
    if ( header == Config::g_MapGeneratorHeader ) {
      std::cout << "Starting Game with custom MapGen!" << std::endl;
      startBool = Game::getInstance() -> init( "Motherload", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, Config::g_WindowWidth,
                                          Config::g_WindowHeight, is, StartFlags::START_USER_GENERATED );
    } else if ( header == Config::g_LoadHeader ) {
      std::cout << "Starting Game with a SaveState!" << std::endl;
          startBool = Game::getInstance() -> init( "Motherload", SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED, Config::g_WindowWidth,
                                             Config::g_WindowHeight, is, StartFlags::START_LOAD_STATE );
    } else {
      std::cout << "NO HEADER MATCHES!!! Wrong input file!" << std::endl;
      return 1;
    }
    
  }
  else {
    std::cout << "Starting Default!" << std::endl;
    std::ifstream str; // dummy :C
    startBool = Game::getInstance() -> init( "Motherload", SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED, Config::g_WindowWidth,
                                             Config::g_WindowHeight, str, StartFlags::START_DEFAULT );
  }

  if ( ! startBool ) {
      std::cout << "Could not initiate the game." << std::endl;
      return 1;
  }
  
  while ( Game::getInstance() -> isRunning() ) // *inspired* by book SDL Game Development
  {
    frameStart = SDL_GetTicks();

    Game::getInstance() -> handleInput();
    Game::getInstance() -> update();
    Game::getInstance() -> render();

    frameDuration = SDL_GetTicks() - frameStart;

    if ( frameDuration < Config::g_TicksInAFrame ) {
      SDL_Delay( Config::g_TicksInAFrame - frameDuration );
    }
  }

  Game::getInstance() -> end();
  delete Game::getInstance();
  return 0;

}