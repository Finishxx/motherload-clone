#ifndef CAMERA_H
#define CAMERA_H

#include "Pos.h"
#include "Player.h"
#include "Component.h"

/**
 * @brief Follows the player.
 * 
 */

class Camera : public Component {
  
  public:
  /**
   * @brief Constructs new camera pointing at player with size defined in Config.
   */
  Camera ( Player * player );
  /**
   * @brief Does out-of-bounds checking and moving.
   */
  void update();

  virtual void draw() const override {}
  virtual void save( std::ofstream & os ) const override {}
  virtual void input() override {}

  Pos getPos() const { return m_Pos; }
  Pos getSize() const { return m_Size; }

  private:
  /**
   * @brief Set pos with respect to how player works in this game.
   */
  void setPosByPlayer( const Pos & pos, const Pos & size ) {  m_Pos = Pos( pos.x - m_Size.x/2, pos.y - m_Size.y/2 ) + Pos ( size.x/2, size.y/2 ) ; }

  Pos m_Size;
  Pos m_Pos;
  Player * m_Player;
};

#endif /* CAMERA_H */
