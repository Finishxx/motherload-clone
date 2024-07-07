#include "Pos.h"
#include <utility>
#include "SDL2/SDL.h"
#include "Config.h"

int Pos::sgnm( int x ) {
  if ( x < 0 )
    return -1;
  if ( x > 0 )
    return 1;
  return 0;

}
Pos Pos::posSgnm( const Pos & pos ) {
  return Pos( sgnm( pos.x ), sgnm( pos.y ) );
}

Pos Pos::middlePos( const Pos & pos, const Pos & size ) { return pos + Pos ( size.x/2, size.y/2 ); }
Pos Pos::rightBottomPos( const Pos & pos, const Pos & size ) { return pos + Pos( size.x, size.y ); }


bool Pos::intersects( const Pos & pos1, const Pos & dim1, const Pos & pos2, const Pos & dim2 ) {
SDL_Rect rect1;
rect1.x = pos1.x; rect1.y = pos1.y;
rect1.w = dim1.x; rect1.h = dim1.y;
SDL_Rect rect2;
rect2.x = pos2.x; rect2.y = pos2.y;
rect2.w = dim2.x; rect2.h = dim2.y;

return SDL_HasIntersection( &rect1, &rect2 );
}

std::ostream & operator << ( std::ostream & os, const Pos & rhs ) {
  os << "[ " << rhs.x << ", " << rhs.y << " ]";
  return os;
}

Pos::Pos() : x( 0 ), y( 0 ) {}
Pos::Pos( double x, double y ) :x(x), y(y) {}
Pos::Pos( const Pos & rhs ) : x(rhs.x), y(rhs.y) {}
Pos::Pos ( Pos && rhs ) : x( std::move( rhs.x ) ), y( std::move( rhs.y ) ) {}

Pos& Pos::operator += ( const Pos& rhs ) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

Pos& Pos::operator -= ( const Pos& rhs ) {
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}

Pos Pos::operator + ( const Pos& rhs ) const {
  return Pos( x + rhs.x, y + rhs.y );
}

Pos Pos::operator - ( const Pos& rhs ) const {
  return Pos( x - rhs.x, y - rhs.y );
}

bool Pos::operator == ( const Pos & rhs ) const {
  return ( ( x == rhs.x ) && ( y == rhs.y ) );
}

bool Pos::isOutOfBounds( const Pos & pos, const Pos & size ) {
  if ( pos.x < 0 || pos.y < 0 ) return true;
  Pos bottomRight = Pos::rightBottomPos( pos, size );
  if ( bottomRight.x >= Config::g_TileSize * ( Config::g_MapWidth - 1 )
    || bottomRight.y >= Config::g_TileSize * ( Config::g_MapHeight - 1 ) )
    return true;
  return false;
}
