#pragma once

#include "Selene/Rendering/Pipeline.h"

namespace Selene
{
	class OpenGLPipeline : public Pipeline
	{
	public:
		~OpenGLPipeline() override;
	public:
		void Bind() const override;
		void BindVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) override;
		void BindIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo) override;
	private:
		uint32_t m_VaoID;
	};
}