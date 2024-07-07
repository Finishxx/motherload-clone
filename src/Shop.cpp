#include "Shop.h"
#include "Graphics.h"
#include <string>

void Shop::draw() const {
  drawPrice();
  drawName();
}

ShopStatus Shop::purchase( Player * player ) {
  if ( ! m_Stock )
    return ShopStatus::OUT_OF_STOCK;
  if ( player -> getMoney() >= m_Price ) {
    executePurchase( player );
    return ShopStatus::PURCHASED;
  }
  return ShopStatus::NO_MONEY;
}

void Shop::drawPrice() const {
  Graphics::getInstance() -> drawTextLeftTop( ( std::to_string( m_Price) + "$" ).c_str(), m_PricePos, Config::g_ShopRightOffset );
}

void Shop::drawName() const {
  Graphics::getInstance() -> drawTextLeftTop( m_Name.c_str(), m_NamePos, Config::g_ShopRightOffset );
}