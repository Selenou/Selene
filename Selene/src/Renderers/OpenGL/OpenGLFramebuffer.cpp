#include "slnpch.h"
#include "OpenGLFramebuffer.h"
#include <glad/glad.h>

namespace Selene
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecs& spec)
	{

	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_FramebufferID);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferID);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}