#pragma once

#include <memory>
#include <string>

#include "Selene/Rendering/Sprite.h"

namespace Selene
{
    struct SpriteComponent
    {
        std::shared_ptr<Sprite> Sprite;

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
    };
}