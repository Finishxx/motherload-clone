#ifndef GAME_SAVER_H
#define GAME_SAVER_H

#include "Player.h"
#include "Camera.h"
#include "Map.h"
#include "MiningHandler.h"
#include "ShopHandler.h"
#include <vector>
#include "Component.h"

/**
 * @brief Saves the current game - i.e. calls save() on all components and prepares the file
 */
class GameSaver {

  public:
  GameSaver( std::vector<Component *> m_Components );
  void saveCurrentTime( const std::string & namePrefix );

  std::vector<Component *> m_Components;
};

#endif /* GAME_SAVER_H */