#pragma once


class Texture {
private:
	static unsigned int _defaultTextureId;
	unsigned int _id;
	std::string _fileName; // name of texture file
	std::string _directory; // directory where texture file is located
	std::string _type; // type of texture (diffuse, specular)

	void load(const std::string& path, const std::string& type);
public:
	Texture();
	Texture(const std::string& path, const std::string& type);
};