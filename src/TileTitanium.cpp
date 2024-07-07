#include "TileTitanium.h"
#include "Config.h"

TileTitanium::TileTitanium( Pos pos ) : Tile( pos ) {}

void TileTitanium::mine( Player * player ) {
  Tile::mine( player );
  player -> takeDamage( Config::g_TitaniumDamage );
}