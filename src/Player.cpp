#include "Player.h"
#include "Graphics.h"
#include "Input.h"
#include "Tile.h"
#include "Parser.h"

std::string const Player::m_ArmorString = "PlayerArmor";
std::string const Player::m_MaxArmorString = "PlayerMaxArmor";
std::string const Player::m_FuelString = "PlayerFuel";
std::string const Player::m_MaxFuelString = "PlayerMaxFuel";
std::string const Player::m_MiningSpeedString = "PlayerMiningSpeed";
std::string const Player::m_MoneyString = "PlayerMoney";
std::string const Player::m_SizeString = "PlayerSize";
std::string const Player::m_PosString = "PlayerPos";
std::string const Player::m_DirString = "PlayerDir";
std::string const Player::m_MiningString = "PlayerIsMining";

Player::Player() {
  std::cout << "Initializing Player" << std::endl;
  m_Dir = Pos( 0, 0 );
  m_Size = Pos( Config::g_TileSize / 2, Config::g_TileSize/2 );
  m_RectID = RectID::ID_PLAYER;
  m_Money = 0;
  m_Mining = false;
}

Player::Player( std::string & str ) {
  if ( !
   (   Parser::parseDoubleIntoFind( str, m_ArmorString, m_Armor )
    && Parser::parseDoubleIntoFind( str, m_MaxArmorString, m_MaxArmor )
    && Parser::parseDoubleIntoFind( str, m_FuelString, m_Fuel )
    && Parser::parseDoubleIntoFind( str, m_MaxFuelString, m_MaxFuel )
    && Parser::parseDoubleIntoFind( str, m_MiningSpeedString, m_MiningSpeed )
    && Parser::parseIntIntoFind( str, m_MoneyString, m_Money )
    && Parser::parsePosIntoFind( str, m_SizeString, m_Size )
    && Parser::parsePosIntoFind( str, m_PosString, m_Pos )
    && Parser::parsePosIntoFind( str, m_DirString, m_Dir )
    && Parser::parseBoolIntoFind( str, m_MiningString, m_Mining )
  ) ) {
    std::cout << "Parsing some of Player values failed!" << std::endl;
  }
  m_RectID = RectID::ID_PLAYER;
}
  
void Player::input() {
  if ( m_Mining ) return;
   if ( m_Dir.x < 0 ) m_Dir.x++;
   else if ( m_Dir.x != 0 ) m_Dir.x--; // standard slow-down

  m_Dir.y += Config::g_Gravity; // gravity
  // Keys
  if ( Input::getInstance() -> isKeyPressed( SDL_SCANCODE_A ) ||
       Input::getInstance() -> isKeyPressed( SDL_SCANCODE_LEFT ) )
    m_Dir.x -= Config::g_Acceleration;
  if ( Input::getInstance() -> isKeyPressed( SDL_SCANCODE_D ) ||
       Input::getInstance() -> isKeyPressed( SDL_SCANCODE_RIGHT ) )
    m_Dir.x += Config::g_Acceleration;
  if ( Input::getInstance() -> isKeyPressed( SDL_SCANCODE_W ) ||
       Input::getInstance() -> isKeyPressed( SDL_SCANCODE_UP ) )
    m_Dir.y -= Config::g_Acceleration;

  // make sure we are not over limit
  if ( m_Dir.x > Config::g_MaxSpeedX ) m_Dir.x = Config::g_MaxSpeedX;
  if ( m_Dir.x < -Config::g_MaxSpeedX ) m_Dir.x = -Config::g_MaxSpeedX;

  if ( m_Dir.y > Config::g_MaxSpeedY ) m_Dir.y = Config::g_MaxSpeedY;
  if ( m_Dir.y < -Config::g_MaxSpeedY/2 ) m_Dir.y = -Config::g_MaxSpeedY/2;

}

void Player::update() {
  m_Fuel -= Config::g_FuelDepletion;
}

void Player::save( std::ofstream & os ) const {
  Parser::save( os, m_ArmorString, std::to_string( m_Armor ) );
  Parser::save( os, m_MaxArmorString, std::to_string( m_MaxArmor ) );
  Parser::save( os, m_FuelString, std::to_string( m_Fuel ) );
  Parser::save( os, m_MaxFuelString, std::to_string( m_MaxFuel ) );
  Parser::save( os, m_MiningSpeedString, std::to_string( m_MiningSpeed ) );
  Parser::save( os, m_MoneyString, std::to_string( m_Money ) );

  Parser::saveBool( os, m_MiningString, m_Mining );

  Parser::savePos( os, m_PosString, m_Pos );
  Parser::savePos( os, m_DirString, m_Dir );
  Parser::savePos( os, m_SizeString, m_Size );
}


void Player::draw() const {
  Graphics::getInstance() -> drawRectToMap( RectID::ID_PLAYER, m_Pos, m_Size );
  Graphics::getInstance() -> drawTextMiddleTop( "Player", m_Pos,
                                                m_Size, Config::g_TileSize/10 + Config::g_FontSize/2 );
}