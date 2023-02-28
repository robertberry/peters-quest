#include "level_loader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

namespace pq {

std::vector<LevelEntitySpec> LevelLoader::loadLevelOrDie(
    std::string path) const noexcept {
  std::vector<LevelEntitySpec> entity_specs;
  std::ifstream input_stream;
  input_stream.open(path, std::ios_base::in);

  std::string entity_type_string;
  int x;
  int y;
  while ((input_stream >> entity_type_string >> x >> y)) {
    LevelEntityType entity_type = typeFromString(entity_type_string);
    entity_specs.push_back({entity_type, x, y});
  }

  return entity_specs;
}

LevelEntityType LevelLoader::typeFromString(std::string_view s) const noexcept {
  if (s == "graybrick") {
    return LevelEntityType::kGrayBrick;
  } else if (s == "player") {
    return LevelEntityType::kPlayer;
  }

  std::cerr << "Unexpected entity type '" << s << "'" << std::endl;
  exit(1);
}

}  // namespace pq
