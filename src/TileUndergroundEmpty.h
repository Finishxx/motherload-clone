#ifndef TILE_UNDERGROUND_EMPTY_H
#define TILE_UNDERGROUND_EMPTY_H

#include "Tile.h"


/**
 * @brief Represents empty underground tile.
 */
class TileUndergroundEmpty : public Tile {

  public:
  TileUndergroundEmpty( Pos pos );

  virtual int getValue() const { return -1; }
  virtual int getDurability() const { return -1; }
  virtual bool isSolid() const { return false; }
  virtual RectID getRectID() const { return RectID::ID_UNDERGROUND_EMPTY; }
};

#endif /* TILE_UNDERGROUND_EMPTY_H */