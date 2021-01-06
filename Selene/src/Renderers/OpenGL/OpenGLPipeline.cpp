#include "slnpch.h"
#include "OpenGLPipeline.h"
#include <glad/glad.h>

namespace Selene
{
	static GLenum DataTypeToOpenGLBaseType(DataType type)
	{
		switch (type)
		{
			case DataType::Float:	return GL_FLOAT;
			case DataType::Float2:  return GL_FLOAT;
			case DataType::Float3:  return GL_FLOAT;
			case DataType::Float4:  return GL_FLOAT;
			case DataType::Mat3:    return GL_FLOAT;
			case DataType::Mat4:    return GL_FLOAT;
			case DataType::Int:     return GL_INT;
			case DataType::Int2:    return GL_INT;
			case DataType::Int3:    return GL_INT;
			case DataType::Int4:    return GL_INT;
			case DataType::Bool:    return GL_BOOL;
			default:				SLN_ENGINE_ASSERT(false, "Unknown DataType!");
		}

		return 0;
	}

	OpenGLPipeline::OpenGLPipeline(const VertexBufferLayout& layout)
		: m_Layout(layout)
	{
		uint32_t attribIndex = 0;

		glCreateVertexArrays(1, &m_VaoID);

		for (const auto& element : m_Layout)
		{
			auto glBaseType = DataTypeToOpenGLBaseType(element.Type);

			glEnableVertexArrayAttrib(m_VaoID, attribIndex);

			glVertexArrayAttribFormat(m_VaoID,
				attribIndex,
				element.GetComponentCount(),
				glBaseType,
				element.Normalized ? GL_TRUE : GL_FALSE,
				element.Offset
			);

			glVertexArrayAttribBinding(m_VaoID, attribIndex, 0);
			
			attribIndex++;
		}
	}

	void OpenGLPipeline::Bind() const
	{
		glBindVertexArray(m_VaoID);
	}

	void OpenGLPipeline::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo)
	{
		glVertexArrayVertexBuffer(m_VaoID, 0, vbo->GetID(), 0, m_Layout.GetStride());
	}

	void OpenGLPipeline::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo)
	{
		glVertexArrayElementBuffer(m_VaoID, ebo->GetID());
	}
}