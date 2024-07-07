#ifndef TILE_EMPTY_H
#define TILE_EMPTY_H

#include "Tile.h"

/**
 * @brief Represents an empty tile.
 */
class TileEmpty : public Tile {

  public:
  TileEmpty( Pos pos );

  virtual void draw() const override {} // overrides to empty function so we don't draw

  virtual int getValue() const { return -1; }
  virtual int getDurability() const { return -1; }
  virtual bool isSolid() const { return false; }
  virtual RectID getRectID() const { return RectID::ID_EMPTY; }
};

#endif /* TILE_EMPTY_H */