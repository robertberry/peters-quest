#include "play_scene.h"

import std;

#include "asset_manager.h"
#include "assets.h"
#include "level_entity_factory.h"
#include "level_loader.h"
#include "music_player.h"

constexpr float kVelocityPixelsPerSecond = 500.0f;
constexpr float kTerminalVelocityPixelsPerSecond = 4000.0f;
constexpr float kGravity = 1000.0f;

namespace pq {

PlayScene::PlayScene(SceneContext& scene_context)
    : scene_context_(scene_context), entity_manager_() {
  AssetManager& asset_manager = scene_context_.getAssetManager();
  auto entity_factory =
      LevelEntityFactory(asset_manager, entity_manager_);
  auto level_loader = LevelLoader();
  const std::vector<LevelEntitySpec> entity_specs =
      level_loader.loadLevelOrDie("levels/level1.txt");
  for (const auto& entity_spec : entity_specs) {
    entity_factory.newEntity(entity_spec);
  }
}

void PlayScene::onEnter() {
  scene_context_.getMusicPlayer().play(kMusicRainingBits);
}

void PlayScene::update(sf::RenderWindow& window, const sf::Time& delta) {
  systemPhysics(delta);
  systemCollisionDetection(delta);
  systemRender(window);
}

void PlayScene::onUserInput(UserInputEvent user_input_event) {
  Entity* player = entity_manager_.firstEntityWithTag(EntityTag::kPlayer);
  if (player == nullptr) {
    // TODO(rob): Should this exit?
    std::cout << "nullptr player?" << std::endl;
    return;
  }
  sf::Vector2f& velocity = player->getTransform().getVelocity();

  GameKey key = user_input_event.key;
  KeyEventType event_type = user_input_event.event_type;
  if (key == GameKey::kLeft) {
    if (event_type == KeyEventType::kPressed) {
      velocity.x = -kVelocityPixelsPerSecond;
    } else if (velocity.x == -kVelocityPixelsPerSecond) {
      velocity.x = 0;
    }
  } else if (key == GameKey::kRight) {
    if (event_type == KeyEventType::kPressed) {
      velocity.x = kVelocityPixelsPerSecond;
    } else if (velocity.x == kVelocityPixelsPerSecond) {
      velocity.x = 0;
    }
  }
}

void PlayScene::systemControls() {}

void PlayScene::systemPhysics(const sf::Time& delta) {
  float seconds_passed = delta.asSeconds();
  auto zero_vector = sf::Vector2f(0.0f, 0.0f);
  for (std::unique_ptr<Entity>& entity : entity_manager_.getEntities()) {
    Transform& transform = entity->getTransform();
    sf::Vector2f& velocity = transform.getVelocity();
    if (velocity == zero_vector && !entity->getGravity()) {
      continue;
    }
    sf::Vector2f& position = transform.getPosition();
    std::cout << "current position (" << position.x << ", " << position.y
              << ")" << std::endl;
    position += (velocity * seconds_passed);
    std::cout << "new position (" << position.x << ", " << position.y << ")"
              << std::endl;
    if (entity->getGravity()) {
      float velocity_delta = kGravity * seconds_passed;
      std::cout << "Velocity delta " << velocity_delta << std::endl;
      velocity.y = std::min(velocity.y + velocity_delta,
                            kTerminalVelocityPixelsPerSecond);
    }

    sf::Sprite* sprite = entity->getSprite();
    if (sprite != nullptr) {
      sprite->setPosition(position);
    }
  }
}

void PlayScene::systemCollisionDetection(const sf::Time& delta) {}

void PlayScene::systemRender(sf::RenderWindow& window) {
  for (std::unique_ptr<Entity>& entity :
       entity_manager_.getEntities()) {
    sf::Drawable* drawable = entity->getDrawable();
    if (drawable == nullptr) {
      continue;
    }
    window.draw(*drawable);
  }
}

}  // namespace pq
