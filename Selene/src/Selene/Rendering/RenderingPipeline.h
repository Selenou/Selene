#pragma once

#include "Buffer.h"

namespace Selene
{
	class RenderingPipeline
	{
	public:
		virtual ~RenderingPipeline() = default;
		static std::shared_ptr<RenderingPipeline> Create();
	public:
		virtual void Bind() const = 0;
		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) = 0;
		virtual std::shared_ptr<VertexBuffer> GetVertexBuffer() = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() = 0;
	};
}