#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <array>
#include <vector>
#include "Camera.h"
#include "Component.h"

/**
 * @brief Holds, draws and initializes map array i.e. manages tiles.
 */
class Map : public Component {

  public:
  virtual void input() override {}
  virtual void update() override {}
  /**
   * @brief Saves map and m_FreeSpace in [ **map-info** ] format into os. 
   */
  virtual void save( std::ofstream & os ) const override;
  void saveMap( std::ofstream & os ) const;

  /**
   * @brief Draws tiles that are visible by camera.
   */
  virtual void draw() const override;
  /**
   * @brief For debuging purposes prints part of a map.
   */
  void printPart( int x, int y, int xEnd, int yEnd ) const;

  Map( Camera * camera ) { m_Camera = camera; }
  Map( Camera * camera, std::string & str );
  /**
   * @brief Initializes new map standardly i.e. randomly generated world with setup form Config.
   */
  void initNewMap();
  /**
   * @brief Initializes new map with user-made genFile.
   */
  void initNewMap( std::ifstream & is );
  /**
   * @brief Returns vector of 3 tiles in a specified direction.
   */
  std::vector<Tile *> getTilesInDir( Pos pos, Pos dir ) const; // used in player movement collision

  void mineTile( const Pos & pos ); // position in actual array

  Tile * getTile( const Pos & pos ); // position in actual array
  int getFreeSpace() { return m_FreeSpace; }

  ~Map();

  private:
  static Map * m_Instance;
  std::array<std::array<Tile *, Config::g_MapHeight>, Config::g_MapWidth> m_Map;

  int m_FreeSpace;
  Camera * m_Camera;
  /**
   * @brief Frees all tiles.
   */
  void clearMap();

  static std::string const m_FreeSpaceString;
  static std::string const m_MapSizeString;

};

#endif /* MAP_H */