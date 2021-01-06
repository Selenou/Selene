#pragma once

#include "Selene/Rendering/Buffer.h"

namespace Selene
{
	class RenderingPipeline
	{
	public:
		virtual ~RenderingPipeline() = default;
		static std::shared_ptr<RenderingPipeline> Create(const VertexBufferLayout& layout);
	public:
		virtual void Bind() const = 0;
		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) = 0;
		//virtual void GetVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) = 0;
		//virtual void GetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) = 0;
	};
}