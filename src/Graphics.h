#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL2/SDL.h"
#include <array>
#include "RectColor.h"
#include "RectID.h"
#include "SDL2/SDL_ttf.h"
#include <map>
#include "Pos.h"
#include "Config.h"
#include "Camera.h"

/**
 * @brief Implemented as a singleton. Draws rectangles and text
 */
class Graphics {

  public:
  static Graphics * getInstance();
  /**
   * @brief Draws a rectangle with size at pos
   */
  void drawRect( RectID id, Pos pos, Pos size ) const;
  /**
   * @brief Draws rect using realPos on map.
   * 
   * In essence calls drawRect and calculates where on screen the rect should be drawn.
   */
  void drawRectToMap( RectID id, Pos pos, Pos size ) const;
  /**
   * @brief Draws text offset pixels on top a rectangle with given pos and size 
   */
  void drawTextMiddleTop( const char * text, Pos pos, Pos size, int offset );
  /**
   * @brief Draws text offset pixels left of a rectangle with given pos and size
   */
  void drawTextLeftTop( const char * text, Pos pos, int offset );
  /**
   * @brief Draws text at pos ( left top point )
   */
  void drawText( const char * text, Pos pos );
  /**
   * @brief Draws text at pos, but stores the text in a cache that clears itself
   */
  void drawTextCached( const char * text, Pos pos );
  /**
   * @brief Clears font and fontMaps
   */
  ~Graphics();

  void init( Camera * camera ) { m_Camera = camera; }

  private:
   /**
   * @brief Holds a texture and width-height of a text
   * 
   * Inspired by book SDL Game Development.
   */
  struct FontHolder
  {
  FontHolder( int width, int height, SDL_Texture * texture )
              : m_Width( width ), m_Height( height ), m_Texture( texture ) {}
  FontHolder() = default;
  int m_Width;
  int m_Height;
  SDL_Texture * m_Texture;
  };

  /**
   * @brief Renders text at pos
   */
  void renderText( FontHolder & current, Pos pos );
  /**
   * @brief Searches m_TextMap for a text. Creates it if not present
   */
  FontHolder getFont( const char * text );
  /**
   * @brief Searches m_TextCache for a text. Cleans it if it is full. Creates it if not present.
   */
  FontHolder getFontFromCache( const char * text );
  /**
   * @brief Clears a FontMap
   */
  void clearMap( std::map<std::string, FontHolder> & map );
  Graphics() { m_Font = TTF_OpenFont( Config::g_Font, Config::g_FontSize ); }

  static Graphics * m_Instance;
  static const std::array<RectColor, RECT_ID_SIZE> m_RectColors;
  Camera * m_Camera;
  static SDL_Color constexpr m_FontColor = { 255, 255, 255 };

  std::map<std::string, FontHolder> m_TextMap;
  std::map<std::string, FontHolder> m_TextCache;
  TTF_Font * m_Font;
};

#endif /* GRAPHICS_H */