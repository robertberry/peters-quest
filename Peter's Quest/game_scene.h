#ifndef PETERS_QUEST_GAME_SCENE_H_
#define PETERS_QUEST_GAME_SCENE_H_

#include "SFML/Graphics.hpp"
#include "game_controls.h"

namespace pq {

// Abstract base class for game scenes. Implementing classes will be
// responsible for the logic specific to a given scene - e.g., a menu or a
// level in the game.
class GameScene {
 public:

  // Logic invoked on entering the scene.
  virtual void onEnter() = 0;

  // Invoked once per frame. The scene should perform its update logic.
  virtual void update(sf::RenderWindow& window, const sf::Time& delta) = 0;

  // Invoked on relevant user input.
  virtual void onUserInput(UserInputEvent user_input_event) = 0;
};

}  // namespace pq

#endif  // PETERS_QUEST_GAME_SCENE_H_
