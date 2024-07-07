#include "MapGenerator.h"
#include "TileEmpty.h"
#include "TileDirt.h"
#include "TileCoal.h"
#include "TileIron.h"
#include "TileGold.h"
#include "TileTitanium.h"
#include "TileUndergroundEmpty.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include "Parser.h"

#include <time.h>

MapGenerator::MapGenerator( std::ifstream & is ) {
  srand( time( 0 ) );
  newUserSetup( is );
}

MapGenerator::MapGenerator() {
  srand( time(0) );
  newStandardRandom();
}

void MapGenerator::createFreeSpace( int freeSpace ) {
  for ( int i = 0; i < Config::g_MapWidth; i++ )
    for ( int j = 0; j < freeSpace; j++ )
      m_Result[i][j] = new TileEmpty( Pos( i, j ) );
}

void MapGenerator::newTotalyRandom() {
  for ( int i = 0; i < Config::g_MapWidth; i++ )
    for ( int j = m_FreeSpace; j < Config::g_MapHeight; j++ ) {

      int current = rand() % 6;
      switch (current)
      {
      case 0:
        m_Result[i][j] = new TileDirt( Pos( i, j ) );
        break;
      case 1:
        m_Result[i][j] = new TileCoal( Pos( i, j ) );
        break;
      case 2:
        m_Result[i][j] = new TileIron( Pos ( i, j ) );
        break;
      case 3:
        m_Result[i][j] = new TileGold( Pos( i, j ) );
        break;
      case 4:
        m_Result[i][j] = new TileTitanium( Pos( i, j ) );
        break;
      case 5:
        m_Result[i][j] = new TileUndergroundEmpty( Pos( i, j ) );
        break;
      default:
        break;
      }
    }
}

void MapGenerator::newStandardRandom() {
  setDefaultValues();
  newRandom();
}

void MapGenerator::setDefaultValues() {
  m_FreeSpace = Config::g_FreeSpace;

  m_UnderGroundEmptySpawnDepth = Config::g_UnderGroundEmptySpawnDepth;
  m_UndergroundEmptySpawnChance = Config::g_UndergroundEmptySpawnChance;

  m_CoalSpawnDepth = Config::g_CoalSpawnDepth;
  m_CoalSpawnChance = Config::g_CoalSpawnChance;
  
  m_IronSpawnDepth = Config::g_IronSpawnDepth;
  m_IronSpawnChance = Config::g_IronSpawnChance;
  m_IronSpawnChanceMax = Config::g_IronSpawnChanceMax;

  m_GoldSpawnDepth = Config::g_GoldSpawnDepth;
  m_GoldSpawnChance = Config::g_GoldSpawnChance;
  m_GoldSpawnChanceMax = Config::g_GoldSpawnChanceMax;

  m_TitaniumSpawnDepth = Config::g_TitaniumSpawnDepth;
  m_TitaniumSpawnChance = Config::g_TitaniumSpawnChance;
  m_TitaniumSpawnChanceMax = Config::g_TitaniumSpawnChanceMax;
}

void MapGenerator::newUserSetup( std::ifstream & is ) {
  setDefaultValues();
  try
  {    
    std::string str;
    for ( std::string temp ; std::getline( is, temp ); )
      str += temp;
    std::cout << "NewNewString: " << str << std::endl;

    // We ignore bool return value of parseIntIntoFind because we have default value in contrast to saveGame 

    Parser::parseIntIntoFind( str, m_FreeSpaceString, m_FreeSpace );
    
    Parser::parseIntIntoFind( str, m_UndergroundEmptySpawnChanceString, m_UndergroundEmptySpawnChance );
    
    Parser::parseIntIntoFind( str, m_UnderGroundEmptySpawnDepthString, m_UnderGroundEmptySpawnDepth );
    
    Parser::parseIntIntoFind( str, m_CoalSpawnChanceString, m_CoalSpawnChance );
    Parser::parseIntIntoFind( str, m_CoalSpawnDepthString, m_CoalSpawnDepth );

    Parser::parseIntIntoFind( str, m_IronSpawnChanceString, m_IronSpawnChance );
    Parser::parseIntIntoFind( str, m_IronSpawnChanceMaxString, m_IronSpawnChanceMax ); 
    Parser::parseIntIntoFind( str, m_IronSpawnDepthString, m_IronSpawnDepth );

    Parser::parseIntIntoFind( str, m_GoldSpawnChanceString, m_GoldSpawnChance );
    Parser::parseIntIntoFind( str, m_GoldSpawnChanceMaxString, m_GoldSpawnChanceMax );
    Parser::parseIntIntoFind( str, m_GoldSpawnDepthString, m_GoldSpawnDepth );

    Parser::parseIntIntoFind( str, m_TitaniumSpawnChanceString, m_TitaniumSpawnChance );
    Parser::parseIntIntoFind( str, m_TitaniumSpawnChanceMaxString, m_TitaniumSpawnChanceMax );
    Parser::parseIntIntoFind( str, m_TitaniumSpawnDepthString, m_TitaniumSpawnDepth );
  }
  catch(const std::logic_error& e)
  {
    std::cout << "Logic error in newUserSetup!" << std::endl;
    m_FailBool = true;
    std::cout << "ErrorMessage: " << e.what() << std::endl;
    return;
  }
  #ifdef DEBUG
  std::cout << "m_FreeSpace: " << m_FreeSpace << std::endl;

  std::cout << "m_UndergroundEmptySpawnChance: " << m_UndergroundEmptySpawnChance << std::endl;
  std::cout << "m_UnderGroundEmptySpawnDepth: " << m_UnderGroundEmptySpawnDepth << std::endl;

  std::cout << "m_CoalSpawnChance: " << m_CoalSpawnChance << std::endl;
  std::cout << "m_CoalSpawnDepth: " << m_CoalSpawnDepth << std::endl;

  std::cout << "m_IronSpawnChance: " << m_IronSpawnChance << std::endl;
  std::cout << "m_IronSpawnChanceMax: " << m_IronSpawnChanceMax << std::endl;
  std::cout << "m_IronSpawnDepth: " << m_IronSpawnDepth << std::endl;

  std::cout << "m_GoldSpawnChance: " << m_GoldSpawnChance << std::endl;
  std::cout << "m_GoldSpawnChanceMax: " << m_GoldSpawnChanceMax << std::endl;
  std::cout << "m_GoldSpawnDepth: " << m_GoldSpawnDepth << std::endl;

  std::cout << "m_TitaniumSpawnChance: " << m_TitaniumSpawnChance << std::endl;
  std::cout << "m_TitaniumSpawnChanceMax: " << m_TitaniumSpawnChanceMax << std::endl;
  std::cout << "m_TitaniumSpawnDepth: " << m_TitaniumSpawnDepth << std::endl;

  #endif /* DEBUG */
  std::cout << "M_FreeSpace: " << m_FreeSpace << std::endl;
  is.close();
  newRandom();
}

void MapGenerator::newRandom() {
  createFreeSpace( m_FreeSpace );
  fillWithDirt( m_FreeSpace );

  std::cout << "Generating empty underground:" << std::endl;
  generateResource( RectID::ID_UNDERGROUND_EMPTY,
                    m_UnderGroundEmptySpawnDepth,
                    m_UndergroundEmptySpawnChance );
  std::cout << "Generating coal:" << std::endl;
  generateResource( RectID::ID_COAL,
                    m_CoalSpawnDepth,
                    m_CoalSpawnChance );
  std::cout << "Generating iron:" << std::endl;
  generateResource( RectID::ID_IRON,
                    m_IronSpawnDepth,
                    m_IronSpawnChance,
                    m_IronSpawnChanceMax );
  std::cout << "Generating gold:" << std::endl;
  generateResource( RectID::ID_GOLD,
                    m_GoldSpawnDepth,
                    m_GoldSpawnChance,
                    m_GoldSpawnChanceMax );
  std::cout << "Generating titanium:" << std::endl;
  generateResource( RectID::ID_TITANIUM,
                    m_TitaniumSpawnDepth,
                    m_TitaniumSpawnChance,
                    m_TitaniumSpawnChanceMax );
}

void MapGenerator::generateResource( RectID rectID, int startDepth, int percent ) {
  generateResource( rectID, startDepth, percent, percent );
}

void MapGenerator::generateResource( RectID rectID, int startDepth, int startPercentage, int endPercentage ) {
  int chanceDiff = floor( endPercentage - startPercentage );

  int trueDepth = startDepth + m_FreeSpace;

  int undergroundCount = floor( Config::g_MapHeight - trueDepth );
  for ( int j = trueDepth; j < Config::g_MapHeight; j++ ) {
    int currentChance;
    if ( chanceDiff == 0 )
      currentChance = startPercentage;
    else
      currentChance = floor( startPercentage
                                + ( chanceDiff * (double) floor( j - trueDepth ) ) / (double) undergroundCount );
    if ( rectID == RectID::ID_UNDERGROUND_EMPTY ) {
    }
    for ( int i = 0; i < Config::g_MapWidth; i++ )
      if ( rand() % 100 <= currentChance ) {
        
        delete m_Result[i][j];
        switch (rectID)
        {
        case RectID::ID_UNDERGROUND_EMPTY:
          m_Result[i][j] = new TileUndergroundEmpty( Pos ( i, j ) );
          break;
        case RectID::ID_COAL:
          m_Result[i][j] = new TileCoal( Pos( i, j ) );
          break;
        case RectID::ID_IRON:
          m_Result[i][j] = new TileIron( Pos( i, j ) );
          break;
        case RectID::ID_GOLD:
          m_Result[i][j] = new TileGold( Pos( i, j ) );
          break;
        case RectID::ID_TITANIUM:
          m_Result[i][j] = new TileTitanium( Pos( i, j ) );
          break;
        default:
          break;
        }
      }
  }
}

void MapGenerator::fillWithDirt( int freeSpace ) {
  for ( int i = 0; i < Config::g_MapWidth; i++ )
    for ( int j = freeSpace; j < Config::g_MapHeight; j++ )
      m_Result[i][j] = new TileDirt( Pos( i, j ) );
}

std::array<std::array<Tile*,Config::g_MapHeight>,Config::g_MapWidth> MapGenerator::getResult() {
  return m_Result;
}
