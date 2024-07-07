#include "Camera.h"
#include "Config.h"

Camera::Camera( Player * player ) {
  m_Player = player;
  m_Size = Pos ( Config::g_WindowWidth, Config::g_WindowHeight );
  update();
  //setPosByPlayer( m_Player -> getPos(), m_Player -> getSize() );
}

void Camera::update() {
  // We don't want to go out of bounds
  setPosByPlayer( m_Player -> getPos(), m_Player -> getSize() );
  if ( m_Pos.x < 0 ) m_Pos.x = 0;
  if ( m_Pos.y < 0 ) m_Pos.y = 0;
  if ( m_Pos.x > Config::g_TileSize * ( Config::g_MapWidth - 1 ) - Config::g_WindowWidth )
    m_Pos.x = Config::g_TileSize * ( Config::g_MapWidth - 1 ) - Config::g_WindowWidth;
  if ( m_Pos.y > Config::g_TileSize * ( Config::g_MapHeight - 1 ) - Config::g_WindowHeight )
    m_Pos.y =  Config::g_TileSize * ( Config::g_MapHeight - 1 ) - Config::g_WindowHeight;
}
