#include "slnpch.h"
#include "OpenGLShader.h"
#include <fstream>
#include <glad/glad.h>

namespace Selene
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		ShaderSources shaderSources;
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

	void OpenGLShader::Compile(const ShaderSources& shaderSources)
	{
		GLuint program = glCreateProgram();

		// Vertex
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertexSrc = shaderSources.VertexSrc.c_str();
		glShaderSource(vertexShader, 1, &vertexSrc, 0);
		glCompileShader(vertexShader);
		glAttachShader(program, vertexShader);

		// Fragment
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragmentSrc = shaderSources.FragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSrc, 0);
		glCompileShader(fragmentShader);
		glAttachShader(program, fragmentShader);

		// Link
		glLinkProgram(program);
		m_ShaderID = program;

		//Cleanup
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	std::string OpenGLShader::ReadFromFile(const std::string& file)
	{
		std::string fileStr;
		std::ifstream in("res/shaders/" + file);

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
			SLN_ENGINE_ERROR("Could not open file '{0}'", file);
		}

		return fileStr;
	}
}