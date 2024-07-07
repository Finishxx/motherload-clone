#ifndef TILE_DIRT_H
#define TILE_DIRT_H

#include "Tile.h"

/**
 * @brief Represents a dirt tile
 */
class TileDirt : public Tile {

  public:
  TileDirt( Pos pos );

  virtual int getValue() const { return Config::g_DirtPrice; }
  virtual int getDurability() const { return Config::g_DirtDurability; }
  virtual bool isSolid() const { return true; }
  virtual RectID getRectID() const { return RectID::ID_DIRT; }

};

#endif /* TILE_DIRT_H */