#ifndef TILE_BEDROCK_H
#define TILE_BEDROCK_H

#include "Tile.h"

/**
 * @brief Represents bedrock tile. Not used.
 */
class TileBedrock : public Tile {
  public:
  TileBedrock( Pos pos );

  virtual int getValue() const { return -1; }
  virtual int getDurability() const { return -1; }
  virtual bool isSolid() const { return true; }
  virtual RectID getRectID() const { return RectID::ID_BEDROCK; }
};

#endif /* TILE_BEDROCK_H */