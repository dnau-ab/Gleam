#include "TestUtils.h"

void testModel() {
	Model model(MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.obj", true));
	Model model1(MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.obj", true), Shader::getDefault());
	Model model2(MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.obj", false), Shader::getDefault());

	std::shared_ptr<Mesh> angelMesh = MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.obj", false);
	Model angelModelA(angelMesh);
	Model angelModelB(angelMesh, Shader::getDefault());
}