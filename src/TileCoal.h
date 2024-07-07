#ifndef TILE_COAL_H
#define TILE_COAL_H

#include "Tile.h"


/**
 * @brief Represents coal tile
 */
class TileCoal : public Tile {
  public:
  TileCoal( Pos pos );

  virtual int getValue() const { return Config::g_CoalPrice; }
  virtual int getDurability() const { return Config::g_CoalDurability; }
  virtual bool isSolid() const { return true; }
  virtual RectID getRectID() const { return RectID::ID_COAL; }

};

#endif /* TILE_COAL_H */