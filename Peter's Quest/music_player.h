#ifndef PETERS_QUEST_MUSIC_PLAYER_H_
#define PETERS_QUEST_MUSIC_PLAYER_H_

#include <string>

#include "SFML/Audio.hpp"

namespace pq {

constexpr int kMusicRainingBits = 0;

// Singleton for playing music during the game. Note that this is separate from
// asset manager because music files are generally large enough that they should
// be streamed from disk, instead of loaded into memory at start up, as the
// asset manager does.
class MusicPlayer final {
 public:
  // Plays the track with track_id.
  void play(int track_id);

  // Stops the currently playing track.
  void stop();

 private:
  sf::Music music_;

  std::string getFileName(int track_id);
};

}  // namespace pq

#endif  // PETERS_QUEST_MUSIC_PLAYER_H_
