#ifndef MOVEMENT_HANDLER_H
#define MOVEMENT_HANDLER_H

#include "Player.h"
#include "Map.h"
#include "Component.h"

/**
 * @brief Handles movement of player object
 */
class MovementHandler : public Component {
  public:
  virtual void draw() const override {}
  virtual void input() override {}
  virtual void save( std::ofstream & os ) const override {}
  MovementHandler( Player * player, Map * map ) : m_Map( map ), m_Player( player ) {}
  /**
   * @brief Moves player every tick.
   * 
   * Movement is done per pixel basis in a while loop moving x, y, x, y with collision setting dir on that axis to 0.
   */
  void update();

  private:
  /**
   * @brief Moves newPos x by 1 pixel in dir, if not already 0.
   */
  void moveX( Pos & dirCopy, Pos & newPos );
  /**
   * @brief Moves newPos y by 1 pixel in dir, if not already 0. Applies fall damage to Player if player fell too hard.
   */
  void moveY( Pos & dirCopy, Pos & newPos );

  Map * m_Map;
  Player * m_Player;
};

#endif /* MOVEMENT_HANDLER_H */