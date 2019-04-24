#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <queue>

#include "Mesh.h"

class MeshLoader {
private:
	static std::vector<SubMesh> processNode(aiNode* node, const aiScene* scene, const std::string& directory, const bool loadTextures);
	static SubMesh processMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory, const bool loadTextures);
	static std::vector<Texture> loadMaterialTextures(const aiMaterial* material, const aiTextureType& type, const std::string& textureTypeName, const std::string directory);

public:
	MeshLoader() = delete;
	static std::shared_ptr<Mesh> loadMesh(const std::string& directory, const std::string& fileName, const bool loadTextures = true);
};