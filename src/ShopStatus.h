#ifndef SHOP_STATUS_H
#define SHOP_STATUS_H

/**
 * @brief Holds all possible outcomes of a purchase in a shop.
 */
enum ShopStatus {
  PURCHASED,
  NO_MONEY,
  OUT_OF_STOCK
};

#endif /* SHOP_STATUS_H */