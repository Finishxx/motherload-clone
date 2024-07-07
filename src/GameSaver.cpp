#include "GameSaver.h"
#include "Config.h"
#include <ctime>
#include <fstream>
#include <string>

GameSaver::GameSaver( std::vector<Component *> components )
    : m_Components( components ) {}

void GameSaver::saveCurrentTime( const std::string & namePrefix ) {
  std::time_t currentTime = std::time( nullptr );
  std::tm * localTime = std::localtime( &currentTime );
  char name[ 100 ];
  std::string del = std::string( 1, Config::g_SaveFileDelimeter );
  #ifdef DEBUG
  std::cout << "GameSaver::SaveFileDelimeter " << Config::g_SaveFileDelimeter << std::endl;
  #endif
  std::string format = "%Y" + del + "%m" + del + "%d" + del + "%H" + del + "%M" + del + "%S";
  std::strftime( name, 100, format.c_str(), localTime );
  std::ofstream file;
  file.open( Config::g_SaveLocation + namePrefix + name, std::ios::out );
  file << Config::g_LoadHeader << Config::g_CategoryDelimeter << std::endl;
  for ( Component * component : m_Components ) {
    if ( file )
      component -> save( file );
    else
      std::cout << "File not open!!" << std::endl;
  }
  file.close();
}
