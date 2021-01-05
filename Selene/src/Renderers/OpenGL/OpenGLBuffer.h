#pragma once

#include "Selene/Rendering/Buffer.h"

namespace Selene
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
		virtual uint32_t GetID() override { return m_VboID; }
	private:
		uint32_t m_VboID = 0;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(void* data, uint32_t size);
		virtual ~OpenGLIndexBuffer() override;
		virtual uint32_t GetID() override { return m_EboID; }
	private:
		uint32_t m_EboID = 0;
	};
}