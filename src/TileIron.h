#ifndef TILE_IRON_H
#define TILE_IRON_H

#include "Tile.h"


/**
 * @brief Represents iron tile.
 */
class TileIron : public Tile {

  public:
  TileIron( Pos pos );

  virtual int getValue() const { return Config::g_IronPrice; }
  virtual int getDurability() const { return Config::g_IronDurability; }
  virtual bool isSolid() const { return true; }
  virtual RectID getRectID() const { return RectID::ID_IRON; }
};

#endif /* TILE_IRON_H */