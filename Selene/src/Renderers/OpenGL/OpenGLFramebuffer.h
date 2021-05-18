#pragma once

#include "Selene/Rendering/Framebuffer.h"

namespace Selene
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecs& spec);
		virtual ~OpenGLFramebuffer();
	public:
		virtual void Bind() override;
		virtual void Unbind() override;
	public:
		inline virtual uint32_t GetColorAttachment() const override { return m_ColorAttachmentID; }
	private:
		uint32_t m_FramebufferID;
		uint32_t m_ColorAttachmentID;
	};
}