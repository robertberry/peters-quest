#include "main_menu_scene.h"

#include <cmath>
#include <iostream>
#include <memory>

#include "SFML/Graphics.hpp"
#include "asset_manager.h"
#include "assets.h"
#include "constants.h"
#include "entity_manager.h"
#include "scene_context.h"

namespace pq {

const int kMenuItemFontSize = 36;
const int kMenuTopPixels = kWindowHeightPixels / 2;
const int kMenuItemSizePixels = 50;

MainMenuScene::MainMenuScene(SceneContext& scene_context,
                             const AssetManager& asset_manager)
    : GameScene(),
      scene_context_(scene_context),
      asset_manager_(asset_manager),
      entity_manager_() {
  const sf::Font& font = asset_manager_.getFontOrDie(kFontOleaguid);
  std::unique_ptr<sf::Text> title = std::make_unique<sf::Text>();
  title->setFont(font);
  title->setCharacterSize(48);
  title->setString("Peter's Quest");
  title->setPosition(sf::Vector2f(/*x=*/30, /*y=*/10));
  entity_manager_.createEntity().setDrawable(std::move(title));

  const sf::Texture& texture =
      asset_manager_.getTextureOrDie(kTexturePeterBigPicture);
  std::unique_ptr<sf::Sprite> title_picture = std::make_unique<sf::Sprite>();
  title_picture->setTexture(texture);
  title_picture->setPosition(
      /*x=*/kWindowWidthPixels - texture.getSize().x - 40,
      /*y=*/40);
  entity_manager_.createEntity().setDrawable(std::move(title_picture));

  addMenuItem(MenuOption::kNewGame, "New Game");
  addMenuItem(MenuOption::kQuit, "Quit");

  const sf::SoundBuffer& buffer =
      asset_manager.getSoundOrDie(kSoundEffectMenu);
  menu_sound_.setBuffer(buffer);
}

void MainMenuScene::onEnter() {}

void MainMenuScene::update(sf::RenderWindow& window, const sf::Time& delta) {
  for (std::unique_ptr<Entity>& entity :
       entity_manager_.getEntities()) {
    sf::Drawable* drawable = entity->getDrawable();
    if (drawable == nullptr) {
      continue;
    }
    window.draw(*drawable);
  }
}

void MainMenuScene::onUserInput(UserInputEvent user_input_event) {
  if (user_input_event.event_type != KeyEventType::kReleased) {
    return;
  }
  GameKey key = user_input_event.key;
  if (key == GameKey::kDown) {
    setSelectedIndex((selected_menu_index_ + 1) % next_menu_item_);
    menu_sound_.play();
  } else if (key == GameKey::kUp) {
    setSelectedIndex(std::abs((selected_menu_index_ - 1) % next_menu_item_));
    menu_sound_.play();
  } else if (key == GameKey::kAction) {
    menu_sound_.play();
    std::cout << "Selected menu item " << selected_menu_index_ << std::endl;
    if (selected_menu_index_ == static_cast<int>(MenuOption::kNewGame)) {
      scene_context_.goToScene(
          static_cast<size_t>(PQScenes::kPlayScene));
    } else if (selected_menu_index_ == static_cast<int>(MenuOption::kQuit)) {
      scene_context_.stop();
    }
  }
}

void MainMenuScene::addMenuItem(MenuOption option, std::string name) {
  int index = next_menu_item_++;
  const sf::Font& font = asset_manager_.getFontOrDie(kFontOleaguid);
  std::unique_ptr<sf::Text> menu_item_text = std::make_unique<sf::Text>();
  menu_item_text->setFont(font);
  menu_item_text->setCharacterSize(kMenuItemFontSize);
  menu_item_text->setString(name);
  menu_item_text->setPosition(
      /*x=*/50, /*y=*/kMenuTopPixels + index * kMenuItemSizePixels);
  if (index == selected_menu_index_) {
    menu_item_text->setFillColor(sf::Color::Green);
  }
  Entity& entity = entity_manager_.createEntity();
  entity.setDrawable(std::move(menu_item_text));

  menu_items_.push_back({option, entity});
}

void MainMenuScene::setSelectedIndex(int index) {
  setMenuItemColor(menu_items_[selected_menu_index_], sf::Color::White);
  setMenuItemColor(menu_items_[index], sf::Color::Green);
  selected_menu_index_ = index;
}

void MainMenuScene::setMenuItemColor(MenuItem& menu_item, sf::Color color) {
  sf::Drawable* drawable = menu_item.entity.getDrawable();
  sf::Text* text = static_cast<sf::Text*>(drawable);
  text->setFillColor(color);
}

}  // namespace pq
