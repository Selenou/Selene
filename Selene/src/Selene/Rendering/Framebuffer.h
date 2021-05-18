#pragma once

namespace Selene 
{
	struct FramebufferSpecs
	{
		uint32_t Width = 0;
		uint32_t Height = 0;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32_t GetColorAttachment() const = 0;
	public:
		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecs& spec);
	};
}