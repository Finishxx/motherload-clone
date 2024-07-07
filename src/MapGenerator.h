#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "Tile.h"
#include "Config.h"
#include <array>
#include <stdlib.h>


/**
 * @brief Class that generates or loads a map and returns it.
 */
class MapGenerator {

  public:
  /**
   * @brief Constructs MapGenerator. Automatically creates new map upon construction with default parameters found in Config.
   */
  MapGenerator();
  /**
   * @brief Construct MapGenerator, based on createNew creates new random map with custom parameters.
   * 
   * @param is ifstream to open file with configuration
   */
  MapGenerator( std::ifstream & is );
  
  /**
   * @brief Returns the finished map
   * 
   * @return std::array<std::array<Tile*,Config::g_MapHeight>,Config::g_MapWidth> 
   */
  std::array<std::array<Tile*,Config::g_MapHeight>,Config::g_MapWidth> getResult();
  /**
   * @brief Generates a new map with configuration given in is
   * 
   * Sets default values and overwrites them if necessary
   * @param is opened file with configuration
   */
  void newUserSetup( std::ifstream & is );
  /**
   * @brief Generates a new totaly random map
   */
  void newTotalyRandom(); // totally random map generation using only Config::FreeSpace
  /**
   * @brief Generates a new map with configuration found in Config
   * 
   * Sets default values and calls newRandom() 
   */
  void newStandardRandom(); // sets parameters to Config defaults and generates a new map
  /**
   * @brief Sets values for generating word to defaults in Config
   */
  void setDefaultValues(); // sets parameters as Config defaults
  /**
   * @brief Based on set member parameters generates a new map
   */
  void newRandom(); // generates map based on current set parameters
  /**
   * @brief Fills map with TileEmpty from y=0 to y=freeSpace
   */
  void createFreeSpace( int freeSpace );
  /**
   * @brief Fills map with dirt from y=freeSpace to y=Config::g_MapHeight
   */
  void fillWithDirt( int freeSpace );
  /**
   * @brief Randomly generates a resource with given parameters.
   * 
   * @param rectID What resource to generate
   * @param startDepth how many blocks below m_FreeSpace should the resource start appearing
   * @param startPercent what is the initial chance of the resource appearing
   * @param endPercent what is the final and highest chance of the resource appearing
   */
  void generateResource( RectID rectID, int startDepth, int startPercent, int endPercent );
  /**
   * @brief Overloaded brother for when we don't care about endPercent i.e. startPercent = endPercent
   */
  void generateResource( RectID rectID, int startDepth, int percent );

  int getFreeSpace() { return m_FreeSpace; }

  private:
  bool m_FailBool = false;
  std::array<std::array<Tile*,Config::g_MapHeight>,Config::g_MapWidth> m_Result;


  const std::string m_FileHeader = "GenerationSetup";

  int m_FreeSpace; const std::string m_FreeSpaceString = "FreeSpace";

  int m_UndergroundEmptySpawnChance;
  const std::string m_UndergroundEmptySpawnChanceString = "UndergroundEmptySpawnChance";
  int m_UnderGroundEmptySpawnDepth;
  const std::string m_UnderGroundEmptySpawnDepthString = "UnderGroundEmptySpawnDepth";

  int m_CoalSpawnChance; const std::string m_CoalSpawnChanceString = "CoalSpawnChance";
  int m_CoalSpawnDepth; const std::string m_CoalSpawnDepthString = "CoalSpawnDepth";

  int m_IronSpawnChance; const std::string m_IronSpawnChanceString = "IronSpawnChance";
  int m_IronSpawnChanceMax; const std::string m_IronSpawnChanceMaxString = "IronSpawnChanceMax";
  int m_IronSpawnDepth; const std::string m_IronSpawnDepthString = "IronSpawnDepth";

  int m_GoldSpawnChance; const std::string m_GoldSpawnChanceString = "GoldSpawnChance";
  int m_GoldSpawnChanceMax; const std::string m_GoldSpawnChanceMaxString = "GoldSpawnChanceMax";
  int m_GoldSpawnDepth; const std::string m_GoldSpawnDepthString = "GoldSpawnDepth";

  int m_TitaniumSpawnChance; const std::string m_TitaniumSpawnChanceString = "TitaniumSpawnChance";
  int m_TitaniumSpawnChanceMax; const std::string m_TitaniumSpawnChanceMaxString = "TitaniumSpawnChanceMax";
  int m_TitaniumSpawnDepth; const std::string m_TitaniumSpawnDepthString = "TitaniumSpawnDepth";

};

#endif /* MAP_GENERATOR_H */