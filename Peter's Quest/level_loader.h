#ifndef PETERS_QUEST_LEVEL_LOADER_H_
#define PETERS_QUEST_LEVEL_LOADER_H_

#include <string>
#include <string_view>;
#include <vector>

#include "level_entity_factory.h"

namespace pq {

// Loads levels from text files.
class LevelLoader final {
 public:
  explicit LevelLoader() {}

  // Loadsa the level from the given text file path.
  std::vector<LevelEntitySpec> loadLevelOrDie(std::string path) const noexcept;

 private:
  LevelEntityType typeFromString(std::string_view s) const noexcept;
};

}  // namespace pq

#endif
