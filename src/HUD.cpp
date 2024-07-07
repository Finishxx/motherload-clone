#include "HUD.h"
#include "Graphics.h"
#include <sstream>

HUD::HUD( Player * player ) {
  m_Player = player;
  m_BarSize = Pos( Config::g_TileSize, Config::g_TileSize/2 );
  m_FuelPos = Pos ( Config::g_TileSize/10 , Config::g_TileSize/10 );
  m_HealthPos = Pos ( Config::g_TileSize/10, Config::g_TileSize/10 + m_FuelPos.y + m_BarSize.y );
  m_MoneyPos = Pos( Config::g_TileSize/10, Config::g_TileSize/10 + m_HealthPos.y + m_BarSize.y );
}

void HUD::draw() const {
  drawFuel();
  drawHealth();
  drawMoney();
}

void HUD::drawFuel() const {
  Graphics::getInstance() -> drawRect( RectID::ID_EMPTY, m_FuelPos, m_BarSize );
  Graphics::getInstance() -> drawRect( RectID::ID_FUEL_BAR, m_FuelPos,
                                       Pos ( floor( m_BarSize.x * (  m_Player -> getFuel() / m_Player -> getMaxFuel() ) ), m_BarSize.y ) );
}

void HUD::drawHealth() const {
  Graphics::getInstance() -> drawRect( RectID::ID_EMPTY, m_HealthPos, m_BarSize );
  Graphics::getInstance() -> drawRect( RectID::ID_HEALTH_BAR, m_HealthPos,
                                       Pos( floor( m_BarSize.x * ( m_Player -> getArmor() / m_Player -> getMaxArmor() ) ), m_BarSize.y ) );  
}

void HUD::drawMoney() const {
  std::stringstream res;
  res << (m_Player -> getMoney() ) << "$";
  Graphics::getInstance() -> drawTextCached( res.str().c_str(), m_MoneyPos );  
}