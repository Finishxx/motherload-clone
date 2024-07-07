#ifndef TILE_TITANIUM_H
#define TILE_TITANIUM_H

#include "Tile.h"


/**
 * @brief Represents titanium tile. Upon mining this tile player takes damage.
 */
class TileTitanium : public Tile {

  public:
  TileTitanium( Pos pos );

  virtual void mine( Player * player ) override;

  virtual int getValue() const { return Config::g_TitaniumPrice; }
  virtual int getDurability() const { return Config::g_TitaniumDurability; }
  virtual bool isSolid() const { return true; }
  virtual RectID getRectID() const { return RectID::ID_TITANIUM; }
};

#endif /* TILE_TITANIUM_H */