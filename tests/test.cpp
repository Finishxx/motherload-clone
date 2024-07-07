#include "../src/Parser.h"
#include "../src/Pos.h"
#include "../src/Config.h"

#include <assert.h>

// Expecting parserTestData to stay the same
// Expecting Config seperators to be the same
int main ( int argc, char ** argv ) {

  std::ofstream os;
  os.open("testDataGenerated.txt");

  Parser::save( os, "testInt2", std::to_string( 3 ) );
  Parser::save( os, "testDouble2", std::to_string( 3.5 ) );
  Parser::saveBool( os, "testBool2", true );
  Parser::savePos( os, "testPos2", Pos( 4.8, 6.9 ) );

  // parseIntInto
  // expecting no header
  std::ifstream is = std::ifstream( "parserTextData.txt" );
  std::string temp, str;
  for ( std::string temp; std::getline( is, temp ) ; )
    str += temp;

  // there is no test1 in file
  int a = 1;
  assert( Parser::parseIntIntoFind( str, "testInt1", a ) == false
          && a ==1 );
  // value is changed
  int b = 2;
  assert( Parser::parseIntIntoFind( str, "testInt2", b ) == true
          && b == 3 );

  // same double:

  // there is no test1 in file
  double aa = 2.5;
  assert( Parser::parseDoubleIntoFind( str, "testDouble1", aa ) == false
          && aa == 2.5 );
  // value is changed
  double bb = 1.5;
  assert( Parser::parseDoubleIntoFind( str, "testDouble2", bb ) == true
          && bb == 3.5 );
  
  // same pos:

  // there is no test1 in file
  Pos aaa = Pos( 2.5, 5.5 );
  assert( Parser::parsePosIntoFind( str, "testPos1", aaa ) == false
          && aaa == Pos( 2.5, 5.5 ) );
  // value is changed
  Pos bbb = Pos( 3.5, 4.8 );
  assert( Parser::parsePosIntoFind( str, "testPos2", bbb ) == true
          && bbb == Pos( 4.8, 6.9) );
  
  // same bool:
  bool aaaa = true;
  assert( Parser::parseBoolIntoFind( str, "testBool1", aaaa ) == false
          && aaaa == true );
  // value is changed
  bool bbbb = false;
  assert( Parser::parseBoolIntoFind( str, "testBool2", bbbb ) == true
          && bbbb == true );
  is.close();




}