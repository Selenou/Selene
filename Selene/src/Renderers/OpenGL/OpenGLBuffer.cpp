#include "slnpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace Selene
{
	// VertexBuffer

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, uint32_t size)
	{
		glCreateBuffers(1, &m_VboID); // generates and initializes a buffer in a single call in GL 4.5 (ARB_direct_state_access_
		glNamedBufferData(m_VboID, size, data, GL_STATIC_DRAW); //copies data into the buffer's memory
	}

	Selene::OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_VboID);
	}

	// IndexBuffer

	OpenGLIndexBuffer::OpenGLIndexBuffer(void* data, uint32_t size)
	{
		glCreateBuffers(1, &m_EboID);
		glNamedBufferData(m_EboID, size, data, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_EboID);
	}
}