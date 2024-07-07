#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include "Pos.h"
#include "Tile.h"

/**
 * @brief Class that contains static methods for parsing from files and saving into files.
 */
class Parser {

  public:

  static bool parseIntIntoFind ( std::string & str, const std::string & expectedString, int & defaultVal );
  static bool parseDoubleIntoFind ( std::string & str, const std::string & expectedString, double & defaultVal );
  static bool parsePosIntoFind ( std::string & str, const std::string & expectedString, Pos & defaultVal );
  static bool parseBoolIntoFind ( std::string & str, const std::string & expectedString, bool & defaultVal );

  static bool findPos( std::string & str, const std::string & expectedString, size_t & startPos, size_t & endPos );

  static bool save( std::ofstream & os, const std::string & name, const std::string & val );
  static bool saveBool( std::ofstream & os, const std::string & name, bool val );
  static bool savePos( std::ofstream & os, const std::string & name, const Pos & pos );

};

#endif /* PARSER_H */