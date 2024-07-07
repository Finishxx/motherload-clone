#include <array>
#include "Tile.h"
#include "Config.h"

/**
 * @brief Used when loading map from a file. Parses the map form given string and returns it.
 */
class MapParser {

  public:
  MapParser( std::string & str, int freeSpace );
  std::array<std::array<Tile*,Config::g_MapHeight>,Config::g_MapWidth> getResult();

  private:
  /**
   * @brief Fills m_Result from y=0 to y < m_FreeSpace with TileEmpty
   */
  void createFreeSpace( int freeSpace );
  /**
   * @brief Inserts a tile with given id, x, y into m_Result
   */
  void parseNewTile( RectID id, int x, int y );

  std::array<std::array<Tile*,Config::g_MapHeight>,Config::g_MapWidth> m_Result;

};