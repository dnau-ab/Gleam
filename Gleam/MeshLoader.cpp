#include "MeshLoader.h"

std::shared_ptr<Mesh> MeshLoader::loadMesh(const std::string& directory, const std::string& fileName, const bool loadTextures) {
	std::string meshPath = directory + "/" + fileName;
	std::shared_ptr<Mesh> mesh = Mesh::getLoaded(meshPath);
	if (mesh == nullptr) {
		std::cout << "LOADER::Loading " << fileName << " from " << directory << std::endl;
		Assimp::Importer importer;
		std::string path = directory == "" ? fileName : (directory + "/" + fileName);
		const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_PreTransformVertices);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "ERROR::LOADER::LOAD OBJECT::ASSIMP::" << importer.GetErrorString() << std::endl;
			return nullptr;
		}

		mesh = std::make_shared<Mesh>(Mesh(processNode(scene->mRootNode, scene, directory, loadTextures), meshPath));
		Mesh::addLoadedMesh(std::weak_ptr<Mesh>(mesh));
	}
	return mesh;
}

std::vector<SubMesh> MeshLoader::processNode(aiNode* node, const aiScene* scene, const std::string& directory, const bool loadTextures) {
	std::vector<SubMesh> meshes;
	std::queue<aiNode*> nodeQueue;
	nodeQueue.push(node);
	while (!nodeQueue.empty()) {
		aiNode* node = nodeQueue.front();
		nodeQueue.pop();
		// get node's meshes
		for (size_t i = 0; i < node->mNumMeshes; i++) {
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.emplace_back(processMesh(mesh, scene, directory, loadTextures));
		}
		// add node's children
		for (size_t i = 0; i < node->mNumChildren; i++) {
			nodeQueue.push(node->mChildren[i]);
		}
	}

	return meshes;
}

SubMesh MeshLoader::processMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory, const bool loadTextures) {
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;
	std::vector<Texture> textures;

	for (size_t i = 0; i < mesh->mNumVertices; i++) {
		Vertex vert;
		vert.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vert.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		// if mesh has texture coordinates
		if (mesh->mTextureCoords[0]) {
			// load texture coordinates
			vert.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}
		else {
			// add defaults
			vert.texCoord = glm::vec2(0, 0);
		}
		// add vertex
		vertices.push_back(vert);
	}

	// add indices of faces
	for (size_t i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	Material meshMaterial;

	// if mesh has materials
	if (mesh->mMaterialIndex >= 0) {
		// load materials
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// set shininess
		float shininess = 0;
		aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &shininess);
		//if (shininess != 0)
		//meshMaterial.setShininess(shininess);

		if (loadTextures) {
			// load diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse", directory);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			// load specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular", directory);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			// load normal maps
			std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "normal", directory);
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			// load ambient maps
			std::vector<Texture> ambientMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "ambient", directory);
			textures.insert(textures.end(), ambientMaps.begin(), ambientMaps.end());
			// load height maps
			std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "height", directory);
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

			meshMaterial.setTextures(textures);
		}
	}

	return SubMesh(vertices, indices, meshMaterial);
}

std::vector<Texture> MeshLoader::loadMaterialTextures(const aiMaterial* material, const aiTextureType& type, const std::string& textureTypeName, const std::string directory) {
	std::vector<Texture> textures;
	// get all textures of a specified type
	for (size_t i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);

		bool loaded = false;
		for (size_t j = 0; j < Texture::loaded.size(); j++) {
			if (std::strcmp(Texture::loaded[j].getName().data(), str.C_Str()) == 0) {
				textures.push_back(Texture::loaded[j]);
				loaded = true;
				break;
			}
		}
		if (!loaded) {
			textures.emplace_back(Texture(directory + "/" + str.C_Str(), textureTypeName));
		}
	}
	return textures;
}