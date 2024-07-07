#include "Parser.h"
#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


bool Parser::parseIntIntoFind ( std::string & str, const std::string & expectedString, int & defaultVal ) {
  size_t startPos, endPos;
  if ( ! findPos( str, expectedString, startPos, endPos ) )
    return false;
  std::string num = str.substr( startPos, endPos - startPos );
  defaultVal = std::stoi( num );
  #ifdef DEBUG
  std::cout << "SubstrInt: " << num << std::endl;
  std::cout << "ResultingValueInt: " << defaultVal << std::endl;
  #endif
  return true;
}

bool Parser::findPos( std::string & str, const std::string & expectedString, size_t & startPos, size_t & endPos ) {
  size_t pos;
  
  if ( ( pos = str.find( expectedString ) ) == std::string::npos )
    return false; // nothing has been found
  startPos = str.find( Config::g_CategoryDelimeter, pos );
  endPos = str.find( Config::g_EndOfLineDelimeter, pos );
  if ( startPos == std::string::npos || endPos == std::string::npos )
    return false;
  startPos++; endPos--;
  return true;
}

bool Parser::parseDoubleIntoFind ( std::string & str, const std::string & expectedString, double & defaultVal ) {
  size_t startPos, endPos;
  if ( ! findPos( str, expectedString, startPos, endPos ) )
    return false;
  std::string num = str.substr( startPos, endPos - startPos );
  defaultVal = std::stod( num );
  #ifdef DEBUG
  std::cout << "SubstrDouble: " << num << std::endl;
  std::cout << "ResultingValueDouble: " << defaultVal << std::endl;
  #endif
  return true;
}

bool Parser::parsePosIntoFind ( std::string & str, const std::string & expectedString, Pos & defaultVal ) {
  size_t startPos, endPos;
  if ( ! findPos( str, expectedString, startPos, endPos ) )
    return false;
  size_t middlePos = str.find( Config::g_PosDelimeter, startPos );
  if ( middlePos == std::string::npos )
    return false;
  
  std::string first = str.substr( startPos, middlePos - startPos - 1 );
  std::string second = str.substr( middlePos + 1, endPos - middlePos - 1 );
  #ifdef DEBUG
  std::cout << "StartPos " << startPos << " , MiddlePos: " << middlePos << " EndPos: " << endPos << std::endl;
  std::cout << "parsePosIntoPos: Pos( " << first << " , " << second << " )" << std::endl;
  #endif
  defaultVal = Pos( std::stoi( first ), std::stoi( second ) );
  return true;
}

bool Parser::parseBoolIntoFind ( std::string & str, const std::string & expectedString, bool & defaultVal ) {
  size_t startPos, endPos;
  if ( ! findPos ( str, expectedString, startPos, endPos ) )
    return false;
  std::string boolean = str.substr( startPos, endPos - startPos );
  #ifdef DEBUG
  std::cout << "BooleanParsingSubstr: " << boolean << std::endl;
  std::cout << "BooleanParsingTrueFind: " << boolean.find( Config::g_True ) << std::endl;
  std::cout << "BooleanParsingTrueFind: " << boolean.find( Config::g_False ) << std::endl;
  #endif

  if ( boolean.find( Config::g_True ) < std::string::npos ) {
    defaultVal = true;
    return true;
  } else if ( boolean.find( Config::g_False < std::string::npos ) ) {
    defaultVal = false;
    return true;
  }
  return false;
}

bool Parser::save( std::ofstream & os, const std::string & name, const std::string & val ) {
  if ( os )
    os << name << Config::g_CategoryDelimeter << " " << val << " " << Config::g_EndOfLineDelimeter << std::endl;
  else
    return false;
  if ( os ) return true; else return false;
}

bool Parser::saveBool( std::ofstream & os, const std::string & name, bool val ) {
  return save( os, name, val ? std::string( 1, Config::g_True ) : std::string( 1 , Config::g_False ) );
}

bool Parser::savePos( std::ofstream & os, const std::string & name, const Pos & pos ) {
  return save( os, name, std::to_string( pos.x ) + " " + Config::g_PosDelimeter + " " + std::to_string( pos.y ) );
}
