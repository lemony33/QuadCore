#pragma once

#include <GLEW-2.0.0_x64\GL\glew.h>
#include <string>

class Texture
{
public:
	Texture(const std::string& fileName);
	void Bind(unsigned int unit);
	virtual ~Texture();

protected:
private:
	Texture(const Texture& other) {};
	void operator=(const Texture& other) {};

	GLuint m_texture;
};
