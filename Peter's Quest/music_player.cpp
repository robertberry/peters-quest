#include "music_player.h"

#include <iostream>
#include <string>

namespace pq {

void MusicPlayer::play(int track_id) {
  std::string file_name = getFileName(track_id);
  if (!music_.openFromFile(file_name)) {
    std::cerr << "Could not open track with file name '" << file_name << "'"
              << std::endl;
    exit(1);
  }
  music_.play();
}

void MusicPlayer::stop() { music_.stop(); }

std::string MusicPlayer::getFileName(int track_id) {
  switch (track_id) {
    case kMusicRainingBits:
      return "sounds/RainingBits.ogg";

    default:
      std::cerr << "Could not find file name for track " << track_id
                << std::endl;
      exit(1);
  }
}

}  // namespace pq
