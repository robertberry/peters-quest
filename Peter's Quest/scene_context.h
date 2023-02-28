#ifndef PETERS_QUEST_SCENE_CONTEXT_H_
#define PETERS_QUEST_SCENE_CONTEXT_H_

#include "asset_manager.h"
#include "music_player.h"

namespace pq {

// Interface passed to scenes for interacting with the Game Engine.
class SceneContext {
 public:
  // Goes to the scene with the provided key.
  virtual void goToScene(size_t scene) = 0;

  // Stops the game and exits.
  virtual void stop() = 0;

  // Returns the music player.
  virtual MusicPlayer& getMusicPlayer() = 0;

  // Returns the asset manager. Can be used to load assets.
  virtual AssetManager& getAssetManager() = 0;
};

}  // namespace pq

#endif  // PETERS_QUEST_SCENE_CONTEXT_H_
