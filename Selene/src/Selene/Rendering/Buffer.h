#pragma once

namespace Selene
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
	public:
		static std::shared_ptr<VertexBuffer> Create(void* data, uint32_t size);
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;
	public:
		static std::shared_ptr<IndexBuffer> Create(void* data, uint32_t size);
	public :
		virtual void Bind() const = 0;
	};
}