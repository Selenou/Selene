#pragma once

namespace Selene
{
	class Context
	{
	public:
		virtual ~Context() = default;
	public:
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void SwapBuffers() = 0;
	public:
		static std::unique_ptr<Context> Create(void* window);
	};
}