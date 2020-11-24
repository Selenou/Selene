#pragma once

namespace Selene
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
	public:
		static std::shared_ptr<VertexBuffer> Create(float* data, uint32_t size);
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};
}