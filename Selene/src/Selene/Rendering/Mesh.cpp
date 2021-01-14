#include "slnpch.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Selene
{
	Mesh::Mesh(const std::string& path) :
		m_FilePath(path)
	{
		Load();
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::Load()
	{
		SLN_ENGINE_INFO("Loading mesh from [{0}]", m_FilePath.c_str());

		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_FilePath, aiProcessPreset_TargetRealtime_Quality);
	}
}