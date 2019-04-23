#include "TestUtils.h"

void testTexture() {
	// check default texture is being created
	assert(Texture::getDefaultID() != -1);

	// create texture objects
	Texture diffuseTex("res/texture_diffuse.png", "diffuse");
	Texture specularTex("res/texture_specular.png", "specular");

	// check textures are added to loaded vector
	assert(Texture::loaded.size() == 2);

	// check diffuseTex members
	assert(diffuseTex.getName() == "texture_diffuse.png");
	assert(diffuseTex.getType() == "diffuse");
	// check specularTex members
	assert(specularTex.getName() == "texture_specular.png");
	assert(specularTex.getType() == "specular");

	// check loaded vector elements for equality with created texture objects
	assert(Texture::loaded[0] == diffuseTex);
	assert(Texture::loaded[1] == specularTex);
}