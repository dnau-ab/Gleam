#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stb_image.h>

#include <string>
#include <vector>
#include <iostream>

class Texture {
private:
	static unsigned int _defaultTextureID;
	
	unsigned int _id;
	std::string _fileName; // name of texture file
	std::string _directory; // directory where texture file is located
	std::string _type; // type of texture (diffuse, specular)

	void load(const std::string& path, const std::string& type);
public:
	static unsigned int loadCubemap(std::vector<std::string> faces);
	static unsigned int getDefaultID();
	static unsigned int getColorTextureID(glm::vec3 color);
	static std::vector<Texture> loaded;
	
	Texture();
	Texture(const std::string& path, const std::string& type);

	unsigned int getID() const;
	std::string getType() const;
	std::string getName() const;

	bool operator==(const Texture& rhs) const;
};