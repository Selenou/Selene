#pragma once

namespace Selene
{
	struct AABBColliderComponent
	{
		glm::vec2 PositionOffset = { 0.0f, 0.0f };
		glm::vec2 Size = { 1.0f, 1.0f };

		AABBColliderComponent() = default;
		AABBColliderComponent(const AABBColliderComponent&) = default;
	};
}