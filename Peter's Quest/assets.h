#ifndef PETERS_QUEST_ASSETS_H_
#define PETERS_QUEST_ASSETS_H_

#include "asset_manager.h"

namespace pq {

constexpr int kFontOleaguid = 0;

constexpr int kTexturePeterBigPicture = 0;
constexpr int kTexturePlatformer1 = 1;

constexpr int kSoundEffectMenu = 0;

inline constexpr SpriteSpec kSpriteSpecBrick1 = {
    /*texture_id=*/kTexturePlatformer1,
    {/*x=*/64, /*y=*/96, /*width=*/16, /*height=*/16}};

inline constexpr SpriteSpec kSpriteSpecPlayer = {
    /*texture_id=*/kTexturePlatformer1,
    {/*x=*/7, /*y=*/14, /*width=*/18, /*height=*/18}};

const AssetSpec kAssetSpecs[] = {
    {kFontOleaguid, AssetType::kFont, "fonts/Oleaguid.ttf"},
    {kTexturePeterBigPicture, AssetType::kTexture,
     "textures/peter_big_pic.png"},
    {kTexturePlatformer1, AssetType::kTexture,
     "textures/arcade_platformerV2.png", sf::Color(134, 88, 214)},
    {kSoundEffectMenu, AssetType::kSound, "sounds/Menu_Navigate_00.wav"}};

}  // namespace pq

#endif  // PETERS_QUEST_ASSETS_H_
