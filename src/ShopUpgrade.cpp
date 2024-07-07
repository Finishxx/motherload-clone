#include "ShopUpgrade.h"
#include "Config.h"
#include "Parser.h"

const std::string ShopUpgrade::m_CurrentUpgradeString = "ShopUpgradeCurrentUpgrade"; 

ShopUpgrade::ShopUpgrade() {
  m_Name = Config::g_ArmorNames[ 0 ];
  m_NamePos = Pos ( Config::g_WindowWidth,  Config::g_UpgradeNameYPos );
  m_Price = Config::g_UpgradeCosts[ 0 ];
  m_PricePos = Pos ( Config::g_WindowWidth, Config::g_UpgradePriceYPos );
  m_Stock = true;
  m_CurrentUpgrade = 3;
  nextUpgrade();
}

ShopUpgrade::ShopUpgrade( std::string & str ) {
  Parser::parseIntIntoFind( str, m_CurrentUpgradeString, m_CurrentUpgrade );
  m_PricePos = Pos ( Config::g_WindowWidth, Config::g_UpgradePriceYPos );
  m_NamePos = Pos ( Config::g_WindowWidth,  Config::g_UpgradeNameYPos );
  m_Stock = true;
  nextUpgrade();
}

void ShopUpgrade::executePurchase( Player * player ) {
  #ifdef DEBUG
  std::cout << "Player bought Upgrade!" << std::endl;
  #endif
  player -> takeMoney( m_Price );
  applyUpgrade( player );
  m_CurrentUpgrade++;
  nextUpgrade();
}

void ShopUpgrade::applyUpgrade( Player * player ) {
  switch ( m_CurrentUpgrade % Config::g_UpgradeCategories )
  {
  case 0:
    player -> setMaxArmor( Config::g_MaxArmor[ m_CurrentUpgrade / Config::g_UpgradeCategories ] );
    break;
  case 1:
    player -> setMaxFuel( Config::g_FuelCapacity[ m_CurrentUpgrade / Config::g_UpgradeCategories ] );
    break;
  case 2:
    player -> setMiningSpeed( Config::g_DrillSpeeds[ m_CurrentUpgrade / Config::g_UpgradeCategories ] );
    break;
  default:
    break;
  }
}

void ShopUpgrade::nextUpgrade() {
  if ( m_CurrentUpgrade >= Config::g_MaxUpgrade * Config::g_UpgradeCategories ) {
    m_Stock = false;
    m_Name = Config::g_OutOfStockString;
    m_Price = 0;
    return;
  }
  switch ( m_CurrentUpgrade % Config::g_UpgradeCategories )
  {
  case 0:
    m_Name = Config::g_ArmorNames[ m_CurrentUpgrade / Config::g_UpgradeCategories ];
    m_Price = Config::g_UpgradeCosts[ m_CurrentUpgrade / Config::g_UpgradeCategories ];
    break;
  case 1:
    m_Name = Config::g_FuelNames[ m_CurrentUpgrade / Config::g_UpgradeCategories ];
    m_Price = Config::g_UpgradeCosts[ m_CurrentUpgrade / Config::g_UpgradeCategories ];
    break;
  case 2:
    m_Name = Config::g_DrillNames[ m_CurrentUpgrade / Config::g_UpgradeCategories ];
    m_Price = Config::g_UpgradeCosts[ m_CurrentUpgrade / Config::g_UpgradeCategories ];
    break;
  default:
    break;
  }
}

void ShopUpgrade::save( std::ofstream & os ) const {
  Parser::save( os, m_CurrentUpgradeString, std::to_string( m_CurrentUpgrade ) );
}
