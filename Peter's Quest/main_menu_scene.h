#ifndef PETERS_QUEST_MAIN_MENU_SCENE_H_
#define PETERS_QUEST_MAIN_MENU_SCENE_H_

#include <string>
#include <vector>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "asset_manager.h"
#include "entity_manager.h"
#include "game_controls.h"
#include "game_scene.h"
#include "scene_context.h"

namespace pq {

enum class MenuOption { kNewGame, kQuit };

struct MenuItem {
  MenuOption option;
  Entity& entity;
};

class MainMenuScene final : public GameScene {
 public:
  explicit MainMenuScene(SceneContext& scene_context,
                         const AssetManager& asset_manager);

  void onEnter() override;

  void update(sf::RenderWindow& window, const sf::Time& delta) override;

  void onUserInput(UserInputEvent user_input_event) override;

 private:
  void addMenuItem(MenuOption option, std::string name);
  void setSelectedIndex(int index);
  void setMenuItemColor(MenuItem& menu_item, sf::Color color);

  int selected_menu_index_ = 0;
  int next_menu_item_ = 0;
  const AssetManager& asset_manager_;
  SceneContext& scene_context_;

  EntityManager entity_manager_;
  std::vector<MenuItem> menu_items_;

  sf::Sound menu_sound_;
};

}  // namespace pq

#endif  // PETERS_QUEST_MAIN_MENU_SCENE_H_
