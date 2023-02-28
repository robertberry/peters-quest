#include "asset_manager.h"

#include <iostream>

#include "SFML/Graphics.hpp"

namespace pq {

AssetManager::AssetManager() : textures_(), fonts_(), sounds_() {}

void AssetManager::loadAsset(const AssetSpec& asset_spec) {
  switch (asset_spec.asset_type) {
    case AssetType::kFont: {
      sf::Font font;
      if (!font.loadFromFile(asset_spec.path)) {
        std::cerr << "Could not load font from " << asset_spec.path
                  << std::endl;
        exit(1);
      }
      fonts_[asset_spec.id] = std::move(font);
      break;
    }

    case AssetType::kTexture: {
      sf::Image image;
      if (!image.loadFromFile(asset_spec.path)) {
        std::cerr << "Could not load texture from " << asset_spec.path
                  << std::endl;
        exit(1);
      }
      if (asset_spec.color_mask.has_value()) {
        const sf::Color& mask = asset_spec.color_mask.value();
        std::cout << "Masking " << asset_spec.path << " with color " << mask.r
                  << ", " << mask.g << ", " << mask.b << ", " << mask.a
                  << std::endl;
        image.createMaskFromColor(mask, /*alpha=*/ 0);
      }

      sf::Texture texture;
      if (!texture.loadFromImage(image)) {
        std::cerr << "Could not load texture from image" << std::endl;
        exit(1);
      }

      textures_[asset_spec.id] = std::move(texture);
      break;
    }

    case AssetType::kSound: {
      sf::SoundBuffer sound;
      if (!sound.loadFromFile(asset_spec.path)) {
        std::cerr << "Could not load sound from " << asset_spec.path
                  << std::endl;
        exit(1);
      }
      sounds_[asset_spec.id] = std::move(sound);
      break;
    }

    case AssetType::kAnimation:
      // TODO(rob): Add loading for animations.
      break;
  }
}

const sf::Font& AssetManager::getFontOrDie(int id) const noexcept {
  return fonts_.at(id);
}

const sf::Texture& AssetManager::getTextureOrDie(int id) const noexcept {
  return textures_.at(id);
}

const sf::SoundBuffer& AssetManager::getSoundOrDie(int id) const noexcept {
  return sounds_.at(id);
}

const std::unique_ptr<sf::Sprite> AssetManager::newSpriteOrDie(
    const SpriteSpec& spec) noexcept {
  const sf::Texture& texture = getTextureOrDie(spec.texture_id);
  std::unique_ptr<sf::Sprite> sprite = std::make_unique<sf::Sprite>(texture);
  auto rect = spec.texture_rect;
  sprite->setTextureRect(sf::IntRect(rect.x, rect.y, rect.width, rect.height));
  return sprite;
}

}  // namespace pq
