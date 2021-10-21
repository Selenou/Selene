#pragma once

#include <memory>
#include <string>

#include "Selene/Rendering/Mesh.h"

namespace Selene
{
    struct MeshRendererComponent
    {
        std::shared_ptr<Mesh> Mesh;

        MeshRendererComponent() = default;
        MeshRendererComponent(const MeshRendererComponent&) = default;
    };
}