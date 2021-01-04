#pragma once

#include "Selene/Rendering/Buffer.h"

namespace Selene
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, uint32_t size);
		~OpenGLVertexBuffer() override;
	private:
		uint32_t m_VboID = 0;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(void* data, uint32_t size);
		~OpenGLIndexBuffer() override;
	private:
		uint32_t m_EboID = 0;
	};
}