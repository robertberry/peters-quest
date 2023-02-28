#ifndef PETERS_QUEST_PLAY_SCENE_H_
#define PETERS_QUEST_PLAY_SCENE_H_

#include "entity_manager.h"
#include "game_scene.h"
#include "scene_context.h"

namespace pq {

// The main scene for playing the game.
class PlayScene final : public GameScene {
 public:
  explicit PlayScene(SceneContext& scene_context);

  void onEnter() override;

  void update(sf::RenderWindow& window, const sf::Time& delta) override;

  void onUserInput(UserInputEvent user_input_event) override;

 private:
  SceneContext& scene_context_;
  EntityManager entity_manager_;

  void systemControls();
  void systemPhysics(const sf::Time& delta);
  void systemCollisionDetection(const sf::Time& delta);
  void systemRender(sf::RenderWindow& window);
};

}  // namespace pq

#endif  // PETERS_QUEST_PLAY_SCENE_H_
