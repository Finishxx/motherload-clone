#ifndef SHOP_UPGRADE_H
#define SHOP_UPGRADE_H

#include "Shop.h"

/**
 * @brief Handles upgrading player if he has the money.
 */
class ShopUpgrade : public Shop {

  public:
  /**
   * @brief Initializes standardly.
   */
  ShopUpgrade();
  /**
   * @brief Initializes from a file.
   */
  ShopUpgrade( std::string & str );
  /**
   * @brief Saves current status.
   */
  void save( std::ofstream & os ) const;

  private:
  virtual void executePurchase( Player * player ) override;
  /**
   * @brief Sets parameters for displaying current goods.
   */
  void nextUpgrade();
  /**
   * @brief Applies upgrade to player.
   */
  void applyUpgrade( Player * player );

  int m_CurrentUpgrade;

  static std::string const m_CurrentUpgradeString; 

};

#endif /* SHOP_UPGRADE_H */