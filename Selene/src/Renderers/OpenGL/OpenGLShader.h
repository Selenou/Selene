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
	public:
		virtual void SetUniform(const std::string& name, const int value) override;
		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) override;
	private:
		std::string ReadFromFile(const std::string& file);
		void Compile(const ShaderSources& shaderSources);
	private:
		uint32_t m_ShaderID;
	};
}