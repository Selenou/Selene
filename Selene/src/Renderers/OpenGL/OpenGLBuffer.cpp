#include "slnpch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace Selene
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size)
	{
		glCreateBuffers(1, &vboID); // generates and initializes a buffer in a single call in GL 4.5 (ARB_direct_state_access_
		glNamedBufferData(vboID, size, data, GL_STATIC_DRAW); //copies data into the buffer's memory
	}

	Selene::OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &vboID);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}