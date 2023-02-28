#include "entity_manager.h"

namespace pq {

EntityManager::EntityManager() {}

void EntityManager::update() {}

Entity& EntityManager::createEntity() {
  entities_.push_back(std::make_unique<Entity>());
  return *entities_.back().get();
}

std::vector<std::unique_ptr<Entity>>& EntityManager::getEntities() {
  return entities_;
}

Entity* EntityManager::firstEntityWithTag(EntityTag tag) {
  for (std::unique_ptr<Entity>& entity : entities_) {
    if (entity->getEntityTag() == tag) {
      return entity.get();
    }
  }

  return nullptr;
}

void Entity::destroy() { is_alive_ = false; }

Transform& Entity::getTransform() { return transform_; }

sf::Drawable* Entity::getDrawable() {
  if (sprite_.get() != nullptr) {
    return sprite_.get();
  }
  return drawable_.get();
}

sf::Sprite* Entity::getSprite() { return sprite_.get(); }

const AxisAlignedBoundingBox* Entity::getAxisAlignedBoundingBox() const {
  return axis_aligned_bounding_box_.get();
}

bool Entity::getGravity() { return gravity_; }

void Entity::setDrawable(std::unique_ptr<sf::Drawable> drawable) {
  drawable_ = std::move(drawable);
}

void Entity::setSprite(std::unique_ptr<sf::Sprite> sprite) {
  sprite_ = std::move(sprite);
}

void Entity::setEntityTag(EntityTag tag) { tag_ = tag; }

void Entity::setGravity(bool value) { gravity_ = value; }

void Entity::setAxisAlignedBoundingBox(
    std::unique_ptr<AxisAlignedBoundingBox> bounding_box) {
  axis_aligned_bounding_box_ = std::move(bounding_box);
}


EntityTag Entity::getEntityTag() { return tag_; }

Transform::Transform() {}

sf::Vector2f& Transform::getPosition() { return position_; }

sf::Vector2f& Transform::getVelocity() { return velocity_; }

AxisAlignedBoundingBox::AxisAlignedBoundingBox(int width, int height)
    : width_(width), height_(height) {}

int AxisAlignedBoundingBox::getWidth() const { return width_; }

int AxisAlignedBoundingBox::getHeight() const { return height_; }

}  // namespace pq
