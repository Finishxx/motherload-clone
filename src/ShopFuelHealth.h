#ifndef SHOP_FUEL_HEALTH_H
#define SHOP_FUEL_HEALTH_H

#include "Shop.h"

/**
 * @brief Handles refilling player's fuel and health.
 * 
 */
class ShopFuelHealth : public Shop {

  public:
  ShopFuelHealth();

  private:
  virtual void executePurchase( Player * player ) override;
};

#endif /* SHOP_FUEL_HEALTH_H */