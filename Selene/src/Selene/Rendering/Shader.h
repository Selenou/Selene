#pragma once

#include <glm/glm.hpp>

namespace Selene
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	public:
		virtual void SetUniform(const std::string& name, const int value) = 0;
		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) = 0;
	public:
		static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////

	class ShaderLibrary
	{
	public:
		void Load(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		const std::shared_ptr<Shader>& Get(const std::string& name);
	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
	};
}