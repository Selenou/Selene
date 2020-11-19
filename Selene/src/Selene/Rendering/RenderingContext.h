#pragma once

namespace Selene
{
	class RenderingContext
	{
	public:
		virtual ~RenderingContext() = default;
	public:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		static std::unique_ptr<RenderingContext> Create(void* window);
	};
}