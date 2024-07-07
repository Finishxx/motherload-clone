#ifndef PLAYER_H
#define PLAYER_H

#include "Pos.h"
#include "RectID.h"
#include "Config.h"
#include "Component.h"

/**
 * @brief Holds information about player and provides interface for other objects to act on player.
 */
class Player : public Component {

  public:
  /**
   * @brief Initializes player standardly.
   * 
   */
  Player();
  /**
   * @brief Initializes player from a file in str.
   */
  Player( std::string & str );
  /**
   * @brief Responds to player input by changing currentDir.
   */
  void input();
  /**
   * @brief Updates fuel.
   */
  void update();
  /**
   * @brief Draws player on the screen together with "Player" name
   */
  virtual void draw() const override;
  /**
   * @brief Saves player into os.
   */
  virtual void save( std::ofstream & os ) const override;

  Pos getPos() const { return m_Pos; }
  Pos getSize() const { return m_Size; }
  Pos getDir() const { return m_Dir; }
  bool isMining() const { return m_Mining; }

  void setDir( Pos dir ) { m_Dir = dir; }
  void setPos( Pos pos ) { m_Pos = pos; }
  void setMining( bool mining ) { m_Mining = mining; }
  void fuelAndRepair() { m_Fuel = m_MaxFuel; m_Armor = m_MaxArmor; }
  void setMaxArmor( int maxArmor ) { m_MaxArmor = maxArmor; }
  void setMaxFuel( int maxFuel ) { m_MaxFuel = maxFuel; }
  void setMiningSpeed( int miningSpeed ) { m_MiningSpeed = miningSpeed; } 

  void takeDamage( int damage ) { m_Armor -= damage; }

  double getArmor() const { return m_Armor; }
  double getMaxArmor() const { return m_MaxArmor; }
  double getFuel() const { return m_Fuel; }
  double getMaxFuel() const { return m_MaxFuel; }
  double getMiningSpeed() const { return m_MiningSpeed; }

  int getMoney() const { return m_Money; }
  void takeMoney( int money ) { m_Money -= money; }
  void giveMoney( int money ) { m_Money += money; }

  private:
  Pos m_Size;
  Pos m_Pos;
  Pos m_Dir;
  RectID m_RectID;

  bool m_Mining;

  double m_Armor = Config::g_MaxArmor[ 0 ];
  double m_MaxArmor = Config::g_MaxArmor[ 0 ];
  double m_Fuel = Config::g_FuelCapacity[ 0 ];
  double m_MaxFuel = Config::g_FuelCapacity[ 0 ];
  double m_MiningSpeed = Config::g_DrillSpeeds[ 0 ];
  int m_Money;

  static std::string const m_ArmorString;
  static std::string const m_MaxArmorString;
  static std::string const m_FuelString;
  static std::string const m_MaxFuelString;
  static std::string const m_MiningSpeedString;
  static std::string const m_MoneyString;
  static std::string const m_SizeString;
  static std::string const m_PosString;
  static std::string const m_DirString;
  static std::string const m_MiningString;

};

#endif /* PLAYER_H */