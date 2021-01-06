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
		virtual void SetUniform(const std::string& name, const glm::mat4& matrix) = 0;
	public:
		static std::shared_ptr<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}