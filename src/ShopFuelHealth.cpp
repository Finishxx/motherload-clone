#include "ShopFuelHealth.h"
#include "Config.h"

ShopFuelHealth::ShopFuelHealth() {
  m_Name = "Fuel & Repair";
  m_NamePos = Pos ( Config::g_WindowWidth,  Config::g_FuelHealthNameYPos );
  m_Price = Config::g_FuelHealthPrice;
  m_PricePos = Pos ( Config::g_WindowWidth, Config::g_FuelHealthPriceYPos );
  m_Stock = true;
}

void ShopFuelHealth::executePurchase( Player * player ) {
  #ifdef DEBUG
  std::cout << "Player bought Fuel & Health!" << std::endl;
  #endif
  player -> takeMoney( m_Price );
  player -> fuelAndRepair();
}