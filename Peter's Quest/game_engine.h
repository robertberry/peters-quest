#ifndef PETERS_QUEST_GAME_ENGINE_H_
#define PETERS_QUEST_GAME_ENGINE_H_

#include <memory>
#include <string>
#include <vector>

#include "SFML/Graphics.hpp"
#include "asset_manager.h"
#include "game_scene.h"
#include "music_player.h"
#include "scene_context.h"

namespace pq {

// Responsible for managing all global game state and logic. Local state should
// be managed in a Scene.
class GameEngine final : public SceneContext {
 public:
  explicit GameEngine(int maxFps, int width, int height, std::string title);

  // Starts the game loop.
  void run(size_t initialScene);

  // Returns the asset manager. Can be used to load assets.
  AssetManager& getAssetManager() override;

  // Adds the scene to the Game Engine.
  void addScene(size_t key, std::unique_ptr<GameScene> scene);

  // Goes to the scene with the provided key.
  void goToScene(size_t scene) override;

  // Returns the music player.
  MusicPlayer& getMusicPlayer() override;

  // Stops the game and exits.
  void stop() override;

 private:
  AssetManager asset_manager_;
  sf::RenderWindow render_window_;
  MusicPlayer music_player_;

  bool is_running_;
  int max_fps_;
  std::vector<std::unique_ptr<GameScene>> scenes_;
  GameScene* active_scene_;
};

}  // namespace pq

#endif  // PETERS_QUEST_GAME_ENGINE_H_
