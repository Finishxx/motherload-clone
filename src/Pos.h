#ifndef POS_H
#define POS_H
#include <iostream>


/**
 * @brief Represents position on a grid.
 * 
 */
struct Pos
{
  Pos();
  Pos( double x, double y );
  Pos( const Pos & rhs );
  Pos( Pos && rhs );
  Pos& operator = (const Pos &) = default;
  Pos& operator += ( const Pos & rhs );
  Pos& operator -= ( const Pos & rhs );
  Pos operator + ( const Pos & rhs ) const;
  Pos operator - ( const Pos & rhs ) const;
  bool operator == ( const Pos & rhs) const;
  friend std::ostream & operator << ( std::ostream & os, const Pos & pos );
  
  double x;
  double y;
  /**
   * @brief Return the pos of middle of a rectangle by given top right corner
   */
  static Pos middlePos( const Pos & pos, const Pos & size );
  /**
   * @brief Return the pos of bottom right corner of rectangle
   */
  static Pos rightBottomPos( const Pos & pos, const Pos & size );
  /**
   * @brief Returns true if two rectangles intersect
   */
  static bool intersects( const Pos & pos1, const Pos & dim1, const Pos & pos2, const Pos & dim2 );
  /**
   * @brief returns signum of a number
   */
  static int sgnm( int x );
  /**
   * @brief Returns signum of a Pos
   */
  static Pos posSgnm( const Pos & x );
  /**
   * @brief Returns true if rectangle is out of bounds
   */
  static bool isOutOfBounds( const Pos & pos, const Pos & size );
};

#endif /* POS_H */
