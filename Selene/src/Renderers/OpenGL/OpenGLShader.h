#pragma once

#include "Selene/Rendering/Shader.h"

namespace Selene
{

	struct ShaderSources
	{
		std::string VertexSrc;
		std::string FragmentSrc;
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();
	public:
		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		std::string ReadFromFile(const std::string& file);
		void Compile(const ShaderSources& shaderSources);
	private:
		uint32_t m_ShaderID;
	};
}