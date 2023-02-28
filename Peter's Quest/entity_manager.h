#ifndef PETERS_QUEST_ENTITY_MANAGER_H_
#define PETERS_QUEST_ENTITY_MANAGER_H_

#include <memory>
#include <vector>

#include "SFML/Graphics.hpp"

namespace pq {

// Tag for the kinds of entities in the game.
enum class EntityTag {
  // Appears behind the player. Is not interactive.
  kDecor,
  // An obstacle - the player cannot move through this.
  kObstacle,
  // The player. This can be controlled with the keyboard.
  // The player. This can be controlled with the keyboard.
  kPlayer
};

// Transform for an in-game entity. Tracks position and velocity.
class Transform final {
 public:
  explicit Transform();

  sf::Vector2f& getPosition();
  sf::Vector2f& getVelocity();

 private:
  sf::Vector2f position_;
  sf::Vector2f velocity_;
};

// Axis-aligned bounding box for collision detection.
class AxisAlignedBoundingBox final {
 public:
  explicit AxisAlignedBoundingBox(int width, int height);

  int getWidth() const;
  int getHeight() const;

 private:
  const int width_;
  const int height_;
};

// An in-game entity. Can be anything from some background art to the player.
class Entity final {
 public:
  // Destroys the entity. It will be removed from the game in the following
  // frame.
  void destroy();

  // Returns the transform of the entity.
  Transform& getTransform();

  // Returns a Drawable for entities that should be rendered. Null for
  // non-renderable entities.
  sf::Drawable* getDrawable();

  // Returns the attached Sprite, if one exists. Otherwise nullptr.
  sf::Sprite* getSprite();

  // Returns the axis-aligned bounding box for collision detection, if one exists.
  const AxisAlignedBoundingBox* getAxisAlignedBoundingBox() const;

  bool getGravity();

  // Sets the drawable. See getDrawable.
  void setDrawable(std::unique_ptr<sf::Drawable> drawable);

  // Sets the sprite. See getDrawable.
  void setSprite(std::unique_ptr<sf::Sprite> sprite);

  // Sets the entity tag.
  void setEntityTag(EntityTag tag);

  // Sets whether gravity affects the Entity.
  void setGravity(bool value);

  // Sets the axis-aligned bounding box for collision detection.
  void setAxisAlignedBoundingBox(std::unique_ptr<AxisAlignedBoundingBox> bounding_box);

  // Returns the entity tag for the entity. This determines behavior.
  EntityTag getEntityTag();

  friend class EntityManager;

 private:
  EntityTag tag_;
  bool is_alive_;
  Transform transform_;
  std::unique_ptr<sf::Drawable> drawable_;
  std::unique_ptr<sf::Sprite> sprite_;
  std::unique_ptr<AxisAlignedBoundingBox> axis_aligned_bounding_box_;
  bool gravity_;
};

// Manages entities in the scene.
class EntityManager final {
 public:
  explicit EntityManager();

  // This should be called every frame. Removes any dead entities and inserts
  // any newly alive entities.
  void update();

  // Creates a new entity. It will be added into the scene in the following
  // frame.
  Entity& createEntity();

  // Returns all entities in the scene.
  std::vector<std::unique_ptr<Entity>>& getEntities();

  // Returns the first entity with the given entity tag, or nullptr if none is
  // found.
  Entity* firstEntityWithTag(EntityTag tag);

 private:
  std::vector<std::unique_ptr<Entity>> entities_;
};

}  // namespace pq

#endif  // PETERS_QUEST_ENTITY_MANAGER_H_
