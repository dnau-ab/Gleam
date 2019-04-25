#include "TestUtils.h"

void testModel() {
	Model model("res/models/Stanfords_Lucy_Angel/Stanford's Lucy Angel.obj");
	Model model1("res/models/Stanfords_Lucy_Angel/Stanford's Lucy Angel.obj", Shader::getDefault());
	Model model2("res/models/Stanfords_Lucy_Angel/Stanford's Lucy Angel.obj", Shader::getDefault(), false);

	std::shared_ptr<Mesh> angelMesh = MeshLoader::loadMesh("res/models/Stanfords_Lucy_Angel/", "Stanford's Lucy Angel.obj", false);
	Model angelModelA(angelMesh);
	Model angelModelB(angelMesh, Shader::getDefault());
}