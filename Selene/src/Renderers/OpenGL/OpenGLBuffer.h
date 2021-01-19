#pragma once

#include "Selene/Rendering/Buffer.h"

namespace Selene
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, uint32_t size);
		virtual ~OpenGLVertexBuffer() override;
		virtual uint32_t GetCount() const override { return m_Size / m_Layout->GetStride(); }
		virtual uint32_t GetID() const override { return m_VboID; }
	private:
		uint32_t m_VboID = 0;
		uint32_t m_Size;
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(void* data, uint32_t size);
		virtual ~OpenGLIndexBuffer() override;
		virtual uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }
		virtual uint32_t GetID() const override { return m_EboID; }
	private:
		uint32_t m_EboID = 0;
		uint32_t m_Size;
	};
}