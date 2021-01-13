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

	void OpenGLPipeline::Bind() const
	{
		glBindVertexArray(m_VaoID);
	}

	void OpenGLPipeline::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo)
	{
		m_Vbo = vbo;
		uint32_t attribIndex = 0;
		auto layout = *(m_Vbo->GetLayout());

		if (m_VaoID)
		{
			glDeleteVertexArrays(1, &m_VaoID);
		}
			
		glCreateVertexArrays(1, &m_VaoID);

		for (const auto& element : layout)
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

		glVertexArrayVertexBuffer(m_VaoID, 0, vbo->GetID(), 0, layout.GetStride());
	}

	void OpenGLPipeline::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ebo)
	{
		m_Ebo = ebo;
		glVertexArrayElementBuffer(m_VaoID, ebo->GetID());
	}
}