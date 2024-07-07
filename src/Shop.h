#ifndef SHOP_H
#define SHOP_H

#include "Pos.h"
#include "ShopStatus.h"
#include "Player.h"

/**
 * @brief Abstract parent to all shops. Implements a lot of functionality, needs his children to implement executePurchase().
 */
class Shop {

  public:
  /**
   * @brief Draws name and price as text.
   */
  virtual void draw() const;
  /**
   * @brief Given player money and stock decides how the transaction proceedes.
   */
  virtual ShopStatus purchase( Player * player );
  /**
   * @brief Called when player has enough money.
   */
  virtual void executePurchase( Player * player ) = 0;


  protected:
  virtual void drawPrice() const;
  virtual void drawName() const;

  std::string m_Name;
  Pos m_PricePos;
  Pos m_NamePos;

  bool m_Stock;
  int m_Price;

};

#endif /* SHOP_H */