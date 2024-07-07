#include "MovementHandler.h"
#include "Pos.h"
#include "Tile.h"
#include "Config.h"
#include <cmath>


void MovementHandler::update() {
  if( m_Player -> isMining() ) return;
  Pos playerDir = m_Player -> getDir();
  if ( playerDir.x == 0 && playerDir.y == 0 ) return;
  Pos dirCopy = playerDir; dirCopy.y = floor(dirCopy.y);
  Pos newPos = m_Player -> getPos();

  std::vector<Tile *> tilesToCheck;

// We move move at a 45 degree angle per pixel starting with x then y and repeat
// if a collision occurs we zero out that dir. If both dirs are 0 we end the loop
  while ( true ) {
    if ( dirCopy.x == 0 && dirCopy.y == 0 ) break;
    moveX( dirCopy, newPos );
    moveY( dirCopy, newPos );
  }
  m_Player -> setPos( newPos );
}

void MovementHandler::moveX( Pos & dirCopy, Pos & newPos ) {

  if ( dirCopy.x == 0 )
    return;

  std::vector<Tile*> tilesToCheck = m_Map -> getTilesInDir( Tile::realToSymbolic( newPos ), Pos( Pos::sgnm( dirCopy.x ), 0 ) );
  
  newPos.x += Pos::sgnm( m_Player -> getDir().x );
  dirCopy.x -= Pos::sgnm( dirCopy.x );

  bool outOfBoundsBool = Pos::isOutOfBounds( newPos, m_Player -> getSize() );

  // Collision
  for ( auto it = tilesToCheck.begin() ; it != tilesToCheck.end() || outOfBoundsBool ; it ++ ) {
    if ( outOfBoundsBool
        ||
        ( (*it) -> isSolid() && Pos::intersects( newPos, m_Player -> getSize(), Tile::symbolicToReal( (*it) -> getPos() ),
                                               Pos( Config::g_TileSize, Config::g_TileSize ) ) ) ) {
      newPos.x -= Pos::sgnm( m_Player -> getDir().x );
      dirCopy.x = 0;
      m_Player -> setDir( Pos( 0, m_Player -> getDir().y ) ) ;
      break;
    }
  }
}

void MovementHandler::moveY( Pos & dirCopy, Pos & newPos ) {
  if ( dirCopy.y == 0 )
    return;

  std::vector<Tile *> tilesToCheck = m_Map -> getTilesInDir( Tile::realToSymbolic( newPos ), Pos( 0, Pos::sgnm( dirCopy.y ) ) );
  
  newPos.y += Pos::sgnm( m_Player -> getDir().y );
  dirCopy.y -= Pos::sgnm( dirCopy.y );

  bool outOfBoundsBool = Pos::isOutOfBounds( newPos, m_Player -> getSize() );
  
  // Collision
  for ( auto it = tilesToCheck.begin() ; it != tilesToCheck.end() || outOfBoundsBool ; it++ ) {
    if ( outOfBoundsBool
      ||
      ( (*it) -> isSolid() && Pos::intersects( newPos, m_Player -> getSize(), Tile::symbolicToReal( (*it) -> getPos() ),
                                               Pos( Config::g_TileSize, Config::g_TileSize ) ) ) ) {
      newPos.y -= Pos::sgnm( m_Player -> getDir().y );
      if ( abs( m_Player -> getDir().y ) >= Config::g_MaxSpeedY/2 )
        m_Player -> takeDamage( abs( m_Player -> getDir().y ) - Config::g_MaxSpeedY/2 );
      dirCopy.y = 0;
      m_Player -> setDir( Pos ( m_Player -> getDir().x, 0 ) );
      break;
    }
  }
}
