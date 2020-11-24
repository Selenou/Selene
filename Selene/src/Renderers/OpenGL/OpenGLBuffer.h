#pragma once

#include "Selene/Rendering/Buffer.h"

namespace Selene
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* data, uint32_t size);
		~OpenGLVertexBuffer() override;
	public:
		void Bind() override;
		void Unbind() override;
	private:
		uint32_t vboID = 0;
	};
}