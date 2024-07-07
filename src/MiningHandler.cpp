#include "MiningHandler.h"
#include "Input.h"
#include <iostream>
#include "Pos.h"
#include "Parser.h"

std::string const MiningHandler::m_MiningProgressString = "MininHandlerMiningProgress";
std::string const MiningHandler::m_IsMiningString = "MiningHandlerIsMining";
std::string const MiningHandler::m_MinedTilePosString = "MiningHandlerMinedTilePos";

MiningHandler::MiningHandler( Player * player, Map * map )
  { m_Player = player; m_MiningProgress = 0; m_Mining = false; m_Map = map; m_MinedTile = nullptr; }

MiningHandler::MiningHandler( Player * player, Map * map, std::string & str )
  : MiningHandler( player, map ) {
  Parser::parseBoolIntoFind( str, m_IsMiningString, m_Mining );
  if ( m_Mining ) {
    Parser::parseDoubleIntoFind( str, m_MiningProgressString, m_MiningProgress );
    Pos minedTilePos = Pos( 0, 0 );
    Parser::parsePosIntoFind( str, m_MinedTilePosString, minedTilePos );
    m_MinedTile = m_Map -> getTile( minedTilePos );
  } else {
    m_MinedTile = nullptr;
  }
}


void MiningHandler::update() {
  if ( m_Mining ) {
    continueMining();
  } else
  {
    Pos miningDir = Pos( 0, 0 );
    if ( ! calculateMiningDir( miningDir ) )
      return;

    Pos playerSymbolic = Tile::realToSymbolic( m_Player -> getPos() + Pos( m_Player -> getSize().x/2, m_Player -> getSize().y/2 ) );
    Tile * minedTile = m_Map -> getTile( playerSymbolic + miningDir );
    Tile * tileBelow = m_Map -> getTile( playerSymbolic + Pos( 0, 1 ) );

    if ( ( ! ( minedTile -> isSolid() && tileBelow -> isSolid() ) )
        || minedTile -> getDurability() < 0 )
      return; // nothing to mine, or we are not on solid ground, or mined tile is not mineable

    miningDir.x *= Config::g_TileSize/10; miningDir.y *= Config::g_TileSize/10;

    if ( Pos::intersects( m_Player -> getPos() + miningDir, m_Player -> getSize(),
                          Tile::symbolicToReal( minedTile -> getPos() ), Pos ( Config::g_TileSize, Config::g_TileSize ) )
        && // we are close enough to mined tile and are grounded
        Pos::intersects( m_Player -> getPos() + Pos( 0, Config::g_TileSize / 10 ), m_Player -> getSize(),
                          Tile::symbolicToReal( tileBelow -> getPos() ), Pos ( Config::g_TileSize, Config::g_TileSize ) ) )  {
      m_Mining = true;
      m_MinedTile = minedTile;
      m_Player -> setMining( true );
    }
  }
}

void MiningHandler::save( std::ofstream & os ) const {
  Parser::saveBool( os, m_IsMiningString, m_Mining );
  Parser::save( os, m_MiningProgressString, std::to_string( m_MiningProgress ) );
  if ( m_Mining )
    Parser::savePos( os, m_MinedTilePosString, m_MinedTile -> getPos() );
}

bool MiningHandler::calculateMiningDir( Pos & miningDir ) {
  if ( ! Input::getInstance() -> isKeyPressed( SDL_SCANCODE_SPACE )
    || Input::getInstance() -> isKeyPressed( SDL_SCANCODE_UP )
    || Input::getInstance() -> isKeyPressed( SDL_SCANCODE_W ) )
    {
      return false; // nothing is pressed or we are trying to fly
    }
  if ( Input::getInstance() -> isKeyPressed( SDL_SCANCODE_A ) 
    || Input::getInstance() -> isKeyPressed( SDL_SCANCODE_LEFT ) )
    miningDir.x--;

  if ( Input::getInstance() -> isKeyPressed( SDL_SCANCODE_D ) 
    || Input::getInstance() -> isKeyPressed( SDL_SCANCODE_RIGHT ) )
    {
    if ( miningDir.x != 0 ) return false;
    else miningDir.x++;
    }

  if ( Input::getInstance() -> isKeyPressed( SDL_SCANCODE_S ) 
    || Input::getInstance() -> isKeyPressed( SDL_SCANCODE_DOWN ) )
    miningDir.y++;
    
  if ( abs( miningDir.y ) + abs( miningDir.x ) >= 2 ) return false; // pressed 2 buttons at once and tried to mine

  return true;
}
void MiningHandler::continueMining() {
  if ( m_MiningProgress < m_MinedTile -> getDurability() )
      m_MiningProgress += m_Player -> getMiningSpeed();
    else {
      #ifdef DEBUG
      std::cout << "Mining::justMinedTile: " << ( m_MinedTile -> getID() ) << " at pos: " << ( m_MinedTile -> getPos() ) << std::endl; 
      #endif
      m_MinedTile -> mine( m_Player );
      m_Map -> mineTile( m_MinedTile -> getPos() );
      m_Mining = false;
      m_Player -> setMining( false );
      m_MiningProgress = 0;
      m_Player -> setDir( Pos( 0, 0 ) );
    }
}