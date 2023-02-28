#include "game_engine.h"

#include <iostream>
#include <memory>
#include <string>

#include "SFML/Graphics.hpp"
#include "asset_manager.h"
#include "game_controls.h"
#include "game_scene.h"

namespace pq {

GameEngine::GameEngine(int maxFps, int width, int height, std::string title)
    : render_window_(sf::VideoMode(width, height), title),
      asset_manager_(),
      is_running_(false),
      max_fps_(maxFps),
      scenes_(),
      active_scene_() {}

void GameEngine::run(size_t initialScene) {
  render_window_.setFramerateLimit(max_fps_);
  is_running_ = true;
  goToScene(initialScene);

  sf::Clock clock;
  while (render_window_.isOpen() && is_running_) {
    sf::Event event;
    while (render_window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        render_window_.close();
      }

      std::optional<UserInputEvent> maybe_event = get_input_event(event);
      if (maybe_event.has_value()) {
        active_scene_->onUserInput(maybe_event.value());
      }
    }

    sf::Time delta = clock.restart();
    if (active_scene_ == nullptr) {
      std::cerr << "No active scene: exiting" << std::endl;
      exit(1);
    }
    render_window_.clear();
    active_scene_->update(render_window_, delta);
    render_window_.display();
  }
}

AssetManager& GameEngine::getAssetManager() { return asset_manager_; }

void GameEngine::addScene(size_t key, std::unique_ptr<GameScene> scene) {
  if (scenes_.size() < key + 1) {
    scenes_.resize(key + 1);
  }
  scenes_[key] = std::move(scene);
}

void GameEngine::goToScene(size_t scene) {
  active_scene_ = scenes_[scene].get();
  active_scene_->onEnter();
}

MusicPlayer& GameEngine::getMusicPlayer() { return music_player_; }

void GameEngine::stop() { is_running_ = false; }

}  // namespace pq
