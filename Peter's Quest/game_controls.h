#ifndef PETERS_QUEST_GAME_CONTROLS_H_
#define PETERS_QUEST_GAME_CONTROLS_H_

#include <optional>

#include "SFML/Graphics.hpp"

namespace pq {

// A key as used in the game.
enum class GameKey {
  // The up key.
  kUp,
  // The down key.
  kDown,
  // The left key.
  kLeft,
  // The right key.
  kRight,
  // The action key.
  kAction,
  // The back key.
  kBack
};

// A type of event for a key.
enum class KeyEventType {
  // The key was pressed.
  kPressed,
  // The key was released.
  kReleased
};

// A game key event. Emitted when the user presses or releases a key that is
// useful in the game.
struct UserInputEvent {
  GameKey key;
  KeyEventType event_type;
};

// Given an sf::Keyboard code returns the game key equivalent. This gives us an
// abstraction layer between the physical keyboard and the game key events we
// care about, making it easier to change the controls in the future. i.e., they
// only need to change in one place, this file.
inline std::optional<GameKey> get_game_key(int code) {
  switch (code) {
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
      return GameKey::kUp;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
      return GameKey::kUp;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
      return GameKey::kLeft;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
      return GameKey::kRight;

    case sf::Keyboard::Space:
    case sf::Keyboard::Enter:
      return GameKey::kAction;

    case sf::Keyboard::Escape:
      return GameKey::kBack;
  }

  return {};
}

// Converts an SFML event into a game user input event. If the event is not
// relevant, returns an empty optional.
inline std::optional<UserInputEvent> get_input_event(
    const sf::Event& sfml_event) {
  if (sfml_event.type == sf::Event::KeyPressed) {
    std::optional<GameKey> maybe_key = get_game_key(sfml_event.key.code);
    if (!maybe_key.has_value()) {
      return {};
    }
    return {{maybe_key.value(), KeyEventType::kPressed}};
  } else if (sfml_event.type == sf::Event::KeyReleased) {
    std::optional<GameKey> maybe_key = get_game_key(sfml_event.key.code);
    if (!maybe_key.has_value()) {
      return {};
    }
    return {{maybe_key.value(), KeyEventType::kReleased}};
  } else {
    return {};
  }
}

}  // namespace pq

#endif  // PETERS_QUEST_GAME_CONTROLS_H_
