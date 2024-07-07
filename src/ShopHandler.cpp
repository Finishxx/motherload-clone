#include "ShopHandler.h"
#include "Input.h"
#include "Graphics.h"
#include "ShopStatus.h"
#include "Tile.h"

ShopHandler::ShopHandler( Player * player, int freeSpace ) : m_Player( player ), m_FreeSpace( freeSpace ) {}

ShopHandler::ShopHandler( Player * player, int freeSpace, std::string & str )
    : m_ShopUpgrade( ShopUpgrade( str ) ), m_Player( player ), m_FreeSpace( freeSpace ) {}

void ShopHandler::draw() const {
  if ( m_Timer > 0 )
    drawMessage();
  m_ShopFuelHealth.draw();
  m_ShopUpgrade.draw();
}

void ShopHandler::save( std::ofstream & os ) const {
  m_ShopUpgrade.save( os );
}


void ShopHandler::drawMessage() const {
  Graphics::getInstance() -> drawTextMiddleTop( m_Message.c_str(), m_Player -> getPos(), m_Player -> getSize(), Config::g_ShopMessageOffset );
}

void ShopHandler::setMessageAfter( std::string origin, ShopStatus status ) {
  resetTimer();
  switch ( status )
  {
  case ShopStatus::NO_MONEY:
    m_Message = origin + m_NoMoney;
    break;
  case ShopStatus::PURCHASED:
    m_Message = origin + m_Purchased;
    break;
  case ShopStatus::OUT_OF_STOCK:
    m_Message = origin + m_OutOfStock;
    break;    
  default:
    break;
  }
}

void ShopHandler::update() {
  if ( m_Timer > 0 )
    m_Timer--;
  ShopStatus status;
  Pos playerSymbolic = Tile::realToSymbolic( m_Player -> getPos() );
  if ( Input::getInstance() -> isKeyDown( SDL_SCANCODE_U ) && playerSymbolic.y < m_FreeSpace ) {
    status = m_ShopUpgrade.purchase( m_Player );
    setMessageAfter( m_Upgrade, status );

  }
  if ( Input::getInstance() -> isKeyDown( SDL_SCANCODE_R ) && playerSymbolic.y < m_FreeSpace ) {
    status = m_ShopFuelHealth.purchase( m_Player );
    setMessageAfter( m_FuelHealth, status );
  }
}