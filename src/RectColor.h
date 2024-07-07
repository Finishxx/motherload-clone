#ifndef RECT_COLOR_H
#define RECT_COLOR_H
/**
 * @brief Hold information of color rgba
 */
struct RectColor
{
  RectColor( int red, int green, int blue, int alpha );
  int red;
  int green;
  int blue;
  int alpha;
};

#endif /* RECT_COLOR_H */