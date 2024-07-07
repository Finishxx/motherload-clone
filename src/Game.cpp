#include "Game.h"
#include <iostream>
#include "Input.h"
#include "MiningHandler.h"
#include "SDL2/SDL_ttf.h"
#include "Graphics.h"
#include <string>
#include <fstream>
#include "GameSaver.h"

Game * Game::m_Instance = nullptr;

Game * Game::getInstance() {
  if ( m_Instance == nullptr )
    m_Instance = new Game();
  return m_Instance;
}

bool Game::init( std::string name, int windowStartPosX,
                 int WindowStartPosY, int windowWidth, int windowHeight,
                 std::ifstream & is, StartFlags startFlag ) {
  std::cout << "Initializing SDL_Init" << std::endl;

  if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    return false;
  std::cout << "Initializing window" << std::endl;
  m_Window = SDL_CreateWindow( name.c_str(), windowStartPosX, WindowStartPosY,
                               windowWidth, windowHeight, 0 );
  if ( m_Window == 0 )
    return false;
  std::cout << "Initializing renderer" << std::endl;

  m_Renderer = SDL_CreateRenderer( m_Window, -1, 0 );
  if ( m_Renderer == 0 )
    return false;

  m_Running = true;

  std::cout << "Initializing TTF fonts" << std::endl;

  if ( TTF_Init() )
    return false;

  switch ( startFlag )
  {
  case StartFlags::START_DEFAULT:
    return initStandard( is, false );
    break;
  case StartFlags::START_USER_GENERATED:
    return initStandard( is, true );
    break;
  case StartFlags::START_LOAD_STATE:
    return initFromFile( is );
    break;
  default:
    return false;
    break;
  }
}

bool Game::initFromFile( std::ifstream & is ) {
  std::cout << "Initializing from a file" << std::endl;
  std::string str;
  for ( std::string temp; std::getline( is, temp ) ; )
    str += temp;
  m_Player = new Player( str );
  m_Camera = new Camera( m_Player );
  m_Map = new Map( m_Camera, str );
  Graphics::getInstance() -> init( m_Camera );
  m_MiningHandler = new MiningHandler( m_Player, m_Map, str );
  m_MovementHandler = new MovementHandler( m_Player, m_Map );
  m_HUD = new HUD( m_Player );
  m_ShopHandler = new ShopHandler( m_Player, m_Map -> getFreeSpace(), str );
  putComponentsIntoVector();

  return true;
}

bool Game::initStandard( std::ifstream & is, bool userGenerated ) {
  std::cout << "Initializing standardly.." << std::endl;
  m_Player = new Player();
  m_Camera = new Camera( m_Player );
  m_Map = new Map( m_Camera );
  if ( userGenerated )
    m_Map -> initNewMap( is );
  else
    m_Map -> initNewMap();
  Graphics::getInstance() -> init( m_Camera );
  m_MiningHandler = new MiningHandler( m_Player, m_Map );
  m_MovementHandler = new MovementHandler( m_Player, m_Map );
  m_HUD = new HUD( m_Player );
  m_ShopHandler = new ShopHandler( m_Player, m_Map -> getFreeSpace() );
  m_Player -> setPos( Pos( ( Config::g_MapWidth / 2 ) * Config::g_TileSize, ( m_Map -> getFreeSpace() - 1 ) * Config::g_TileSize ) ); // player spawn point
  putComponentsIntoVector();
  return true;
}

void Game::handleInput() {
  Input::getInstance() -> update();
  m_Player -> input();
  SDL_Event event;
  while ( SDL_PollEvent(&event)) 
    if ( event.type == SDL_QUIT ) 
      m_Running = false;
}

void Game::update() {

  for ( Component * component : m_Components )
    component -> update();

  if ( m_Player -> getArmor() < 0 || m_Player -> getFuel() < 0 )
    m_Running = false;
  if ( Input::getInstance() -> isKeyDown( SDL_SCANCODE_I ) )
    save();

}

void Game::render() {
  for ( Component * component : m_Components )
    component -> draw();

  SDL_SetRenderDrawColor( m_Renderer, 0, 0, 255, 0 ); 
  SDL_RenderPresent( m_Renderer );
  SDL_RenderClear( m_Renderer );
}

void Game::save() {
  GameSaver gameSaver = GameSaver( m_Components );
  gameSaver.saveCurrentTime( Config::g_SaveGamePrefix );
}

void Game::end() {
  std::cout << "Exiting game" << std::endl;
  for ( Component * component : m_Components )
    delete component;

  delete Input::getInstance();
  delete Graphics::getInstance();


  SDL_DestroyRenderer( m_Renderer );
  m_Renderer = nullptr;
  SDL_DestroyWindow( m_Window );
  m_Window = nullptr;
  //SDL_QuitSubSystem( SDL_INIT_VIDEO );

  TTF_Quit();
  SDL_Quit();
  std::cout << "SDL_Quit!" << std::endl;


  m_Running = false;
}

void Game::putComponentsIntoVector() {
  m_Components.push_back( m_Map );
  m_Components.push_back( m_Player );
  m_Components.push_back( m_Camera );
  m_Components.push_back( m_HUD );
  m_Components.push_back( m_MiningHandler );
  m_Components.push_back( m_MovementHandler );
  m_Components.push_back( m_ShopHandler );
}


