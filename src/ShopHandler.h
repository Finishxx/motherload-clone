#ifndef SHOP_HANDLER_H
#define SHOP_HANDLER_H

#include <string>
#include "RectID.h"
#include "Pos.h"
#include "ShopUpgrade.h"
#include "ShopFuelHealth.h"
#include "Player.h"
#include "ShopStatus.h"
#include "Component.h"

/**
 * @brief Holds all shops and displays messages relating to purchases.
 * 
 */
class ShopHandler : public Component {
  public:
  /**
   * @brief Initializes shops standardly.
   */
  ShopHandler( Player * player, int freeSpace );
  /**
   * @brief Initializes shops with values from a saveFile.
   */
  ShopHandler( Player * player, int freeSpace, std::string & str );
  /**
   * @brief Calls draw() on shops and draws message.
   */
  virtual void draw() const override;
  /**
   * @brief Checks for input and calls purchase on shops. Displays/Changes message if need be.
   */
  virtual void update() override;
  virtual void input() override {}
  /**
   * @brief Saves current shop state.
   */
  virtual void save( std::ofstream & os ) const override;

  private:
  void resetTimer() { m_Timer = Config::g_ShopMessageLingerTime; }
  void setMessageAfter( std::string origin, ShopStatus status );
  void drawMessage() const;

  ShopFuelHealth m_ShopFuelHealth;
  ShopUpgrade m_ShopUpgrade;
  Player * m_Player;

  int m_Timer = 0;
  int m_FreeSpace;

  std::string m_Message;

  std::string m_FuelHealth = "Fuel & Health ";
  std::string m_Upgrade = "Upgrade "; 

  std::string m_NoMoney = "No Money!";
  std::string m_Purchased = "Purchased!";
  std::string m_OutOfStock = "Out Of Stock!";
};

#endif /* SHOP_HANDLER_H */