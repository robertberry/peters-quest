#ifndef PETERS_QUEST_ASSET_MANAGER_H_
#define PETERS_QUEST_ASSET_MANAGER_H_

#include <map>
#include <string>
#include <memory>
#include <optional>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace pq {

enum class AssetType { kFont, kTexture, kAnimation, kSound };

struct AssetSpec {
  const int id;
  const AssetType asset_type;
  const std::string path;
  const std::optional<sf::Color> color_mask;
};

struct SpriteRect {
  const int x;
  const int y;
  const int width;
  const int height;
};

struct SpriteSpec {
  const int texture_id;
  const SpriteRect texture_rect;
};

class AssetManager final {
 public:
  explicit AssetManager();

  void loadAsset(const AssetSpec& asset_spec);
  const sf::Font& getFontOrDie(int id) const noexcept;
  const sf::Texture& getTextureOrDie(int id) const noexcept;
  const sf::SoundBuffer& getSoundOrDie(int id) const noexcept;
  const std::unique_ptr<sf::Sprite> newSpriteOrDie(const SpriteSpec& spec) noexcept;

 private:
  std::map<int, sf::Texture> textures_;
  std::map<int, sf::Font> fonts_;
  std::map<int, sf::SoundBuffer> sounds_;
};

}  // namespace pq

#endif PETERS_QUEST_ASSET_MANAGER_H_
