#ifndef PETERS_QUEST_LEVEL_ENTITY_FACTORY_H_
#define PETERS_QUEST_LEVEL_ENTITY_FACTORY_H_

#include "asset_manager.h"
#include "entity_manager.h"

namespace pq {

// Type of entities in the game.
enum class LevelEntityType {
  // The player. The user can control this entity.
  kPlayer,
  // A solid obstacle. The player can stand on this, cannot walk through it.
  kGrayBrick
};

// Spec for constructing an entity for use in the level.
struct LevelEntitySpec {
  // The type of the entity.
  const LevelEntityType type;
  // Its initial x coordinate.
  const int x;
  // Its initial y coordinate.
  const int y;
};

class LevelEntityFactory final {
 public:
  explicit LevelEntityFactory(AssetManager& asset_manager,
                              EntityManager& entity_manager);

  // Creates a new entity for the given spec.
  Entity& newEntity(const LevelEntitySpec& spec);

 private:
  EntityManager& entity_manager_;
  AssetManager& asset_manager_;

  std::unique_ptr<sf::Sprite> spriteForSpec(const LevelEntitySpec& spec);
  EntityTag tagForSpec(const LevelEntitySpec& spec) const;
};

}  // namespace pq

#endif
