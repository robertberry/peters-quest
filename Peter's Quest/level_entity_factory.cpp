#include "level_entity_factory.h"

#include <iostream>
#include <memory>

#include "assets.h"

namespace pq {

const int kGridSquareSizePixels = 16;
const int kSpriteScale = 4.0f;

LevelEntityFactory::LevelEntityFactory(AssetManager& asset_manager,
                                       EntityManager& entity_manager)
    : asset_manager_(asset_manager), entity_manager_(entity_manager) {}

Entity& LevelEntityFactory::newEntity(const LevelEntitySpec& spec) {
  std::unique_ptr<sf::Sprite> sprite = spriteForSpec(spec);
  sprite->setScale(sf::Vector2f(kSpriteScale, kSpriteScale));
  Entity& entity = entity_manager_.createEntity();
  sf::Vector2i position =
      sf::Vector2i(spec.x, spec.y) * kGridSquareSizePixels * kSpriteScale;
  sf::Vector2f& transform_position = entity.getTransform().getPosition();
  transform_position.x = position.x;
  transform_position.y = position.y;
  // TODO(robertberry): It is annoying having to keep Sprite and Transform
  // synced.
  sprite->setPosition(transform_position);
  std::cout << "Adding sprite at (" << transform_position.x << ","
            << transform_position.y << ")" << std::endl;
  sf::FloatRect local_bounds = sprite->getLocalBounds();
  entity.setAxisAlignedBoundingBox(std::make_unique<AxisAlignedBoundingBox>(
      /*width=*/local_bounds.width, /*height=*/local_bounds.height));
  entity.setSprite(std::move(sprite));
  EntityTag tag = tagForSpec(spec);
  entity.setEntityTag(tag);
  if (tag == EntityTag::kPlayer) {
    entity.setGravity(true);
  }
  return entity;
}

std::unique_ptr<sf::Sprite> LevelEntityFactory::spriteForSpec(
    const LevelEntitySpec& spec) {
  switch (spec.type) {
    case LevelEntityType::kGrayBrick:
      return asset_manager_.newSpriteOrDie(kSpriteSpecBrick1);
      break;

    case LevelEntityType::kPlayer:
      return asset_manager_.newSpriteOrDie(kSpriteSpecPlayer);

    default:
      std::cerr << "Unknown level entity type in spec" << std::endl;
      exit(1);
  }
}

EntityTag LevelEntityFactory::tagForSpec(const LevelEntitySpec& spec) const {
  switch (spec.type) {
    case LevelEntityType::kGrayBrick:
      return EntityTag::kObstacle;

    case LevelEntityType::kPlayer:
      return EntityTag::kPlayer;

    default:
      return EntityTag::kDecor;
  }
}

}  // namespace pq
