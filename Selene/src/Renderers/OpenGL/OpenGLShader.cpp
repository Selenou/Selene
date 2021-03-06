#include "slnpch.h"
#include "OpenGLShader.h"
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Selene
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		ShaderSources shaderSources;

		SLN_INFO("Loading shader from [%s, %s]", vertexSrc, fragmentSrc);
		shaderSources.VertexSrc = ReadFromFile(vertexSrc);
		shaderSources.FragmentSrc = ReadFromFile(fragmentSrc);

		Compile(shaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ShaderID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniform(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniform(const std::string & name, const glm::mat4 & matrix)
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::Compile(const ShaderSources& shaderSources)
	{
		GLuint program = glCreateProgram();
		GLint isSuccess = 0;

		// Vertex compilation
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertexSrc = shaderSources.VertexSrc.c_str();
		glShaderSource(vertexShader, 1, &vertexSrc, 0);
		glCompileShader(vertexShader);

		// Check compilation error
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isSuccess);
		if (!isSuccess)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			SLN_ASSERT(false, "Vertex shader compilation failed : [%s]", &infoLog[0]);
		}

		glAttachShader(program, vertexShader);

		// Fragment compilation
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragmentSrc = shaderSources.FragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSrc, 0);
		glCompileShader(fragmentShader);

		// Check compilation error
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isSuccess);
		if (!isSuccess)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			SLN_ASSERT(false, "Fragment shader compilation failed : [%s]", &infoLog[0]);
		}

		glAttachShader(program, fragmentShader);

		// Link
		glLinkProgram(program);
		
		// Check linking error
		glGetProgramiv(program, GL_LINK_STATUS, &isSuccess);
		if (!isSuccess)
		{
			GLint maxLength = 0;
			glGetShaderiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			SLN_ASSERT(false, "Shader program linking failed : [%s]", &infoLog[0]);
		}
		
		m_ShaderID = program;

		// Cleanup
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	std::string OpenGLShader::ReadFromFile(const std::string& file)
	{
		std::string fileStr;
		std::ifstream in("assets/shaders/" + file);

		if (in)
		{
			// Get length of file
			in.seekg(0, std::ios::end);
			std::streamoff fileLength = in.tellg();
			in.seekg(0, std::ios::beg);
			fileStr.resize(fileLength);

			// Read data
			in.read(&fileStr[0], fileStr.size());
			in.close();
		}
		else
		{
			SLN_ERROR("Could not open file [%s]", file);
		}

		return fileStr;
	}
}