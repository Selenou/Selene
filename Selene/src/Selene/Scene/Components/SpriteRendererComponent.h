#pragma once

#include <memory>
#include <string>

#include "Selene/Rendering/Sprite.h"

namespace Selene
{
    struct SpriteRendererComponent
    {
        std::shared_ptr<Sprite> Sprite;

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
    };
}