#pragma once

#include "Selene/Rendering/RenderingPipeline.h"

namespace Selene
{
	class OpenGLPipeline : public RenderingPipeline
	{
	public:
		virtual void Bind() const override;
		virtual void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) override;
		virtual inline std::shared_ptr<VertexBuffer> GetVertexBuffer() override { return m_Vbo; };
		virtual inline std::shared_ptr<IndexBuffer> GetIndexBuffer() override { return m_Ebo; };
	private:
		uint32_t m_VaoID;
		std::shared_ptr<VertexBuffer> m_Vbo;
		std::shared_ptr<IndexBuffer> m_Ebo;
	};
}