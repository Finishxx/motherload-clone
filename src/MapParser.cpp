#include "MapParser.h"

#include "Parser.h"
#include "Pos.h"
#include "TileDirt.h"
#include "TileEmpty.h"
#include "TileCoal.h"
#include "TileUndergroundEmpty.h"
#include "TileIron.h"
#include "TileGold.h"
#include "TileTitanium.h"
#include <sstream>
#include <string>

void MapParser::createFreeSpace( int freeSpace ) {
  for ( int i = 0 ; i < Config::g_MapWidth ; i++ )
    for ( int j = 0 ; j < freeSpace ; j++ )
      m_Result[ i ][ j ] = new TileEmpty( Pos ( i, j ) );
}

MapParser::MapParser( std::string & str, int freeSpace ) {
  createFreeSpace( freeSpace );

  size_t startPos = str.find( Config::g_MapStartDelimeter );
  size_t endPos = str.find( Config::g_MapEndDelimeter );
  std::string mapSubstr = str.substr( startPos + 1 , endPos - 1 - startPos );
  std::istringstream strStrm = std::istringstream( mapSubstr );
    for ( int x = 0, y = freeSpace, id;
        ( ! strStrm.eof() ) && ! ( y >= Config::g_MapHeight );
        x >= Config::g_MapWidth - 1 ? x = 0 : x++ , x == 0 ? y++ : y ) { // load nextID, rest x if need be, if reseted y++
      strStrm >> id;
      if ( strStrm.eof() ) break;
      if ( id >= RectID::RECT_ID_SIZE || id < 0 ) throw std::logic_error( "MapParser::ParsingTileID:: There is no Tile like this!!!" );
      parseNewTile( static_cast<RectID>( id ), x, y );
    }
}

void MapParser::parseNewTile( RectID id, int x, int y ) {
  switch ( id ) {
    case ID_EMPTY:
    m_Result[ x ][ y ] = new TileEmpty( Pos( x, y ) );
    return;
    case ID_UNDERGROUND_EMPTY:
    m_Result[ x ][ y ] = new TileUndergroundEmpty( Pos ( x, y ) );
    return;
    case ID_DIRT:
    m_Result[ x ][ y ] = new TileDirt( Pos ( x, y ) );
    return;
    case ID_COAL:
    m_Result[ x ][ y ] = new TileCoal( Pos( x, y ) );
    return;
    case ID_IRON:
    m_Result[ x ][ y ] = new TileIron( Pos( x, y ) );
    return;
    case ID_GOLD:
    m_Result[ x ][ y ] = new TileGold( Pos( x, y ) );
    return;
    case ID_TITANIUM:
    m_Result[ x ][ y ] = new TileTitanium( Pos( x, y ) );
    return;
    default:
    throw std::logic_error( "MapParser::ParseNewTile: Invalid tile!!" );
  }
}

std::array<std::array<Tile*,Config::g_MapHeight>,Config::g_MapWidth> MapParser::getResult() {
  return m_Result;
}