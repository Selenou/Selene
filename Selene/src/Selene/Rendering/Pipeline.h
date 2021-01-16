#pragma once

#include "Buffer.h"

namespace Selene
{
	class Pipeline
	{
	public:
		virtual ~Pipeline() = default;
		static std::shared_ptr<Pipeline> Create();
	public:
		virtual void Bind() const = 0;
		virtual void BindVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) {};
		virtual void BindIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) {};
	};
}