#pragma once

namespace Selene
{
	class Mesh
	{
	public:
		Mesh(const std::string& path);
		~Mesh();
	private:
		void Load();
	private:
		std::string m_FilePath;
	};
}