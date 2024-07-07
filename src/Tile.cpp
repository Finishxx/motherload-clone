#include "Tile.h"
#include "Graphics.h"
#include "Config.h"

Pos Tile::symbolicToReal ( const Pos & pos ) {
  return Pos( (int) pos.x * Config::g_TileSize, (int) pos.y * Config::g_TileSize );
}

Pos Tile::realToSymbolic ( const Pos & pos ) {
  return Pos( (int) pos.x / Config::g_TileSize, (int) pos.y / Config::g_TileSize );
}

void Tile::draw() const {
  Pos realPos = symbolicToReal( m_Pos );
  Graphics::getInstance() -> drawRectToMap( getRectID(), realPos, Pos( Config::g_TileSize, Config::g_TileSize ) );
}

void Tile::mine( Player * player ) {
  player -> giveMoney( getValue() );
}