#pragma once

#include "Selene/Rendering/RenderingPipeline.h"

namespace Selene
{
	class OpenGLPipeline : public RenderingPipeline
	{
	public:
		OpenGLPipeline(const VertexBufferLayout& layout);
		virtual void Bind() const override;
		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) override;
	private:
		uint32_t m_VaoID;
		VertexBufferLayout m_Layout;
	};
}