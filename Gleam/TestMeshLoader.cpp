#include "TestUtils.h"

void testMeshLoader() {
	std::shared_ptr<Mesh> invalid = MeshLoader::loadMesh("invalid", "file");
	assert(invalid == nullptr);

	std::shared_ptr<Mesh> doesNotExist = MeshLoader::loadMesh("res/models", "fakeModel.obj");
	assert(doesNotExist == nullptr);

	std::shared_ptr<Mesh> angelOBJ = MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.obj", true);
	assert(angelOBJ != nullptr);

	std::shared_ptr<Mesh> angel3DS = MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.3ds", true);
	assert(angel3DS != nullptr);

	std::shared_ptr<Mesh> bucketFBX_supported = MeshLoader::loadMesh("res/models/", "bucket.fbx", false);
	assert(bucketFBX_supported != nullptr);

	std::shared_ptr<Mesh> angelFBX_unsupported = MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.fbx", false);
	assert(angelFBX_unsupported == nullptr);

	std::shared_ptr<Mesh> angelMAX_unsupported = MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.max", true);
	assert(angelMAX_unsupported == nullptr);

}