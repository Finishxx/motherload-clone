#include "Map.h"
#include "MapGenerator.h"
#include <iostream>
#include "TileUndergroundEmpty.h"
#include "Parser.h"
#include "MapParser.h"

const std::string Map::m_FreeSpaceString = "MapFreeSpace";
const std::string Map::m_MapSizeString = "MapSize";

void Map::initNewMap() {
  MapGenerator newMap = MapGenerator();
  m_Map = newMap.getResult();
  m_FreeSpace = newMap.getFreeSpace();
}

Map::Map( Camera * camera, std::string & str ) {
  m_Camera = camera;
  Parser::parseIntIntoFind( str, m_FreeSpaceString, m_FreeSpace );
  MapParser parser = MapParser( str, m_FreeSpace );
  m_Map = parser.getResult();
}

void Map::initNewMap( std::ifstream & is ) {
  MapGenerator newMap = MapGenerator( is );
  m_Map = newMap.getResult();
  m_FreeSpace = newMap.getFreeSpace();
}

void Map::save( std::ofstream & os ) const {
  Parser::save( os, m_FreeSpaceString, std::to_string( m_FreeSpace ) );
  saveMap( os );
}

void Map::saveMap( std::ofstream & os ) const {
  os << "\n" << Config::g_MapStartDelimeter << std::endl;
  for ( int y = m_FreeSpace ; y < Config::g_MapHeight ; y++ ) {
    os << "  ";
    for ( int x = 0 ; x < Config::g_MapWidth; x++ )
      os << m_Map[ x ][ y ] -> getRectID() << " ";
    os << std::endl;
  }
  os << "\n" << Config::g_MapEndDelimeter << std::endl;
}

void Map::draw() const {
  Pos topLeft = Tile::realToSymbolic( m_Camera -> getPos() );
  Pos bottomRight = Tile::realToSymbolic( Pos( m_Camera -> getPos().x + m_Camera -> getSize().x,
                                               m_Camera -> getPos().y + m_Camera -> getSize().y ) ); // we need to "round up"

  for ( int i = topLeft.x ; i <= bottomRight.x ; i++ )
    for ( int j = topLeft.y ; j <= bottomRight.y ; j++ ) {
      m_Map[i][j] -> draw();
    }
}

void Map::printPart( int x, int y, int xEnd, int yEnd ) const {
  for( int i = x ; i < xEnd; x++ ) {
    std::cout << "\n";
    for ( int j = y ; j < yEnd ; j ++ ) {
      if ( m_Map[i][j] -> getRectID() == 6 )
        std::cout << "D";
      else
        std::cout << m_Map[i][j]->getRectID();
    }
  }
  std::cout << std::endl;
}

void Map::mineTile( const Pos & pos ) {
  delete m_Map[pos.x][pos.y];
  m_Map[pos.x][pos.y] = new TileUndergroundEmpty( pos ); 
}

Tile * Map::getTile( const Pos & pos ) { return m_Map[pos.x][pos.y]; }

std::vector<Tile *> Map::getTilesInDir( Pos pos, Pos dir ) const {
  std::vector<Tile *> result;
  if ( dir.x == 0 ) {
    pos += dir;
    for ( int i = pos.x - 1 ; i <= pos.x + 1; i++ ) {
      if ( i >= Config::g_MapWidth || i < 0 || pos.y >= Config::g_MapHeight || pos.y < 0 ) continue;
      result.push_back( m_Map[i][pos.y] );
    }
    return result;
  }
  pos += dir;
  for ( int i = pos.y - 1 ; i <= pos.y + 1 ; i++ ) {
    if ( pos.x >= Config::g_MapWidth || pos.x < 0 || i >= Config::g_MapHeight || i < 0 ) continue;
    result.push_back( m_Map[pos.x][i] );
  }
  return result;
}

void Map::clearMap() {
  for ( int i = 0; i < Config::g_MapWidth; i++ )
    for( int j = 0; j < Config::g_MapHeight; j++ )
      delete m_Map[i][j];
}

Map::~Map() {
  clearMap();
}

