#pragma once

#include <memory>
#include <string>

#include "Selene/Rendering/Mesh.h"

namespace Selene
{
    struct MeshComponent
    {
        std::shared_ptr<Mesh> Mesh;

        MeshComponent() = default;
        MeshComponent(const MeshComponent&) = default;
    };
}