#ifndef MINING_HANDLER_H
#define MINING_HANDLER_H
#include "Player.h"
#include "Tile.h"
#include "Map.h"
#include "Component.h"
/**
 * @brief Handles player mining.
 */
class MiningHandler : public Component {
  public:

  virtual void draw() const override {}
  /**
   * @brief Saves current mining progress and current mined tile.
   */
  virtual void save( std::ofstream & os ) const override;
  virtual void input() override {}

  /**
   * @brief Initializes MiningHandler with pointer to player and map on which he acts.
   */
  MiningHandler( Player * player, Map * map );
  /**
   * @brief Initializes MiningHandler from a file in str.
   */
  MiningHandler( Player * player, Map * map, std::string & str );
  /**
   * @brief If not mining checks for player input. If mining advances the process or ends it.
   */
  void update();

  private:
  Player * m_Player;
  Map * m_Map;

  /**
   * @brief Based on player input decides if player wants to mine and sets the direction if so.
   * 
   * @param miningDir Dir in which player wants to mine
   * @return true player is wanting to mine
   * @return false player is pushing button combination that implies he is not interested in mining
   */
  bool calculateMiningDir( Pos & miningDir );
  /**
   * @brief increases m_MiningProgress or ends mining - destroys block and gives player rewards
   */
  void continueMining();

  double m_MiningProgress;
  bool m_Mining;
  Tile * m_MinedTile;

  static std::string const m_MiningProgressString;
  static std::string const m_IsMiningString;
  static std::string const m_MinedTilePosString;

};

#endif /* MINING_HANDLER_H */