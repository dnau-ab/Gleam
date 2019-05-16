#include "Texture.h"

void Texture::load(const std::string& path, const std::string& type) {
	_type = type;

	// get directory and file name
	size_t i = path.find_last_of('/');
	if (i != std::string::npos) {
		_directory = path.substr(0, i + 1);
		_fileName = path.substr(i + 1);
	} else {
		_directory = "/";
		_fileName = path;
	}

	// check to see if texture has already been loaded
	for (size_t i = 0; i < Texture::loaded.size(); i++) {
		if (_directory.compare(Texture::loaded[i]._directory) == 0 && _fileName.compare(Texture::loaded[i]._fileName) == 0) {
			_id = Texture::loaded[i]._id;
			return;
		}
	}

	// didn't find texture in loaded vector so load it
	int width, height, numComponents;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &numComponents, 0);

	if (data) {
		// determine data format
		GLenum format = GL_RED;
		switch (numComponents) {
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		}

		// bind texture and its data
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		// setup texture mipmapping
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// get rid of image data since it is bound
		stbi_image_free(data);

		// add this texture to the collection of loaded textures
		loaded.push_back(*this);
	}
	else {
		std::cout << "ERROR::TEXTURE::LOAD::Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
}

Texture::Texture(const std::string& path, const std::string& type) {
	load(path, type);
}

unsigned int Texture::getID() const {
	return _id;
}

std::string Texture::getType() const {
	return _type;
}

std::string Texture::getName() const {
	return _fileName;
}

bool Texture::operator==(const Texture& rhs) const {
	return ((rhs._directory == _directory) && (rhs._fileName == _fileName) && (rhs._type == _type));
}

std::vector<Texture> Texture::loaded;

unsigned int Texture::loadCubemap(std::vector<std::string> faces) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

unsigned int Texture::_defaultTextureID = -1;
unsigned int Texture::getDefaultID() {
	if (_defaultTextureID == -1) {
		// generate default texture
		unsigned textureID;
		glGenTextures(1, &textureID);
		_defaultTextureID = textureID;

		GLubyte data[] = { 255, 255, 255, 255 };

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_S);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_T);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	return _defaultTextureID;
}

unsigned int Texture::getColorTextureID(glm::vec3 color) {
	unsigned textureID;
	glGenTextures(1, &textureID);

	GLubyte data[] = { (GLubyte)(color.r * 255), (GLubyte)(color.g * 255), (GLubyte)(color.b * 255), 255 };

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	return textureID;
}