#ifndef TILE_H
#define TILE_H

#include "Pos.h"
#include "RectID.h"
#include "Player.h"
/**
 * @brief Represent a square tile in the world. Some can be mined and give the player gold.
 */
class Tile {
  public:
  Tile( Pos pos ) : m_Pos( pos ) {};
  /**
   * @brief Draws tile on the map
   * 
   */
  virtual void draw() const;
  /**
   * @brief Converts a symbolic pos of a tile e.g. ( 5, 5 ) to real pos e.g. ( 500, 500 ) given tileSize = 100
   */
  static Pos symbolicToReal ( const Pos & pos );
  /**
   * @brief Converts a symbolic pos of a tile e.g. ( 500, 500 ) to real pos e.g. ( 5, 5 ) given tileSize = 100
   */
  static Pos realToSymbolic ( const Pos & pos );

  virtual int getValue() const = 0;
  virtual int getDurability() const = 0;
  virtual bool isSolid() const = 0;
  virtual RectID getRectID() const = 0;

  virtual Pos getPos() const { return m_Pos; }
  /**
   * @brief Does actions on player when mined. Normally just gives value.
   */
  virtual void mine( Player * player );

  virtual ~Tile() = default;

  protected:
  Pos m_Pos;


};

#endif /* TILE_H */