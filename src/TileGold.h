#ifndef TILE_GOLD_H
#define TILE_GOLD_H

#include "Tile.h"


/**
 * @brief Represents gold tile.
 */
class TileGold : public Tile {

  public:
  TileGold( Pos pos );

  virtual int getValue() const { return Config::g_GoldPrice; }
  virtual int getDurability() const { return Config::g_GoldDurability; }
  virtual bool isSolid() const { return true; }
  virtual RectID getRectID() const { return RectID::ID_GOLD; }
};

#endif /* TILE_GOLD_H */