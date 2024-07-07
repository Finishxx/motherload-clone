#include "Graphics.h"
#include "Game.h"

Graphics * Graphics::m_Instance = nullptr;

Graphics * Graphics::getInstance() {
  if ( m_Instance == nullptr )
    m_Instance = new Graphics();
  return m_Instance;
}

void Graphics::drawRect( RectID id, Pos pos, Pos size ) const {
  SDL_Renderer * renderer = Game::getInstance() -> getRenderer();
  SDL_Rect rect;
  rect.x = pos.x; rect.y = pos.y; rect.w = size.x; rect.h = size.y;

  SDL_SetRenderDrawColor( renderer,
                          m_RectColors[id].red,
                          m_RectColors[id].green,
                          m_RectColors[id].blue,
                          m_RectColors[id].alpha );
                          
  SDL_RenderFillRect( renderer, &rect );

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 ); // draw rect border
                          
  SDL_RenderDrawRect( renderer, &rect );
}

void Graphics::drawRectToMap( RectID id, Pos pos, Pos size ) const {
  drawRect( id, pos - m_Camera -> getPos(), size );
}

void Graphics::drawTextMiddleTop( const char * text, Pos pos, Pos size, int offset ) {
  Pos realPos = pos - m_Camera -> getPos(); // real for renderer
  FontHolder current = getFontFromCache( text );

  Pos middlePos = Pos::middlePos( realPos, size );
  Pos textMiddlePos = Pos( middlePos.x, middlePos.y - size.y/2 - offset );
  Pos textRealPos = textMiddlePos - Pos( current.m_Width/2, current.m_Height/2 );

  renderText( current, textRealPos );
}

void Graphics::drawText( const char * text, Pos pos ) {
  FontHolder current = getFontFromCache( text );
  renderText( current, pos );
}

void Graphics::renderText( FontHolder & current, Pos pos ) {
  SDL_Rect srcRect, dstRect;
  srcRect.w = dstRect.w = current.m_Width; srcRect.h = dstRect.h = current.m_Height;
  srcRect.x = 0; srcRect.y = 0;

  dstRect.x = pos.x; dstRect.y = pos.y;
  SDL_RenderCopy( Game::getInstance() -> getRenderer(), current.m_Texture, &srcRect, &dstRect ); 
}

void Graphics::drawTextCached( const char * text, Pos pos ) {
  FontHolder current = getFontFromCache( text );
  renderText( current, pos );
}

Graphics::FontHolder Graphics::getFont( const char * text ) {
  FontHolder result;
  auto it = m_TextMap.find( text );
  if ( it == m_TextMap.end() ) {
    SDL_Surface * toRender = TTF_RenderText_Solid( m_Font, text, m_FontColor );
    SDL_Texture * toDraw = SDL_CreateTextureFromSurface( Game::getInstance() -> getRenderer(), toRender );
    result = m_TextMap.insert( { text, FontHolder( toRender -> w, toRender -> h, toDraw ) } ).first -> second;
    SDL_FreeSurface( toRender );
  } else {
    result = it -> second;
  }
  return result;
}

Graphics::FontHolder Graphics::getFontFromCache( const char * text ) {
  FontHolder result;
  auto it = m_TextCache.find( text );
  if ( it == m_TextCache.end() ) {
    
    if ( m_TextCache.size() >= Config::g_MaxFontCacheSize ) 
      clearMap( m_TextCache );

    SDL_Surface * toRender = TTF_RenderText_Solid( m_Font, text, m_FontColor );
    SDL_Texture * toDraw = SDL_CreateTextureFromSurface( Game::getInstance() -> getRenderer(), toRender );
    result = m_TextCache.insert( { text, FontHolder( toRender -> w, toRender -> h, toDraw ) } ).first -> second;
    SDL_FreeSurface( toRender );
  } else {
    result = it -> second;
  }
  return result;
}

void Graphics::clearMap( std::map<std::string, Graphics::FontHolder> & map ) {
  while( map.size() > 0 ) {
    auto it = map.begin();
    SDL_DestroyTexture( it -> second.m_Texture );
    map.erase( map.begin() );
  }
}

Graphics::~Graphics() {
  TTF_CloseFont( m_Font );
  m_Font = nullptr;
  clearMap( m_TextMap );
  clearMap( m_TextCache );
}

void Graphics::drawTextLeftTop( const char * text, Pos pos, int offset ) { // DOES NOT TAKE CAMERA INTO CONSIDERATION
  FontHolder current = getFontFromCache( text );

  Pos textRealPos = Pos( pos.x - offset - current.m_Width, pos.y );

  renderText( current, textRealPos );
}


const std::array<RectColor, (int)RECT_ID_SIZE> Graphics::m_RectColors = {
  RectColor( 255, 0, 0, 0 ),                                   //ID_PLAYER                   = 0,  // RED
  RectColor( 255, 192, 203, 0 ),                                   //ID_SHOP_REPAIR              = 1,  // 
  RectColor( 246, 239, 233, 0 ),                                   //ID_SHOP_UPGRADE             = 2,  //
  RectColor( 0, 0, 255, 0 ),                                   //ID_EMPTY_OVERWORLD          = 3,  // BLUE
  RectColor( 92,	62,	42, 0 ),                                   //ID_EMPTY_UNDERGROUND        = 4,  // BROWN + BLACK
  RectColor( 0, 0, 0, 0 ),                                   //ID_COAL                     = 5,  // BLACK
  RectColor( 165, 42, 42, 0 ),                                   //ID_DIRT                     = 6,  // BROWN
  RectColor( 165, 156, 148, 0 ),                                   //ID_IRON                     = 7,  // IRONY
  RectColor( 255, 215, 0, 0 ),                                   //ID_GOLD                     = 8,  // GOLD
  RectColor( 124, 252, 0, 0 ),                                   //ID_TITANIUM                 = 9,  // GREEN
  RectColor( 0, 0, 0, 0 ),
  RectColor( 0, 0, 0, 0 ),                                   //ID_BEDROCK                  = 10, // BLACK
  RectColor( 0, 0, 0, 255 ), // EMPTY
  RectColor( 255, 255, 0, 0 ), // ID_FUEL
  RectColor( 255, 0, 0, 0 ) //ID_HEALTH
};
