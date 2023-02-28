#include <memory>
#include <string>

#include "SFML/Graphics.hpp"
#include "asset_manager.h"
#include "assets.h"
#include "constants.h"
#include "game_engine.h"
#include "main_menu_scene.h"
#include "play_scene.h"

using ::pq::AssetSpec;
using ::pq::GameEngine;
using ::pq::GameScene;
using ::pq::MainMenuScene;
using ::pq::PlayScene;
using ::pq::PQScenes;

const int kMaxFps = 144;
const std::string kGameTitle = "Peter's Quest";

int main(int argc, char* argv[]) {
  GameEngine game(kMaxFps, pq::kWindowWidthPixels, pq::kWindowHeightPixels,
                  kGameTitle);

  pq::AssetManager& asset_manager = game.getAssetManager();
  for (const AssetSpec& asset_spec : pq::kAssetSpecs) {
    asset_manager.loadAsset(asset_spec);
  }

  std::unique_ptr<GameScene> main_menu_scene =
      std::make_unique<MainMenuScene>(game, asset_manager);
  game.addScene((size_t)PQScenes::kMainMenu, std::move(main_menu_scene));

  std::unique_ptr<GameScene> play_scene = std::make_unique<PlayScene>(game);
  game.addScene((size_t)PQScenes::kPlayScene, std::move(play_scene));

  game.run((size_t)PQScenes::kMainMenu);
  return 0;
}
