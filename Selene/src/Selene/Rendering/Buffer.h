#pragma once

#include <stdint.h>

namespace Selene
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;
	public:
		static std::shared_ptr<VertexBuffer> Create(void* data, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;
	public:
		static std::shared_ptr<IndexBuffer> Create(void* data, uint32_t size);
	};
}