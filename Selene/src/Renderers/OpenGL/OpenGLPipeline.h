#pragma once

#include "Selene/Rendering/Pipeline.h"

namespace Selene
{
	class OpenGLPipeline : public Pipeline
	{
	public:
		virtual void Bind() const override;
		virtual void BindVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) override;
		virtual void BindIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) override;
	private:
		uint32_t m_VaoID;
	};
}